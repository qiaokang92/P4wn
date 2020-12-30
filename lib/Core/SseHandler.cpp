#include "HashTableHandler.h"
#include "SseHandler.h"
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

#include <boost/lambda/lambda.hpp>
#include <boost/math/distributions/beta.hpp>

using namespace boost::lambda;
using namespace boost::math;

using namespace klee;
using namespace std;
using namespace llvm;

SseHandler::SseHandler(Executor* _executor, unsigned _line,
                       double _confidence, double _interval,
                       unsigned _maxSample,
                       unsigned _isEnabled):
executor(_executor),
targetLine(_line),
confidence(_confidence),
interval(_interval),
maxSample(_maxSample),
isEnabled(_isEnabled)
{
   LOG(LOG_MASK_SSE, "new sse handler created, line=%u, confi=%f, interval=%f",
       targetLine, confidence, interval);
}

SseHandler::SseHandler(SseHandler &_handler):
   executor(_handler.executor),
   targetLine(_handler.targetLine),
   confidence(_handler.confidence),
   interval(_handler.interval),
   maxSample(_handler.maxSample)
{

}

SseHandler::~SseHandler()
{

}

void SseHandler::sampleOnce(ExecutionState &state)
{
   // keep running this state, do not schedule any other state
   // TODO: avoid forking new states.
   state.isSample = true;
   state.isSampleDone = false;

   while (!state.isSampleDone) {
      //LOG(LOG_MASK_SSE, "to run an ins = %f", state.getPathProb());

      KInstruction *ki = state.pc;

      executor->stepInstruction(state);
      executor->executeInstruction(state, ki);

      //LOG(LOG_MASK_SSE, "finish an ins = %f", state.getPathProb());
   }
}

void SseHandler::run(ExecutionState &initialState)
{
   vector<unsigned> res;
   LOG(LOG_MASK_SSE, "SSE starts to take max %d samples", maxSample);

   // Beta(a,b) distribution
   // unsigned a = 1;
   // unsigned b = 1;
   double a = 1;
   double b = 1;

   static double explored = 0.0;

   for (unsigned i=0; i < maxSample; i ++) {
      LOG(LOG_MASK_SSE, "start taking the %dth sample", i);

      // make a copy of the initial state state
      ExecutionState *nextState = new ExecutionState(initialState);
      sampleOnce(*nextState);

      LOG(LOG_MASK_SSE, "sample %d trigger target event %d times",
          i, nextState->sampleRes);
      res.push_back(nextState->sampleRes);

      if (nextState->sampleRes > 0) {
         a += 1;
      } else {
         b += 1;
      }

      double esti = a / (a + b);

      double left = esti - interval < 0? 0 : esti - interval;
      double right = esti + interval >1? 1 : esti + interval;

      double p = ibeta(a, b, right) - ibeta(a, b, left);

      LOG(LOG_MASK_SSE, "Beta(%g, %g), left=%g, right=%g, p=%g",
          a, b, left, right, p);

      // If Informed Sampling is enabled, we relax the confidence level
      // based on the explored space.
      if (isEnabled) {
         explored += nextState->getPathProb();
         confidence = (confidence - explored) / (1.0 - explored);
         LOG(LOG_MASK_SSE, "pathprob=%g, explored updated to %g, confidence "
             "level updated to %g", nextState->getPathProb(), explored, confidence);
      }

      delete nextState;

      if (p >= confidence) {
         LOG(LOG_MASK_SSE, "satisfied the confidence! p=%g, mu=%g",
             p, esti);
         break;
      } else {
         LOG(LOG_MASK_SSE, "not satisfying the confidence! p=%g, mu=%g",
             p, esti);
      }
   }

   /*
   for (int i=0; i < res.size(); i++) {
      LOG(LOG_MASK_SSE, "sample %d trigger target event %d times",
          i, res[i]);
   }
   */

   LOG(LOG_MASK_SSE, "sampled %ld states, done", res.size());
}
