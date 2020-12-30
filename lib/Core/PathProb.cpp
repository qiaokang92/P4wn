#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "PathProb.h"
#include "helper.h"
#include <algorithm>    // std::sort
#include "ModelCounter.h"
#include <chrono>
#include "klee/ExecutionState.h"
#include "klee/Expr.h"
#include "Executor.h"

using namespace klee;
using namespace std;

int BranchProb::count = 0;

static string getStdoutFromCommand(string cmd)
{
   string data;
   FILE * stream;
   const int max_buffer = 4096;
   char buffer[max_buffer];
   cmd.append(" 2>&1");

   stream = popen(cmd.c_str(), "r");
   if (stream) {
      while (!feof(stream))
         if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
      pclose(stream);
   }
   return data;
}

static double getLastNumber(string output)
{
   std::stringstream ss(output);
   std::string to;
   std::string num;
   double ret;

   while (std::getline(ss, to, '\n')){
      num = to;
   }
   ret = stof(num);
   return ret;
}

QueryHandler::QueryHandler(unsigned number, unsigned traceEnabled,
                           unsigned maxNumPkt, int _profile,
                           Executor *_executor)
{
   progNum  = number;
   queryTime = 0.0;
   progName = getProgNameFromNumer(number);
   queryTraceEnabled = traceEnabled ? 1 : 0;
   numPkt = maxNumPkt;
   profile = _profile;
   numQueries = 0;
   numQueriesNotFound = 0;
   modelCounter = new LattECounter();
   executor = _executor;

   LOG(-1, "creating query handler, prog=%s, profile=%d, query trace %s",
       progName.c_str(), profile, queryTraceEnabled ? "enabled" : "disabled");
}

QueryHandler::~QueryHandler()
{
   delete modelCounter;
   return;
}

double QueryHandler::queryAdminByName(string name)
{
   double ret;

   // search the query history
   auto it = name2prob.find(name);

   // prob found, don't have to query the trace
   if (it != name2prob.end()) {
      return it->second;
   }

   numQueriesNotFound += 1;
   string ops = getOpsFromName(name);
   ret = modelCounter->computeProbByOps(ops,
                            std::to_string(progNum) + "-" + progName);

   LOG(LOG_MASK_QUERY, "query admin for %s name=%s, ops=%s prob=%g, numQueriesNotFound=%d",
       progName.c_str(), name.c_str(), ops.c_str(), ret, numQueriesNotFound);

   // write to query history and return
   name2prob[name] = ret;
   return ret;
}

double QueryHandler::queryAdminByLine(int line, ref<Expr> cond)
{
   LOG(LOG_MASK_QUERY, "querying admin for %s line=%d", progName.c_str(), line);

   (*cond.get()).dump();

   // search the query history
   auto it = line2prob.find(line);

   // prob found, don't have to query the trace
   if (it != line2prob.end()) {
      return it->second;
   }

   numQueriesNotFound += 1;

   string ops = getOpsFromLine(line, cond);

   LOG(LOG_MASK_QUERY, "generating MC query for %s ops=%s, line=%d, numQueriesNotFound=%d",
       progName.c_str(), ops.c_str(), line, numQueriesNotFound);

   double ret = modelCounter->computeProbByOps(ops,
                                  std::to_string(progNum) + "-" + progName);

   // write to query history and return
   line2prob[line] = ret;
   return ret;
}

// TODO: add more programs
string QueryHandler::getTraceName()
{
   if (progName == "poise") {
      return "poise";
   } else if (progName == "netwarden"  ||
              progName == "nethcf") {
      // Sensitivity experiment for NetWarden: different traces
      if (profile == 1) {
         return "netwarden1";
      } else if (profile == 2) {
         return "netwarden2";
      } else if (profile == 3) {
         return "netwarden3";
      } else {
         assert(0);
      }
   } else if (progName == "blink"      ||
              progName == "starflow"   ||
              progName == "netcache"   ||
              progName == "p40f"       ||
              progName == "lb"         ||
              progName == "flowlet"    ||
              progName == "nat"        ||
              progName == "acl"        ||
              progName == "counter"    ||
              progName == "test"       ||
              progName == "vera"       ||
              progName == "rwnd") {

      // Sensitivity experiment for starflow, rwnd, p40f, flowlet
      if (profile == 1) {
         return "equinix-nyc.dirA.20190117-130000.UTC.anon";
      } else if (profile == 2) {
         return "equinix-nyc.dirA.20180315-130000.UTC.anon";
      } else if (profile == 3) {
         return "equinix-chicago.dirA.20160218-130000.UTC.anon";
      } else {
         assert(0);
      }
   } else {
      ERR("no trace for program=%s", progName.c_str());
      assert(0);
      return "";
   }
}

