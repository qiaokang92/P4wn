#ifndef TELE_SCOPE_HANDLER_H
#define TELE_SCOPE_HANDLER_H

#include <vector>
#include <string>
#include <map>
#include "klee/Expr.h"

namespace klee {

template<class T> class ref;
class ExecutionState;
class Executor;

class TeleScopeHandler {

public:
   TeleScopeHandler(int n);
   ~TeleScopeHandler() {};
   TeleScopeHandler(const TeleScopeHandler &) {};

   int ProcessAllPaths(std::vector<ExecutionState *> states);

   // counter
   int ts_init_handler(ExecutionState *state, int small_thres, int real_thres);
   int ts_pkt_handler(ExecutionState *state, int pktID, int reg);
   int ts_handler(ExecutionState *state, int reg);

   // cmin
   int ts_cmin_pkt_handler(ExecutionState *state, int pktID);
   int ts_cmin_handler(ExecutionState *state);

private:
   int numLoop;

};

class TeleScopeData {
public:
   TeleScopeData();
   TeleScopeData(const TeleScopeData &);
   ~TeleScopeData() {};

   void dump();

   int ts_init(ExecutionState *s, int small, int real);

   // counter
   int ts_pkt(int pktID, int cur_reg);
   int ts_final(int cur_reg);

   void updateState(ExecutionState *s) {state = s;}
   ExecutionState *getState() {return state;}

   enum PeriodicityType
   {
      REPEAT_ALL,
      REPEAT_FROM_SECOND,
      NO_PERIODICITY
   };
   PeriodicityType ts_periodicity();

   static double finalResult;

private:
   ExecutionState *state;
   int reg;
   int smallThres;
   int realThres;

   // per-packet constraints collected by telescope_pkt
   // vector<...>
   std::vector<double> perPktProbs;
   std::vector<double> pktProbs;
   std::vector<int> pktRegs;
};

} /* namespace klee */

#endif /* TELE_SCOPE_HANDLER_H */
