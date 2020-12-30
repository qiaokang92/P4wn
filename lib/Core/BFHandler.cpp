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

#include "BFHandler.h"

using namespace klee;
using namespace std;
using namespace llvm;
using boost::math::binomial;

namespace klee {
  extern RNG theRNG;
}

namespace boost {
   void throw_exception( std::exception const & e ) {

   }
}

BFHandler::BFHandler(Executor &_executor)
: executor(_executor)
{
   printf("new bf handler created!\n");
}

BFHandler::BFHandler(BFHandler &_handler)
: executor(_handler.executor)
{

}

BFHandler::~BFHandler()
{

}

BF::BF()
{
}

BF::BF(int _size):
   size(_size),
   cur_size(0)
{
   // create an empty table
   LOG(LOG_MASK_BF, "creating an empty hash table, size=%d", _size);
}

BF::BF(const BF &_table):
   size(_table.size),
   cur_size(_table.cur_size)
{
}

BF::~BF()
{
}

int BFHandler::bf_init(ExecutionState &cur, size_t sz)
{
   LOG(LOG_MASK_BF, "allocating bf, size=%ld", sz);
   cur.bf = new BF(sz);
   return 0;
}

// This function computes the probability that for a BF size >=3,
// a new accss would add n new dirty bits to the BF
double BFHandler::get_path_prob(BF* bf, int n)
{
   double ret = 0;
   assert(bf->cur_size >= 3);
   assert(n >= 0 && n <= 3);
   // uint64_t k = bf->cur_size;
   // uint64_t N = bf->size;
   // uint64_t base = N * N * N;
   double k = bf->cur_size;
   double N = bf->size;
   double base = N * N * N;

   if (n == 0) {
      ret = k * k * k / base;
   } else if (n == 1) {
      ret = (3 * k * k * (N - k) + 3 * k * (N - k) + (N - k)) / base;
   } else if (n == 2) {
      ret = (3 * k * (N - k) * (N - k - 1) + 3 * (N - k) * (N - k - 1)) / base;
   } else if (n == 3) {
      ret = (N - k) * (N - k - 1) * (N - k - 2) / base;
   }

   // LOG(LOG_MASK_BF, "n=%d, k=%f, N=%f, ret=%f", n, k, N, ret);
   return ret;
}

int BFHandler::bf_access(ExecutionState &cur,
                         vector<ExecutionState*> &states,
                         vector<int> &rets)
{
   BF *bf = cur.bf;
   assert(bf);
   LOG(LOG_MASK_BF, "accessing bf, cur size=%d", bf->cur_size);

   // It's impossible that BF size is 1 or 2
   assert(bf->cur_size == 0 || bf->cur_size >= 3);

   // When the BF is empty, can only produce "miss" result
   if (bf->cur_size == 0) {
      bf->cur_size = 3;
      states.push_back(&cur);
      rets.push_back(BF_ACCESS_MISS_ADD3);

      LOG(LOG_MASK_BF, "accessing an empty bf, returning one path (miss)");
      return 0;
   }

   // When BF.size >= 3, that will be 4 possible outputs
   executor.branchTableAccessNoCond(cur, 4, states);
   rets.push_back(BF_ACCESS_HIT);
   rets.push_back(BF_ACCESS_MISS_ADD1);
   rets.push_back(BF_ACCESS_MISS_ADD2);
   rets.push_back(BF_ACCESS_MISS_ADD3);

   // update path probs for child states
   // for the first branch, bf size doesn't change
   states[0]->updatePathProb(get_path_prob(bf, 0));

   states[1]->updatePathProb(get_path_prob(bf, 1));
   states[1]->bf->cur_size += 1;

   states[2]->updatePathProb(get_path_prob(bf, 2));
   states[2]->bf->cur_size += 2;

   states[3]->updatePathProb(get_path_prob(bf, 3));
   states[3]->bf->cur_size += 3;

   LOG(LOG_MASK_BF, "accessing a non-empty bf, returning 4 paths");
   return 0;
}

int BFHandler::bf_read(ExecutionState &cur,
                         vector<ExecutionState*> &states,
                         vector<int> &rets)
{
   BF *bf = cur.bf;
   assert(bf);
   LOG(LOG_MASK_BF, "reading bf, cur size=%d", bf->cur_size);

   // It's impossible that BF size is 1 or 2
   assert(bf->cur_size == 0 || bf->cur_size >= 3);

   // When the BF is empty, can only produce "miss" result
   if (bf->cur_size == 0) {
      states.push_back(&cur);
      rets.push_back(GREYBOX_MISS);
      LOG(LOG_MASK_BF, "bf is empty, read misses");
      return 0;
   }

   // When BF.size >= 3, that will be 2 possibilities: miss or hit
   double probHit = get_path_prob(bf, 0);
   double probMiss = 1 - probHit;
   executor.branchTableAccessNoCond(cur, 2, states);

   rets.push_back(GREYBOX_HIT);
   rets.push_back(GREYBOX_MISS);

   states[0]->updatePathProb(probHit);
   states[1]->updatePathProb(probMiss);

   LOG(LOG_MASK_BF, "bf is empty, read misses");

   return 0;
}