// TODO: add more programs
string QueryHandler::getOpsFromName(string name)
{
   if (name == "ma_true") {
      if (progName == "poise") {
         return "ctx_deny";
      } else if (progName == "netwarden") {
         return "nw_to:200";
      } else {
         goto out;
      }
   } else {
      goto out;
   }

out:
   LOG(-1, "cannot find ops from name=%s for prog=%s, returning name",
       name.c_str(), progName.c_str());

   return name;
}

string QueryHandler::getOpsFromLine(int line, ref<Expr> cond)
{
   LOG(-1, "prog=%s, getting ops from line=%d", progName.c_str(), line);
   ref<Expr> r = cond;

   // parse condition to get ops
   /*
   if (progName == "poise" ||
       progName == "blink" ||
       progName == "starflow" ||
       progName == "netcache"
      ) {
   */
   while (r->getWidth() != 8) {
      r = cast<CmpExpr>(r)->right;
      r->dump();
   }

   LOG(-1, "expr kind = %d", r->getKind());
   cast<ReadExpr>(r)->index->dump();
   string name = cast<ReadExpr>(r)->updates.root->name;
   LOG(-1, "name = %s", name.c_str());

   return name;

   // legacy code: fixed mapping from line number to ops
   /*
   if (progName == "poise") {
      if (line == 55) {
         return "ctx";
      } else if (line == 57) {
         return "ctx_deny";
      } else {
         goto err;
      }
   } else if (progName == "blink") {
      if (line == 85) {
         return "not_syn_ack_only";
      } else if (line == 88) {
         return "overall_to:80";    // timeout
      } else if (line == 98) {
         return "fin";    // fin
      } else if (line == 104) {
         return "rtx_before_fin";
      } else if (line == 110) {
         return "rtx";
      } else if (line == 124) {
         return "is_flow_timeout";
      }

      else {
         goto err;
      }
   } else if (progName == "starflow") {
      if (line == 36) {
         return "ipv4";
      } else {
         return "half";
      }
   } else if (progName == "netcache") {
      if (line == 54 || line == 64) {
         return "nc_exist";
      } else if (line == 56 || line == 66) {
         return "nc_read";
      } else if (line == 76) {
         return "nc_exist_read";
      } else {
         goto err;
      }
   } else if (progName == "rwnd") {
      if (line == 48) {
         return "dupack";
      } else if (line == 58) {
         return "half";
      } else  {
         goto err;
      }
   } else if (progName == "p40f") {
      if (line == 41) {
         return "syn_only";
      } else if (line == 56) {
         return "http";
      } else {
         goto err;
      }
   } else if (progName == "flowlet") {
      if (line == 31) {
         // query the ratio of IPD>5ms
         // Note: the original flowlet program uses 50ms, but it's too large,
         // there is no 50ms IPD in the CAIDA trace.
         return "perflow_to:5000000";
      } else if (line == 39) {
         return "half";
      }
   } else if (progName == "nethcf") {
      return "half_simple";
   } else if (progName == "lb") {
      return "half";
   } else if (progName == "counter") {
      return "half";
   } else if (progName == "test") {
      return "half";
   } else {
      goto err;
   }

err:
   ERR("cannot find ops from line=%d for prog=%s", line, progName.c_str());
   assert(0);
   return "";
   */
}

// TODO: add more programs
string QueryHandler::getProgNameFromNumer(unsigned num)
{
   if (num == 0) {
      return "poise";
   } else if (num == 1) {
      return "netwarden";
   } else if (num == 2) {
      return "blink";
   } else if (num == 3) {
      return "starflow";
   } else if (num == 4) {
      return "netcache";
   } else if (num == 5) {
      return "rwnd";
   } else if (num == 6) {
      return "p40f";
   } else if (num == 7) {
      return "lb";
   } else if (num == 8) {
      return "flowlet";
   } else if (num == 9) {
      return "nat";
   } else if (num == 10) {
      return "acl";
   } else if (num == 11) {
      return "nethcf";
   } else if (num == 12) {
      return "counter";
   } else if (num == 99) {
      return "test";
   } else if (num == 98) {
      return "vera";
   }
   else {
      ERR("unkown program number=%d", num);
      assert(0);
      return "";
   }
}

