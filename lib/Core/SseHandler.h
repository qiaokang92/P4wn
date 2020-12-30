#ifndef SSE_HANDLER_H
#define SSE_HANDLER_H

#include <vector>
#include <string>
#include <map>
#include "klee/Expr.h"

namespace klee {

template<class T> class ref;
class ExecutionState;
class Executor;


class SseHandler {

public:
   SseHandler(Executor* _executor, unsigned _line,
              double _confidence, double _interval,
              unsigned _maxSample,
              unsigned _isEnabled);
   SseHandler(SseHandler &);
   ~SseHandler();
   void run(ExecutionState &initialState);

private:
   Executor *executor;
   unsigned targetLine;
   double confidence;
   double interval;
   unsigned maxSample;
   unsigned isEnabled;

   void sampleOnce(ExecutionState &state);
};

} /* namespace klee */

#endif /* SSE_HANDLER_H */
