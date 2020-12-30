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
#include "Executor.h"
#include <cmath>
#include <math.h>
#include <vector>
#include <boost/lambda/lambda.hpp>
#include <boost/math/distributions/beta.hpp>
#include "TeleScopeHandler.h"

using namespace klee;
using namespace std;
using namespace llvm;

//==============================================
//============= TeleScopeHandler ===============
//==============================================

TeleScopeHandler::TeleScopeHandler(int n)
{
   numLoop = n;
}

int TeleScopeHandler::ProcessAllPaths(vector<ExecutionState *> states)
{
   LOG(LOG_MASK_TS, "Telescoping done, final result is %g",
       TeleScopeData::finalResult / numLoop);
   return 0;
}

int TeleScopeHandler::ts_init_handler(ExecutionState *state,
                                      int small_thres, int real_thres)
{
   state->tsData.ts_init(state, small_thres, real_thres);
   return 0;
}

int TeleScopeHandler::ts_pkt_handler(ExecutionState *state,
                                      int pktID, int cur_reg)
{
   assert(state == state->tsData.getState());
   state->tsData.ts_pkt(pktID, cur_reg);
   return 0;
}

int TeleScopeHandler::ts_handler(ExecutionState *state, int cur_reg)
{
   assert(state == state->tsData.getState());
   state->tsData.ts_final(cur_reg);
   return 0;
}

int TeleScopeHandler::ts_cmin_pkt_handler(ExecutionState *state,
                                          int pktID)
{
   assert(state == state->tsData.getState());
   int cmin_max = state->cmin->getMaxValue();
   state->tsData.ts_pkt(pktID, cmin_max);
   return 0;
}

int TeleScopeHandler::ts_cmin_handler(ExecutionState *state)
{
   assert(state == state->tsData.getState());
   int cmin_max = state->cmin->getMaxValue();
   state->tsData.ts_final(cmin_max);
   return 0;
}


//==============================================
//============= TeleScopeData ==================
//==============================================

double TeleScopeData::finalResult = 0.0;

TeleScopeData::TeleScopeData():
   reg(0),
   smallThres(0),
   realThres(0),
   pktProbs(0)
{}

TeleScopeData::TeleScopeData(const TeleScopeData &_tsData):
   state(_tsData.state),
   reg(_tsData.reg),
   smallThres(_tsData.smallThres),
   realThres(_tsData.realThres),
   perPktProbs(_tsData.perPktProbs),
   pktProbs(_tsData.pktProbs),
   pktRegs(_tsData.pktRegs)
{

}

void TeleScopeData::dump()
{
   uint32_t i;
   LOG(LOG_MASK_TS, "state %d has %ld pkt probs", state->id, perPktProbs.size());
   for (i = 0; i < pktProbs.size(); i ++) {
      LOG(LOG_MASK_TS, "pkt[%d] prob=%g", i, perPktProbs[i])
   }

   LOG(LOG_MASK_TS, "state %d has %ld pkt regs", state->id, pktRegs.size());
   for (i = 0; i < pktRegs.size(); i ++) {
      LOG(LOG_MASK_TS, "pkt[%d] reg=%d", i, pktRegs[i])
   }
}

int TeleScopeData::ts_init(ExecutionState *s, int small_thres, int real_thres)
{
   LOG(LOG_MASK_TS, "Initing TsData, small thres=%d, real thres=%d",
       small_thres, real_thres);
   state = s;
   smallThres = small_thres;
   realThres  = real_thres;
   return 0;
}

int TeleScopeData::ts_pkt(int pktID, int cur_reg)
{
   //LOG(LOG_MASK_TS, "Updating TsData for pkt=%d, pathProb=%g, reg: %d->%d",
   //    pktID, state->getPathProb(), reg, cur_reg);

   if (int(pktRegs.size()) != pktID) {
      WARN("pktregs size=%ld, pktID=%d\n", pktRegs.size(), pktID);
      assert(0);
   }
   assert(int(pktRegs.size()) == pktID);
   assert(int(perPktProbs.size()) == pktID);
   assert(int(pktProbs.size()) == pktID);

   reg = cur_reg;

   // TODO; Update per-packet constraints and probs
   double pathProb = state->getPathProb();
   pktProbs.push_back(pathProb);
   if (pktID == 0) {
      perPktProbs.push_back(pathProb);
   } else {
      double lastProb = pktProbs[pktID - 1];
      perPktProbs.push_back(pathProb / lastProb);
   }
   pktRegs.push_back(cur_reg);

   return 0;
}

bool AlmostEqual2sComplement(float A, float B, int maxUlps)
{
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
    int aInt = *(int*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}

static int checkVectorSame(vector<double> v)
{
   int ret = 0;
   double first = v[0];
   for (auto val: v) {
      if (!AlmostEqual2sComplement(val, first, 1)) {
         ret = 1;
      }
   }
   if (ret == 0) {
      return 0;
   }

   assert(ret == 1);
   double second = v[1];
   for (uint32_t i = 2; i < v.size(); i ++) {
      if (!AlmostEqual2sComplement(v[i], second, 1)) {
         ret = 2;
      }
   }
   return ret;
}

TeleScopeData::PeriodicityType TeleScopeData::ts_periodicity()
{
   // TODO: for now, we only distinguish two types by comparing
   // TODO: Also check per-packet constraint for periodicity

   int ret = checkVectorSame(perPktProbs);
   if (ret == 0) {
      return REPEAT_ALL;
   } else if (ret == 1) {
      return REPEAT_FROM_SECOND;
   } else {
      return NO_PERIODICITY;
   }
}

int TeleScopeData::ts_final(int cur_reg)
{
   assert(reg == cur_reg);
   //LOG(LOG_MASK_TS, "Telescoping state %d with reg=%d, smallThres=%d, real=%d",
   //    state->id, reg, smallThres, realThres);

   // check if this state is telescopable
   if (reg == smallThres) {
      LOG(LOG_MASK_TS, "state %d (cur_reg = smallThres = %d) "
          "seems telescopable", state->id, reg);
      dump();

      // infer the final prob result
      double result = 0.0;
      TeleScopeData::PeriodicityType ptype = ts_periodicity();

      if (ptype == NO_PERIODICITY) {
         LOG(LOG_MASK_TS, "state %d turns out not telescopable", state->id);
      } else {
         if (ptype == REPEAT_ALL) {
            result = pow(perPktProbs[0], realThres);
         } else if (ptype == REPEAT_FROM_SECOND) {
            result = perPktProbs[0] * pow(perPktProbs[1], realThres-1);
         }
         LOG(LOG_MASK_TS, "telescoping state %d inferred prob of reg==%d is %g",
             state->id, realThres, result);
         finalResult += result;
      }
   } else {
      //LOG(LOG_MASK_TS, "state %d (cur_reg=%d smallThres=%d) "
      //    "seems not telescopable", state->id, cur_reg, smallThres);
   }

   return 0;
}