double QueryHandler::queryTraceByLine(int line, ref<Expr> cond)
{
   double ret = 0.0;
   LOG(LOG_MASK_QUERY, "querying trace for %s line=%d", progName.c_str(), line);

   // search the query history
   auto it = line2prob.find(line);

   // prob found, don't have to query the trace
   if (it != line2prob.end()) {
      return it->second;
   }

   numQueriesNotFound += 1;

   // Program-specific parameters
   string trace_name = getTraceName();
   string ops        = getOpsFromLine(line, cond);

   LOG(LOG_MASK_QUERY, "prob for %s at line=%d not found, generating query, "
       "ops=%s, trace_name=%s",
       progName.c_str(), line, ops.c_str(), trace_name.c_str());

   // for "half", let's query the trace
   // for "half-simple", let's return directly
   if (ops == "half_simple") {
      ret = 0.5;
   }

   // For testing
   /*
   if (progName == "test") {
      ret = 0.001;
   }
   */

   // Hard-coded known queries
   // e.g., missing table entries
   /*
   if (ops == "half") {
      ret = 0.5;
   }
   */

   // sensitivity experiment for NetCache: different hit rate
   if (ops == "nc_exist") {
      if (profile == 1) {
         ret = 0.5;
      } else if (profile == 2) {
         ret = 0.4;
      } else if (profile == 3) {
         ret = 0.6;
      } else {
         assert(0);
      }
   }
   if (ops == "nc_read") {
      ret = 0.9;
   }

   if (ops == "nc_exist_read") {
      ret = 0.45;
   }

   // Some best guesses for Blink
   if (ops == "overall_to:80") {
      ret = 0.01;
   }
   if (ops == "rtx_before_fin") {
      ret = 0.000001;
   }
   if (ops == "is_flow_timeout") {
      ret = 0.1;
   }
   if (ops == "not_syn_ack_only") {
      ret = 0.9;
   }

   // obtained from python
   // Sensitivity experiment for Blink: rtx from different traces
   /*
   if (ops == "rtx") {
      if (profile == 1) {
         // ./query.py . equinix-nyc.dirA.20190117-130000.UTC.anon rtx 100000
         ret = 0.00067;
      } else if (profile == 2) {
         // ./query.py . equinix-nyc.dirA.20180315-130000.UTC.anon rtx 100000
         ret = 8.32659275824e-05;
      } else if (profile == 3) {
         // ./query.py . equinix-chicago.dirA.20160218-130000.UTC.anon rtx 100000
         ret = 0.00035;
      } else {
         assert(0);
      }
   }
   */

   if (ret == 0.0) {
   // Fixed parameters
      string trace_prog   = "query.py";
      string trace_folder = "/home/qiaokang/dpattacks/tools/klee-prob/examples/trace/";

      // Get the final query command
      string cmd = "python " + trace_folder + trace_prog + " " + trace_folder + \
                   " " + trace_name + " " + ops + " " + to_string(numPkt);

      // Invoke the Python query program
      string output = getStdoutFromCommand(cmd);
      LOG(LOG_MASK_QUERY, "retrieving prob frm cmd output: %s", output.c_str());

      // fetch the prob from Python program stdout
      ret = getLastNumber(output);
      LOG(LOG_MASK_QUERY, "queried prob is %f", ret);
   }

   // write to query history and return
   line2prob[line] = ret;
   // assert(ret > 0);
   return ret;
}

double QueryHandler::queryTraceByName(string name)
{
   double ret;
   LOG(LOG_MASK_QUERY, "querying trace for %s name=%s",
       progName.c_str(), name.c_str());

   // search the query history
   auto it = name2prob.find(name);

   // prob found, don't have to query the trace
   if (it != name2prob.end()) {
      return it->second;
   }

   numQueriesNotFound += 1;

   LOG(LOG_MASK_QUERY, "prob for %s, name=%s not found, generating query..",
       progName.c_str(), name.c_str());

   // Program-specific parameters
   string trace_name = getTraceName();
   string ops        = getOpsFromName(name);

   // Fixed parameters
   string trace_prog   = "query.py";
   string trace_folder = "/home/qiaokang/dpattacks/tools/klee-prob/examples/trace/";

   // Get the final query command
   string cmd = "python " + trace_folder + trace_prog + " " + trace_folder + \
                " " + trace_name + " " + ops + " " + to_string(numPkt);

   // Invoke the Python query program
   string output = getStdoutFromCommand(cmd);
   LOG(LOG_MASK_QUERY, "retrieving prob frm cmd output: %s", output.c_str());

   // fetch the prob from Python program stdout
   ret = getLastNumber(output);
   LOG(LOG_MASK_QUERY, "queried result is %f", ret);

   // write to query history and return
   name2prob[name] = ret;
   assert(ret > 0);
   return ret;
}

