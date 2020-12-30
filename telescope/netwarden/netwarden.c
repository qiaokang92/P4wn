#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE  128
#define NUM_LOOP   5
#define CMIN_THRES 5
#define REAL_THRES 20
// =======================================
// ======== switch control plane =========
// =======================================
int cp_ma_table_insert(int val)
{
   // this operation inserts one entry to the MA table
   // following klee_access_ma calls should see a different MA table
   klee_ma_insert(val);
   return 0;
}

// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   int i;
   int ret;

   // int ipd[NUM_LOOP];
   // klee_make_symbolic(ipd, sizeof ipd, "ipd");

   // Initialze the per-flow MA table, modeled as a greybox
   klee_ma_init();

   // Create a Sketch, which is internally represented by three hash tables
   // Each hash table has total size N, cur size k and k (vi, pi) pairs.
   klee_cmin_init(HASH_SIZE);
   klee_telescope_init(CMIN_THRES, REAL_THRES);
   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);
      klee_update_iter(i);
      // timestamp of the current packet
      //curr_ts = timestamp[i];

      // Check the conn_t table
      ret = klee_ma_access();

      // this packet hits on the conn_t table
      if (ret == GREYBOX_HIT) {  // 4.995
         printf("pkt[%d]: hits on the conn_t table\n", i);
         ret = klee_ma_read();
         // Query: Large IPD ratio
         if (ret == NW_IPD_LARGE) {   // 0.1888 / 5 = 0.0376
            printf("pkt[%d]: this is a large IPD, adding to CMIN\n", i);
            klee_cmin_add();
         }
      }

      // this packet misses on the conn_t table
      else {      // 0.005 / 5 = 0.001
         printf("pkt[%d] misses on the conn_t table\n", i);
         // Invoke CP to insert a new entry
         cp_ma_table_insert(NW_IPD_SMALL);
      }

      if (klee_cmin_larger_than(CMIN_THRES)) {   // 1.22e-20 / 5 = 2.45e-21
         // send IPDs to CPU
         printf("sending IPDs to CPU\n");
      }
      klee_telescope_cmin_pkt(i);
   }
   klee_telescope_cmin();

   return 0;
}
