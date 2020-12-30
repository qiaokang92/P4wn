#ifndef CMIN_HANDLER_H
#define CMIN_HANDLER_H

#include <vector>
#include <string>
#include <map>
#include "klee/Expr.h"
#include "HashTableHandler.h"

namespace klee {

template<class T> class ref;
class ExecutionState;
class Executor;

class CminSketch {

public:
   CminSketch();
   CminSketch(int sz);
   CminSketch(const CminSketch &);
   ~CminSketch();

   double cmin_add_to_ht(int f1, int f2, int f3);
   void dump();

   // internal expression of the Cmin sketch: 3 hash tables
   HashTable ht1;
   HashTable ht2;
   HashTable ht3;

   int getMaxValue();

private:
};


class CminHandler {

public:
   Executor &executor;

   CminHandler(Executor  &);
   CminHandler(CminHandler &);
   ~CminHandler();

   // APIs
   // create a Cmin instance for the current state
   int cmin_init(ExecutionState &cur, size_t sz);

   // add by one to the Sketch
   int cmin_add(ExecutionState &cur,
                std::vector<ExecutionState*> &states,
                std::vector<int> &rets);

   // add by one to the Sketch
   int cmin_larger_than(ExecutionState &cur,
                        int val,
                        std::vector<ExecutionState*> &states,
                        std::vector<int> &rets);
private:
};

} /* namespace klee */

#endif /* CMIN_HANDLER_H */