double QueryHandler::queryProbByLine(int line, ref<Expr> cond)
{
   double ret;
   auto t1 = std::chrono::high_resolution_clock::now();

   if (queryTraceEnabled) {
      ret = queryTraceByLine(line, cond);
   } else {
      ret = queryAdminByLine(line, cond);
   }

   auto t2 = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

   queryTime += duration;
   numQueries += 1;
   LOG(-1, "query line %d spent time %ld us, queryTime %u",
       line, duration, queryTime);

   return ret;
}

double QueryHandler::queryProbByName(string name)
{
   double ret;
   auto t1 = std::chrono::high_resolution_clock::now();

   if (queryTraceEnabled) {
      ret = queryTraceByName(name);
   } else {
      ret = queryAdminByName(name);
   }

   auto t2 = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

   queryTime += duration;
   numQueries += 1;
   LOG(-1, "query name %s spent time %ld us, queryTime %u",
       name.c_str(), duration, queryTime);

   return ret;
}

double QueryHandler::queryProbTableMiss()
{
   double ret;
   if (queryTraceEnabled) {
      unsigned nflows = queryProbByName("nflows");
      unsigned npkts  = queryProbByName("ntcp");
      unsigned npkts_per_flow = npkts / nflows;
      double probMiss = 1.0 / (double) npkts_per_flow;
      ret = probMiss;
   } else {
      auto t1 = std::chrono::high_resolution_clock::now();
      ret = queryAdminByName("tablemiss");
      auto t2 = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
      queryTime += duration;
      numQueries += 1;
      LOG(-1, "query name %s spent time %ld us, queryTime %u",
          "tablemiss", duration, queryTime);
   }

   return ret;
}

int QueryHandler::handleProbPath(string expr,
                       int value,
                       ExecutionState &cur,
                       std::vector<ExecutionState*> &states,
                       std::vector<int> &rets)
{
   rets.push_back(true);
   rets.push_back(false);

   LOG(-1, "expr=%s, value=%d", expr.c_str(), value);

   executor->branchTableAccessNoCond(cur, rets.size(), states);
   states[0]->updatePathProb(0.5);
   states[1]->updatePathProb(0.5);

   return 0;
}

// ============================================
// ============ AllPathProbs =================
// ============================================

AllPathProbs::AllPathProbs(int numloop, std::string progname,
                           int progNo, int prof, double _delta):
   numLoop(numloop),
   profile(prof),
   progNum(progNo),
   progName(progname),
   delta(_delta)
{
   dumpPath = "./profile" + std::to_string(profile) + "/"
               + std::to_string(progNum) + "-" + progName + ".result";
}

void AllPathProbs::dumpFinalRanking()
{
   std::stringstream ss;
   std::vector<std::vector<std::pair<std::string, double>>> rank;
   int i = 0;
   for (auto p: pbs) {
      if (i++ == 0) {
         continue;
      }
      double ifprob = p->ifAccumProb / (double) numLoop;
      if (ifprob <= 1.0) {
         ss << ifprob << " " << p->line <<"-if " << progName << std::endl;
      }

      double elseprob = p->elseAccumProb / (double) numLoop;
      if (elseprob <= 1.0) {
         ss << elseprob << " " << p->line << "-else " << progName << std::endl;
      }
   }

   std::ofstream output_file;
   output_file.open(dumpPath);

   if (!output_file.is_open()) {
      WARN("failed to open %s, printing to std", dumpPath.c_str());
      printf("%s\n", ss.str().c_str());
   } else {
      LOG(-1, "storing results in %s file, numloop=%u", dumpPath.c_str(),
          numLoop);
      output_file << ss.rdbuf();
   }
}

void AllPathProbs::processAccumPkt()
{
   uint32_t i;
   for (auto p: pbs) {
      //for (i = 1; i < p->ifAccumPkt.size(); i ++) {
      if (p->ifAccumPkt[0] == 0) {
         p->ifAccumPkt[0] = 0;
      }

      if (p->elseAccumPkt[0] == 0) {
         p->elseAccumPkt[0] = 0;
      }

      for (i = 1; i < numLoop; i ++) {
         p->ifAccumPkt[i] += p->ifAccumPkt[i - 1];
      }
      assert(numLoop == p->ifAccumPkt.size());

      for (i = 1; i < p->ifAccumPkt.size(); i ++) {
         p->ifAccumPkt[i] /= (i + 1);
      }

      //for (i = 1; i < p->elseAccumPkt.size(); i ++) {
      for (i = 1; i < numLoop; i ++) {
         p->elseAccumPkt[i] += p->elseAccumPkt[i - 1];
      }
      assert(numLoop == p->elseAccumPkt.size());

      for (i = 1; i < p->elseAccumPkt.size(); i ++) {
         p->elseAccumPkt[i] /= (i + 1);
      }
   }
}

