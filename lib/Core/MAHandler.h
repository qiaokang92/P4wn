#ifndef MA_HANDLER_H
#define MA_HANDLER_H

#include <vector>
#include <string>
#include <map>
#include "klee/Expr.h"
#include "MAHandler.h"

namespace klee {

template<class T> class ref;
class ExecutionState;
class Executor;

class MATable {

public:
   MATable(int nflows, ExecutionState *state);
   MATable(const MATable &);
   ~MATable();

   int ma_insert(int val);

   ExecutionState *state;
   int nflows;
   int cur_size;
   int status;
   // <value, number of entries>
   // sum(data->second) == cur_size
   std::map<int, int> data;
};


class MAHandler {

public:
   Executor &executor;

   MAHandler(Executor  &);
   MAHandler(MAHandler &);
   ~MAHandler();

   // APIs
   int ma_init(ExecutionState &cur);
   int ma_insert(ExecutionState &cur, int val);

   int ma_access(ExecutionState &cur,
                 std::vector<ExecutionState*> &states,
                 std::vector<int> &rets);

   int ma_read(ExecutionState &cur,
                 std::vector<ExecutionState*> &states,
                 std::vector<int> &rets);
private:
};

} /* namespace klee */

#endif /* MA_HANDLER_H */
