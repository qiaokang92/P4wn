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
#include "MAHandler.h"
#include "klee/klee.h"

using namespace klee;
using namespace std;
using namespace llvm;
using boost::math::binomial;

namespace klee {
  extern RNG theRNG;
}

MAHandler::MAHandler(Executor &_executor)
: executor(_executor)
{
   printf("new MA handler created!\n");
}

MAHandler::MAHandler(MAHandler &_handler):
   executor(_handler.executor)
{

}

MAHandler::~MAHandler()
{

}

MATable::MATable(int _nflows, ExecutionState *_state):
   state(_state),
   nflows(_nflows),
   cur_size(0)
{
   LOG(LOG_MASK_MA, "state[%d]: creating an MA table, nflows=%d",
       state->id, _nflows);
}

MATable::MATable(const MATable &_ma):
   nflows(_ma.nflows),
   cur_size(_ma.cur_size),
   status(_ma.status),
   data(_ma.data)
{
   LOG(LOG_MASK_MA, "state[%d]: forking a MA table, nflows=%d",
       _ma.state->id, _ma.nflows);
}

MATable::~MATable()
{
}

int MATable::ma_insert(int val)
{
   /*
   LOG(LOG_MASK_MA, "state[%d]: inserting val=%d to MA, cur_size %d -> %d",
       state->id, val, cur_size, cur_size + 1);

   cur_size += 1;
   auto it = data.find(val);
   if (it == data.end()) {
      data[val] = 1;
   } else {
      data[val] += 1;
   }
   */

   LOG(LOG_MASK_MA, "ignore MA table insertion request, val=%d", val);
   return 0;
}

int MAHandler::ma_init(ExecutionState &cur)
{
   //int nflows = executor.queryHandler->queryProbByName("nflows");
   int nflows = 100; // not used
   LOG(LOG_MASK_CMIN, "state[%d]: allocating MA, nflows=%d", cur.id, nflows);
   cur.ma = new MATable(nflows, &cur);
   return 0;
}

int MAHandler::ma_insert(ExecutionState &cur, int val)
{
   //return cur.ma->ma_insert(val);
   LOG(LOG_MASK_MA, "ignore MA table insertion request, val=%d", val);
   return 0;
}

int MAHandler::ma_access(ExecutionState &cur,
                         std::vector<ExecutionState*> &states,
                         std::vector<int> &rets)
{
   MATable *ma = cur.ma;

   // empty MA table, will have to miss on the table
   /*
   if (ma->cur_size == 0) {
      states.push_back(&cur);
      rets.push_back(GREYBOX_MISS);
      return 0;
   }
   */
   // fork 2 paths, hit or miss, and update the flag

   //unsigned nflows = executor.queryHandler->queryProbByName("nflows");
   //unsigned npkts  = executor.queryHandler->queryProbByName("ntcp");
   //unsigned npkts_per_flow = npkts / nflows;

   double probMiss = executor.queryHandler->queryProbTableMiss();
   double probHit  = 1 - probMiss;
   executor.branchTableAccessNoCond(cur, 2, states);

   LOG(LOG_MASK_MA, "probMiss=%g", probMiss);

   // the hit path
   rets.push_back(GREYBOX_HIT);
   states[0]->updatePathProb(probHit);
   states[0]->ma->status = GREYBOX_HIT;

   LOG(LOG_MASK_MA, "probHit %g, state[%d] is the hit branch, pathProb %g",
       probHit, states[0]->id, states[0]->getPathProb());

   // the miss path
   rets.push_back(GREYBOX_MISS);
   states[1]->updatePathProb(probMiss);
   states[1]->ma->status = GREYBOX_MISS;

   LOG(LOG_MASK_MA, "probMiss %g, state[%d] is the miss branch, pathProb %g",
       probMiss, states[1]->id, states[1]->getPathProb());

   return 0;
}

int MAHandler::ma_read(ExecutionState &cur,
                       std::vector<ExecutionState*> &states,
                       std::vector<int> &rets)
{
   MATable *ma = cur.ma;

   /*
   if (ma->cur_size == 0 || ma->status != GREYBOX_HIT) {
      ERR("illegal ma_read request");
      assert(0);
   }

   vector<double> probs;
   int sum = 0;
   for (auto i : ma->data) {
      if (i.second > 0) {
         rets.push_back(i.first);
         probs.push_back((double)i.second / (double)ma->cur_size);
      }
      sum += i.second;
   }

   assert(sum == ma->cur_size);
   assert(rets.size() > 0);

   LOG(LOG_MASK_MA, "read operation will return %ld paths", rets.size());

   executor.branchTableAccessNoCond(cur, rets.size(), states);
   for (int i = 0; i < states.size(); i ++) {
      states[i]->updatePathProb(probs[i]);
      LOG(LOG_MASK_MA, "state[%d] read val %d, prob %f, pathProb updated to %f",
          states[i]->id, rets[i], probs[i], states[i]->getPathProb());
   }
   */

   // Assume the MA table only contains binary values.
   double probTrue  = executor.queryHandler->queryProbByName("ma_true");
   double probFalse = 1 - probTrue;

   rets.push_back(MA_READ_TRUE);
   rets.push_back(MA_READ_FALSE);

   executor.branchTableAccessNoCond(cur, rets.size(), states);
   states[0]->updatePathProb(probTrue);
   states[1]->updatePathProb(probFalse);

   LOG(LOG_MASK_MA, "MA read: true path prob %g", states[0]->getPathProb());
   LOG(LOG_MASK_MA, "MA read: false path prob %g", states[1]->getPathProb());

   return 0;
}
