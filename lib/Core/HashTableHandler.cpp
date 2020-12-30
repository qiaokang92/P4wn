#include "HashTableHandler.h"
#include <stdio.h>
#include <string>
#include <map>
#include <fstream>
#include "llvm/Support/raw_ostream.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>
#include "helper.h"
#include "klee/ExecutionState.h"
#include "klee/Internal/ADT/RNG.h"
#include <boost/math/distributions/binomial.hpp>
#include "Executor.h"
#include <cmath>
#include "klee/klee.h"

// TODO: use macros in klee.h instead of hard-coded return values.

using namespace klee;
using namespace std;
using namespace llvm;
using boost::math::binomial;

namespace klee {
  extern RNG theRNG;
}

HashTableHandler::HashTableHandler(Executor &_executor)
: executor(_executor)
{
   printf("new ht handler created!\n");
}

HashTableHandler::HashTableHandler(HashTableHandler &_handler)
: executor(_handler.executor)
{

}

HashTableHandler::~HashTableHandler()
{

}

HashTable::HashTable()
{
}

HashTable::HashTable(int _size):
   status(-1),
   size(_size),
   cur_size(0)
{
   // create an empty table
   LOG(LOG_MASK_HT, "creating an empty hash table, size=%d", _size);
}

HashTable::HashTable(const HashTable &_table):
   status(_table.status),
   size(_table.size),
   cur_size(_table.cur_size),
   dist(_table.dist)
{
}

HashTable::~HashTable()
{
}

int HashTableHandler::ht_init(ExecutionState &cur, size_t sz)
{
   LOG(LOG_MASK_HT, "allocating table size=%ld", sz);
   cur.table = new HashTable(sz);

   // TODO: add deletion of the hash table
   return 0;
}


int HashTableHandler::ht_access(ExecutionState &cur,
                                vector<ExecutionState*> &states,
                                vector<int> &rets)
{
   HashTable *t = cur.table;
   assert(t);

   LOG(LOG_MASK_HT, "accessing table, cur size=%d", t->cur_size);

   // processing the first access
   if (t->cur_size == 0) {
      LOG(LOG_MASK_HT, "table is empty, can only insert entry, pathprob=%f",
          cur.getPathProb());
      t->status = GREYBOX_MISS;
      states.push_back(&cur);
      rets.push_back(GREYBOX_MISS);
      return 0;
   }

   // TODO: cannot insert to empty if table is full
   assert(t->cur_size < t->size);

   // Obtain per-path probabilities
   double probEmpty = 1 - ((double) t->cur_size) / ((double) t->size);
   double probNonEmpty = 1 - probEmpty;
   double probCollision = probNonEmpty * (1.0 / (double) t->size);
   double probHit = probNonEmpty - probCollision;
   assert(probEmpty + probCollision + probHit > 0.99);

   LOG(LOG_MASK_HT, "table not empty, pathprob=%g, empty=%g,hit=%g,col=%g",
       cur.getPathProb(), probEmpty, probHit, probCollision);

   // if we are doing Monte Carlo sampling, just pick up one state
   if (cur.isSample == true) {
      assert(cur.isSampleDone == false);

      double r = theRNG.getDouble();

      LOG(LOG_MASK_HT, "r=%f", r);

      // pick up a branch according to per-path prob
      states.push_back(&cur);
      t = states[0]->table;
      if (r < probEmpty) {
         cur.updatePathProb(probEmpty);
         t->status = GREYBOX_MISS;
         rets.push_back(GREYBOX_MISS);
         LOG(LOG_MASK_HT, "access=empty, pathprob=%f", cur.getPathProb());
      } else if (probEmpty <= r && r < probEmpty + probCollision) {
         cur.updatePathProb(probCollision);
         t->status = GREYBOX_COL;
         rets.push_back(GREYBOX_COL);
         LOG(LOG_MASK_HT, "access=col, pathprob=%f", cur.getPathProb());
      } else {
         cur.updatePathProb(probHit);
         t->status = GREYBOX_HIT;
         rets.push_back(GREYBOX_HIT);
         LOG(LOG_MASK_HT, "access=hit, pathprob=%f", cur.getPathProb());
      }

      return 0;
   }

   // fork three states
   executor.branchTableAccessNoCond(cur, 3, states);
   rets.push_back(GREYBOX_MISS);
   rets.push_back(GREYBOX_HIT);
   rets.push_back(GREYBOX_COL);
   assert(states.size() == 3);
   assert(rets.size() == 3);

   // empty prob
   states[0]->updatePathProb(probEmpty);
   // hit prob
   states[1]->updatePathProb(probHit);
   // collision prob
   states[2]->updatePathProb(probCollision);

   // empty
   t = states[0]->table;
   t->status = GREYBOX_MISS;

   // hit
   t = states[1]->table;
   t->status = GREYBOX_HIT;

   // collision
   t = states[2]->table;
   t->status = GREYBOX_COL;

   return 0;
}

int HashTableHandler::ht_check(ExecutionState &cur, int &status)
{
   ERR("not implemented");
   assert(0);
   return 0;
}

