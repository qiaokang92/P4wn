#ifndef BF_HANDLER_H
#define BF_HANDLER_H

#include <vector>
#include <string>
#include <map>
#include "klee/Expr.h"

namespace klee {

template<class T> class ref;
class ExecutionState;
class Executor;

class BF {

public:
   BF();
   BF(int sz);
   BF(const BF &);
   ~BF();

   int size;
   int cur_size;

private:
};


class BFHandler {

public:
   Executor &executor;

   BFHandler(Executor  &);
   BFHandler(BFHandler &);
   ~BFHandler();

   // APIs
   // create a bf instance for the current state
   int bf_init(ExecutionState &cur, size_t sz);

   // access the bf, will fork 4 new states from cur
   int bf_access(ExecutionState &cur,
                 std::vector<ExecutionState*> &states,
                 std::vector<int> &rets);

   // read the bf, will fork 2 new states from cur
   // the bf will remain unchanged
   int bf_read(ExecutionState &cur,
               std::vector<ExecutionState*> &states,
               std::vector<int> &rets);
private:
   double get_path_prob(BF *bf, int num_added_bits);
};

} /* namespace klee */

#endif /* BF_HANDLER_H */
