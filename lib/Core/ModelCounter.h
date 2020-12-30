#ifndef MODEL_COUNTER_H
#define MODEL_COUNTER_H

#include <vector>
#include <string>
#include "klee/Expr.h"
#include "klee/Internal/Module/Cell.h"
#include <klee/Constraints.h>

namespace klee {

template<class T> class ref;


class LattECounter {
public:
   double computeProb(ref<Expr>, klee::ConstraintManager consManager);
   double computeProbByOps(std::string ops, std::string prog);
   std::string expr2Str(ref<Expr> e);
private:
   std::string conStrs2Vex(std::vector<std::string> k);
   std::string conManager2Vex(ConstraintManager cons);
};

} /* namespace klee */

#endif /* MODEL_COUNTER_H */