// Based the previous access result, return a branch for each possible
// value in the table
int HashTableHandler::ht_read(ExecutionState &cur,
                              vector<ExecutionState*> &states,
                              vector<int> &rets)
{
   HashTable *t = cur.table;

   LOG(LOG_MASK_HT, "reading HT, status=%d, cur_size=%d", t->status,
       t->cur_size);

   // the access misses the table, have to return 0
   if (t->status == GREYBOX_MISS) {
      rets.push_back(HT_READ_FALSE);
      states.push_back(&cur);
      return 0;
   }

   // hit or collision
   assert(t->dist.size() > 0);
   executor.branchTableAccessNoCond(cur, t->dist.size(), states);

   int i = 0;
   for (auto x : t->dist) {
      rets.push_back(x.first);
      states[i]->updatePathProb(x.second);
      LOG(LOG_MASK_HT, "read value=%d, prob=%g, pathProb=%g", x.first,
          x.second, states[i]->getPathProb());
      i ++;
   }

   return 0;
}

// Write val to the table, based on previous access result
// This API doesn't fork states
int HashTableHandler::ht_write(ExecutionState &cur, int val)
{
   HashTable *t = cur.table;
   int num = t->cur_size;
   double p0 = t->dist[0];
   double p1 = t->dist[1];

   // empty table, and we just missed the table
   if (num == 0) {
      assert(t->status == GREYBOX_MISS);
      LOG(LOG_MASK_HT, "writing %d to an empty table", val);
      if (val == 0) {
         t->dist[0] = 1;
         t->dist[1] = 0;
      } else if (val == 1) {
         t->dist[0] = 0;
         t->dist[1] = 1;
      }
      t->cur_size += 1;
      return 0;
   }

   // Table not empty, but we just missed the table
   if (t->status == GREYBOX_MISS) {
      for (auto d: t->dist) {
         if (d.first == val) {
            d.second = (d.second * num + 1) / (num + 1);
         } else {
            d.second = (d.second * num) / (num + 1);
         }
      }
      t->cur_size += 1;
      return 0;
   }

      // write 1 to an empty entry
      /*
      if (val == 1) {
         t->dist[0] = (p0 * num) / (num + 1);
         t->dist[1] = 1 - t->dist[0];
      } else if (val == 0) {
         t->dist[0] = (p0 * num + 1) / (num + 1);
         t->dist[1] = 1 - t->dist[0];
      }
      */


   // Table not empty, and we just hit or collide on an existing entry
   // TODO: only support binary HT
   if (t->dist.size() > 2) {
      t->dump();
   }
   assert(t->dist.size() <= 2);
   if (val == 1) {
      t->dist[0] = p0 * ((p0 * num - 1) / num) + (p0 * p1);
      t->dist[1] = 1 - t->dist[0];
   } else if (val == 0) {
      t->dist[0] = p0 * p0 +
                   p1 * (p0 * num + 1) / num;
      t->dist[1] = 1 - t->dist[0];
   }

   return 0;
}

long long factorial(long number)
{
   long long ret;
   if (number <= 1)
		ret = 1;
	else
		ret = number * factorial(number - 1);

   assert(ret > 0);

   return ret;
}

long long combinator(int n,int m)
{
   // LOG(LOG_MASK_HT, "computing C %d %d", n, m);

   int temp;
	if (n < m) {
      temp = n;
		n = m;
		m = temp;
   }

	long long ret = factorial(n) / (factorial(m) * factorial(n - m));

   // LOG(LOG_MASK_HT, "C %d %d = %lld", n, m, ret);

   return ret;
}

// This API only supports binary HT, e.g., the value must be 0 or 1
double HashTable::test_sum_prob(int sum)
{
   double p0, p1, ret = 0;
   p0 = dist[0];
   p1 = dist[1];

   if (cur_size < sum) {
      return 0;
   }

   const double success_fraction = p1;
   int flips = cur_size;

   binomial flip(flips, success_fraction);

   ret = 1 - cdf(flip, sum - 1);

   assert(ret >= 0);
   assert(ret <= 1);

   /*
   for (int i=sum; i <= cur_size; i ++) {
      long long c = combinator(i, cur_size);
   }
   */

   LOG(LOG_MASK_HT, "test sum prob=%f for sum>=%d, size=%d, curSize=%d, p0=%f, p1=%f",
       ret, sum, size, cur_size, p0, p1);

   return ret;
}

