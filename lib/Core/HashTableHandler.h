#ifndef HASH_TABLE_HANDLER_H
#define HASH_TABLE_HANDLER_H

#include <vector>
#include <string>
#include <map>
#include "klee/Expr.h"

namespace klee {

template<class T> class ref;
class ExecutionState;
class Executor;


class HashTableHandler {

public:
   Executor &executor;

   HashTableHandler(Executor &);
   HashTableHandler(HashTableHandler &);
   ~HashTableHandler();

   // APIs
   // create a hashtable instance for the current state
   int ht_init(ExecutionState &cur, size_t sz);

   // access the table, will fork several new states from cur
   int ht_access(ExecutionState &cur,
                 std::vector<ExecutionState*> &states,
                 std::vector<int> &rets);

   // check the status of ht_access
   int ht_check(ExecutionState &cur, int &status);

   // read from hash table of cur state
   int ht_read(ExecutionState &cur,
               std::vector<ExecutionState*> &states,
               std::vector<int> &rets);

   // write to the table of cur state
   int ht_write(ExecutionState &cur, int val);

   // return the max possible value in this hash table
   int ht_get_max(ExecutionState &cur);

   // test if the sum of all entries is greater than sum
   int ht_test_sum(ExecutionState &cur, int sum,
                   std::vector<ExecutionState*> &states,
                   std::vector<int> &rets);

   int ht_add_handler(ExecutionState &state);

   // test whether any entry in the ht is larger than val
   int ht_read_larger_than(ExecutionState &state,
                           int val,
                           std::vector<ExecutionState*> &states,
                           std::vector<int> &rets);

private:

};

class HashTable {

public:
   HashTable();
   HashTable(int sz);
   HashTable(const HashTable &);
   ~HashTable();

   //std::string history;
   //std::string writes;
   int status;
   int size;
   int cur_size;

   // distribution of used entries in the table
   std::map<int, double> dist;

   //int key_len = 32; //assuming int, len=32.
   //int val_len = 32; //assuming int, len=32
   //std::vector<ref<Expr>> keys;

   //
   double test_sum_prob(int);

   // add by 1 to the hash table
   double ht_add(int flag);

   double ht_get_prob_larger_than(int val);
   double ht_get_prob_larger_than_after_hit(int val);

   void dump();

   int getMaxValue();

private:

};

} /* namespace klee */

#endif /* HASH_TABLE_HANDLER_H */
