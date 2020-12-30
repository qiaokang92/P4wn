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
#include "CminHandler.h"

using namespace klee;
using namespace std;
using namespace llvm;
using boost::math::binomial;

namespace klee {
  extern RNG theRNG;
}

CminHandler::CminHandler(Executor &_executor)
: executor(_executor)
{
   printf("new Cmin handler created!\n");
}

CminHandler::CminHandler(CminHandler &_handler)
: executor(_handler.executor)
{

}

CminHandler::~CminHandler()
{

}

CminSketch::CminSketch()
{
}

CminSketch::CminSketch(int _size):
ht1(_size),
ht2(_size),
ht3(_size)
{
   LOG(LOG_MASK_CMIN, "creating an empty cmin, size=%d", _size);
}

CminSketch::CminSketch(const CminSketch &_cmin):
ht1(_cmin.ht1),
ht2(_cmin.ht2),
ht3(_cmin.ht3)
{
   //LOG(LOG_MASK_CMIN, "forking a cmin");
}

CminSketch::~CminSketch()
{
}

int CminHandler::cmin_init(ExecutionState &cur, size_t sz)
{
   LOG(LOG_MASK_CMIN, "allocating cmin, size=%d", (int)sz);
   cur.cmin = new CminSketch(sz);
   return 0;
}

double CminSketch::cmin_add_to_ht(int f1, int f2, int f3)
{
   double p1 = ht1.ht_add(f1);
   double p2 = ht2.ht_add(f2);
   double p3 = ht3.ht_add(f3);

   LOG(LOG_MASK_CMIN, "adding one to cmin, f1=%d, f2=%d, f3=%d,"
       " p1=%g, p2=%g, p3=%g",
       f1, f2, f3, p1, p2, p3);
   return p1 * p2 * p3;
}

void CminSketch::dump()
{
   ht1.dump();
   ht2.dump();
   ht3.dump();
}

int CminHandler::cmin_add(ExecutionState &cur,
                         vector<ExecutionState*> &states,
                         vector<int> &rets)
{
   CminSketch *cmin = cur.cmin;
   int nbranch1 = cmin->ht1.cur_size == 0 ? 1 : 2;
   int nbranch2 = cmin->ht2.cur_size == 0 ? 1 : 2;
   int nbranch3 = cmin->ht3.cur_size == 0 ? 1 : 2;

   // TODO: add support for SSE
   // fork n1*n2*n3 states
   int nstates = nbranch1 * nbranch2 * nbranch3;

   LOG(LOG_MASK_CMIN, "adding 1 to cmin, creating %d x %d x %d = %d paths",
       nbranch1, nbranch2, nbranch3, nstates);

   executor.branchTableAccessNoCond(cur, nstates, states);

   // Update Cmin greybox for each forked state
   int i = 0;
   double prob = 0.0;
   for (int f1 = nbranch1-1; f1 >= 0; f1 --) {
      for (int f2 = nbranch2-1; f2 >= 0; f2 --) {
         for (int f3 = nbranch3-1; f3 >= 0; f3 --) {
            rets.push_back(i);
            prob = states[i]->cmin->cmin_add_to_ht(f1, f2, f3);
            LOG(LOG_MASK_CMIN, "path %d prob is %g", i, prob);
            states[i]->updatePathProb(prob);
            // states[i]->cmin->dump();

            i ++;
         }
      }
   }

   LOG(LOG_MASK_CMIN, "returning %d paths, size of rets=%ld",
       nstates, rets.size());
   return 0;
}


int CminHandler::cmin_larger_than(ExecutionState &cur,
                                  int val,
                                  std::vector<ExecutionState*> &states,
                                  std::vector<int> &rets)
{
   // TODO: add support for SSE

   // to make sure cmin is greater than val, each ht has to be greater than val
   double p1 = cur.cmin->ht1.ht_get_prob_larger_than_after_hit(val);
   double p2 = cur.cmin->ht2.ht_get_prob_larger_than_after_hit(val);
   double p3 = cur.cmin->ht3.ht_get_prob_larger_than_after_hit(val);
   double prob = p1 * p2 * p3;

   LOG(LOG_MASK_CMIN, "state prob=%g, testing if cmin value is larger than %d",
       cur.getPathProb(), val);
   LOG(LOG_MASK_CMIN, "p1=%g, p2=%g, p3=%g, prob=%g", p1, p2, p3, prob);

   // greater than val is impossible, returning one branch
   if (prob == 0.0) {
      states.push_back(&cur);
      rets.push_back(0);
      LOG(LOG_MASK_CMIN, "cannot greater than %d, returning one branch", val);
      return 0;
   }

   // greater than val is possible
   executor.branchTableAccessNoCond(cur, 2, states);

   // branch 1: cmin is greater than val
   rets.push_back(1);
   states[0]->updatePathProb(prob);
   // branch 2: cmin is not greater than val
   rets.push_back(0);
   states[1]->updatePathProb(1 - prob);

   LOG(LOG_MASK_CMIN, "greater than %d: %g, else: %g", val, prob, 1-prob);
   return 0;
}

int CminSketch::getMaxValue()
{
   int max1 = ht1.getMaxValue();
   int max2 = ht2.getMaxValue();
   int max3 = ht3.getMaxValue();

   return MIN(MIN(max1, max2), max3);
}