extern bool AlmostEqual2sComplement(float A, float B, int maxUlps);

bool AllPathProbs::compareBlock(std::pair<std::string, double> pair1,
                                std::pair<std::string, double> pair2)
{
   if (!AlmostEqual2sComplement(pair1.second, pair2.second, 1)){
      return (pair1.second < pair2.second);
   } else {
      return (pair1.first < pair2.first);
   }
}

void AllPathProbs::processRanking()
{
   // rank all nodes per iteration
   for (int i = 0; i < numLoop; i ++) {
      std::vector<std::pair<std::string, double>> rank_iter;

      int j = 0;
      for (auto p: pbs) {
         // ignore the for loop branch
         if (j++ == 0) {
            continue;
         }
         //The loog branch in Blink is the second one
         if (progName == "blink" && p->line == 75) {
            continue;
         }
         std::string name_if = std::to_string(p->line) + "-if";
         std::string name_else = std::to_string(p->line) + "-else";
         rank_iter.push_back(std::make_pair(name_if, p->ifAccumPkt[i]));
         rank_iter.push_back(std::make_pair(name_else, p->elseAccumPkt[i]));
      }

      std::sort(rank_iter.begin(), rank_iter.end(), compareBlock);
      rank.push_back(rank_iter);
   }
}

void AllPathProbs::dumpPerPktRanking()
{
   for (uint32_t i = 0; i < rank.size(); i ++) {
      printf("==== Iteration %d ====\n", i);
      for (auto block: rank[i]) {
         printf("%s: %g\n", block.first.c_str(), block.second);
      }
   }
}

int AllPathProbs::numDiffOfTwoRanks(rank_t r1, rank_t r2)
{
   uint32_t i;
   int delta = 0;
   assert(r1.size() == r2.size());
   for (i = 0; i < r1.size(); i ++) {
      if (r1[i].first != r2[i].first) {
         delta += 1;
      }
   }
   return delta;
}

double AllPathProbs::getProbFromName(rank_t r, std::string name)
{
   for (auto b: r) {
      if (b.first == name) {
         return b.second;
      }
   }
   return -1;
}

int AllPathProbs::numLargeOfTwoRanks(rank_t r1, rank_t r2)
{
   int ret = 0;
   double max_delta = 0;
   for (auto b1: r1) {
      double p1 = b1.second;
      double p2 = getProbFromName(r2, b1.first);
      // printf("looking for %s prob in r2, p2=%g\n", b1.first.c_str(), p2);
      assert(p2 >= 0);

      if (abs(p1 - p2) > delta) {
         ret += 1;
      }

      max_delta = abs(p1 - p2) > max_delta ? abs(p1 - p2) : max_delta;
   }
   printf("max delta is %g\n", max_delta);
   return ret;
}

bool AllPathProbs::isStableDelta()
{
   int num_large = 0;
   int num_stable = 0;

   for (uint32_t i = 0; i < rank.size() - 1; i ++) {
      num_large = numLargeOfTwoRanks(rank[i], rank[i+1]);
      printf("rank[%d] --> rank[%d], numLarge is %d\n", i, i + 1, num_large);
      if (num_large == 0) {
         num_stable += 1;
      }
   }

   return (num_stable >= 1);
}

bool AllPathProbs::isStableRanking()
{
   uint32_t i;
   int delta = 0;
   int num_stable = 0;
   for (i = 0; i < rank.size() - 1; i ++) {
      delta = numDiffOfTwoRanks(rank[i], rank[i+1]);
      printf("rank[%d] --> rank[%d], delta is %d\n", i, i + 1, delta);
      if (delta == 0) {
         num_stable += 1;
      }
   }

   return (num_stable >= 1);
}

bool AllPathProbs::isStable(string ops)
{
   printf("checking stability of %lu ranks, ops=%s, delta=%g\n",
          rank.size(), ops.c_str(), delta);
   if (ops == "ranking") {
      return isStableRanking();
   } else {
      return isStableDelta();
   }
}
