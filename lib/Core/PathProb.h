#ifndef PATH_PROB_H
#define PATH_PROB_H

#include <vector>
#include <string>
#include <map>

namespace klee {

class BranchProb;
class LattECounter;
class Executor;
class ExecutionState;
class Expr;
template<class T> class ref;

class AllPathProbs {
public:
   AllPathProbs(int numloop, std::string progname, int progNo,
                int prof, double delta);

   void processAccumPkt();
   void processRanking();

   void dumpFinalRanking();
   void dumpPerPktRanking();

   bool isStable(std::string ops);

   std::vector<BranchProb *> pbs;

private:
   typedef std::pair<std::string, double> block_t ;
   typedef std::vector<block_t> rank_t;

   double getProbFromName(rank_t r, std::string name);
   int numLargeOfTwoRanks(rank_t r1, rank_t r2);
   int numDiffOfTwoRanks(rank_t r1, rank_t r2);
   static bool compareBlock(block_t pair1, block_t pair2);
   bool isStableDelta();
   bool isStableRanking();

   std::vector<rank_t> rank;
   uint32_t numLoop;
   int profile;
   int progNum;
   std::string progName;
   std::string dumpPath;
   double delta;
};

class BranchProb {
public:
   static int count;
   int depth;
   int id;
   unsigned line;
   double ifAccumProb = 0;
   double elseAccumProb = 0;

   std::map<int, double> ifAccumPkt;
   std::map<int, double> elseAccumPkt;

   BranchProb(int dep, unsigned l) {
      depth = dep;
      id = count;
      count ++;
      line = l;
   }
};

class QueryHandler {
public:

   QueryHandler(unsigned number, unsigned traceEnabled,
                unsigned maxNumPkt, int profile, Executor *executor);
   QueryHandler(QueryHandler &) {};
   ~QueryHandler();

   int handleProbPath(std::string expr,
                      int value,
                      ExecutionState &cur,
                      std::vector<ExecutionState*> &states,
                      std::vector<int> &rets);

   double queryProbByLine(int line, ref<Expr> cond);
   double queryProbByName(std::string name);

   std::string getProgNameFromNumer(unsigned number);
   double queryProbTableMiss();
   unsigned queryTime;
   int numQueries;
   int numQueriesNotFound;
   Executor *executor;

private:
   double queryAdminByLine(int line, ref<Expr> cond);
   double queryTraceByLine(int line, ref<Expr> cond);

   double queryAdminByName(std::string name);
   double queryTraceByName(std::string name);

   // utils
   std::string getOpsFromLine(int line, ref<Expr> cond);
   std::string getOpsFromName(std::string name);
   std::string getTraceName();
   std::string progName;

   unsigned queryTraceEnabled;
   std::map<int, double> line2prob;
   std::map<std::string, double> name2prob;
   unsigned numPkt;
   unsigned progNum;

   int profile;
   LattECounter *modelCounter;
};

}


#endif /* PATH_PROB_H */