int HashTableHandler::ht_test_sum(ExecutionState &cur, int sum,
                                  vector<ExecutionState*> &states,
                                  vector<int> &rets)
{
   // Compute and update outgoing path probabilities.
   double cur_prob = cur.getPathProb();

   // Using the CDF of binomial distribution to compute p
   double p = cur.table->test_sum_prob(sum);
   assert(p >= 0 && p <= 1);

   // if larger than sum is 0% or 100%
   if (p < 0.0001 || p > 0.9999) {
      LOG(LOG_MASK_HT, "p=%f, test_sum is determinsitic", p);
      states.push_back(&cur);
      rets.push_back(p < 0.0001 ? 0 : 1);
      LOG(LOG_MASK_HT, "continue pcur=%f, test_sum is %s", cur_prob,
          p > 0.9999 ? "100%" : "0%");
      return 0;
   }

   // if we are doing Monte Carlo sampling, just pick up one state
   if (cur.isSample == true) {
      assert(cur.isSampleDone == false);

      double r = theRNG.getDouble();

      states.push_back(&cur);

      // 10% return 1 (>= sum)
      if (r < p) {
         cur.updatePathProb(p);
         rets.push_back(1);
      }
      // 90% return 0 (<= sum)
      else {
         cur.updatePathProb(1-p);
         rets.push_back(0);
      }

      LOG(LOG_MASK_HT, "test sum returning, path prob=%f", cur.getPathProb());
      return 0;
   }

   // if both possible, need to fork two branches
   executor.branchTableAccessNoCond(cur, 2, states);
   assert(states.size() == 2);

   states[0]->updatePathProb(p);
   rets.push_back(1);
   states[1]->updatePathProb(1 - p);
   rets.push_back(0);

   LOG(LOG_MASK_HT, "pcur=%f, p1=%f, p2=%f", cur.getPathProb(),
       states[0]->getPathProb(), states[1]->getPathProb());

   return 0;
}

int HashTableHandler::ht_add_handler(ExecutionState &state)
{
   int status = state.table->status;
   // ht_add returns the prob of hitting/missing the hash table,
   // in this handler we don't need that.
   state.table->ht_add(status);
   return 0;
}

// Add by 1 to each possible entry of HT, based the previous access result
// previous result is provided by flag, so that this API can be used by
// cmin_add_to_ht
double HashTable::ht_add(int flag)
{
   LOG(LOG_MASK_CMIN, "adding one to hash table, cur_size=%d, flag=%d",
       cur_size, flag);

   double ret;
   // hit
   if (flag) {
      assert(cur_size > 0);
      int largest = 0;
      for (auto const x : dist) {
         if (x.second > 0 && x.first > largest) {
            largest = x.first;
         }
      }
      int v = largest;

      if (dist[v] * cur_size > 1) {
         dist[v] = (double)(dist[v] * cur_size - 1) / (double)cur_size;
      } else {
         dist[v] = 0;
      }

      dist[v+1] = (double)(dist[v+1] * cur_size + 1) / (double)cur_size;

      ret = (double)cur_size / (double)size;
      return ret;
   }

   // miss
   ret = ((double)size - (double)cur_size) / (double)size;

   if (dist.size() == 0) {
      dist[1] = 1.0;
   } else {
      for (auto x : dist) {
         if (x.first == 1) {
            x.second = (x.second * cur_size + 1) / (cur_size + 1);
         } else {
            x.second = (x.second * cur_size) / (cur_size + 1);
         }
      }
   }

   cur_size += 1;
   return ret;
}

void HashTable::dump()
{
   LOG(LOG_MASK_HT, "hash table size=%d, cur_size=%d", size, cur_size);
   for (auto x : dist) {
      LOG(LOG_MASK_HT, "[v=%d, p=%f]", x.first, x.second);
   }
}

int HashTableHandler::ht_read_larger_than(ExecutionState &cur,
                                          int val,
                                          vector<ExecutionState*> &states,
                                          vector<int> &rets)
{
   HashTable *t = cur.table;
   double larger = t->ht_get_prob_larger_than_after_hit(val);
   if (larger == 0.0) {
      states.push_back(&cur);
      rets.push_back(0);
      LOG(LOG_MASK_HT, "cannot greater than %d, returning one branch", val);
      return 0;
   } else if (larger == 1.0) {
      states.push_back(&cur);
      rets.push_back(1);
      LOG(LOG_MASK_HT, "always greater than %d, returning one branch", val);
      return 0;
   }

   executor.branchTableAccessNoCond(cur, 2, states);

   // branch 1: greater than val
   rets.push_back(1);
   states[0]->updatePathProb(larger);
   // branch 2: cmin is not greater than val
   rets.push_back(0);
   states[1]->updatePathProb(1 - larger);

   LOG(LOG_MASK_HT, "greater than %d prob=%g, elseprob=%g", val,
       larger, 1-larger);
   return 0;
}

// Get the probability that ht value is greater than val
// This API assumes that the previous access has hit HT
double HashTable::ht_get_prob_larger_than_after_hit(int val)
{
   double ret = 0.0;

   for (auto x : dist) {
      if (x.first >= val) {
         ret += x.second;
      }
   }
   return ret;
}

// Get the probability that ht value is greater than val
// This API doesn't assume that the previous access has hit HT
// Should be used by CminHandler::cmin_larger_than
double HashTable::ht_get_prob_larger_than(int val)
{
   double ret = 0.0;

   for (auto x : dist) {
      if (x.first >= val) {
         ret += (x.second * (double)cur_size / (double)size);
      }
   }
   return ret;
}

int HashTable::getMaxValue()
{
   int ret = 0;
   for (auto e: dist) {
      if (e.second > 0) {
         ret = ret > e.first ? ret : e.first;
      }
   }
   return ret;
}
