#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define CMIN_SIZE  256
#define BF_SIZE    512
#define NUM_LOOP   5
#define CMIN_THRES 5
#define REAL_THRES 16

#define NC_READ_REQUEST     0
#define NC_READ_REPLY       1
#define NC_HOT_READ_REQUEST 2
#define NC_WRITE_REQUEST    4
#define NC_WRITE_REPLY      5
#define NC_UPDATE_REQUEST   8
#define NC_UPDATE_REPLY     9

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
   // packet headers
   int op[NUM_LOOP];
   klee_make_symbolic(op, sizeof op, "op");

   int i;
   int ret;

   // Initialize the BF, modeled as a greybox
   klee_bf_init(BF_SIZE);
   klee_telescope_init(CMIN_THRES, REAL_THRES);
   klee_cmin_init(CMIN_SIZE);
   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      // process_cache();
      int exist;
      klee_make_symbolic(&exist, sizeof exist, "exist");

      // Query the ratio of hit, NetCache paper says it's less than 50%
      if (exist) {
         // Suppose 90%
         if (op[i] == NC_READ_REQUEST) {     // 2.25 / 5  = 0.45
            //printf("checking cache valid\n");
         } else {                              // 0.25 / 5 = 0.05
            //printf("setting cache valid\n");
         }
      }

      // process_value();
      if (exist) {
         // Suppose 90%
         if (op[i] == NC_READ_REQUEST) {              // 2.25 / 5 = 0.45
            //printf("reading value from cache\n");
         } else {                                     // 0.25 / 5 = 0.05
            //printf("writing value to cache\n");
         }
      }

      // ipv4_route();

      // egress
      if (op[i] == NC_READ_REQUEST && exist == 0) {       // 2.25 / 5 = 0.45
         // heavy_hitter();
         klee_cmin_add();
         if (klee_cmin_larger_than(CMIN_THRES)) {         // 1.38824e-38 / 5 = 2.77648e-39
            ret = klee_bf_access();
            if (ret != BF_ACCESS_HIT) {                   //
               printf("sending HH report to CPU\n");
            }                                             // else is 0
         }
      }
      klee_telescope_cmin_pkt(i);
   }
   klee_telescope_cmin();

   return 0;
}
