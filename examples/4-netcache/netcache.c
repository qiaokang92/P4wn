#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define CMIN_SIZE  256
#define BF_SIZE    512
#define NUM_LOOP   3
#define CMIN_THRES 128

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
   uint8_t is_read[NUM_LOOP];
   klee_make_symbolic(is_read, sizeof is_read, "nc_read");

   int i;
   int ret;

   // Initialize the BF, modeled as a greybox
   klee_bf_init(BF_SIZE);

   klee_cmin_init(CMIN_SIZE);
   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      // process_cache();
      uint8_t is_exist;
      uint8_t is_exist_read;
      klee_make_symbolic(&is_exist, sizeof is_exist, "nc_exist");
      klee_make_symbolic(&is_exist_read, sizeof is_exist_read, "nc_exist_read");

      // Query the ratio of hit, NetCache paper says it's less than 50%
      if (is_exist) {
         // Suppose 90%
         if (is_read[i]) {     // 2.25 / 5  = 0.45
            printf("checking cache valid\n");
         } else {                              // 0.25 / 5 = 0.05
            printf("setting cache valid\n");
         }
      }

      // process_value();
      if (is_exist) {
         // Suppose 90%
         if (is_read[i]) {              // 2.25 / 5 = 0.45
            printf("reading value from cache\n");
         } else {                                     // 0.25 / 5 = 0.05
            printf("writing value to cache\n");
         }
      }

      // ipv4_route();

      // egress
      if (is_exist_read) {       // 2.25 / 5 = 0.45
         // heavy_hitter();
         klee_cmin_add();
         if (klee_cmin_larger_than(CMIN_THRES)) {         // 1.38824e-38 / 5 = 2.77648e-39
            ret = klee_bf_access();
            if (ret != BF_ACCESS_HIT) {                   //
               printf("sending HH report to CPU\n");
            }                                             // else is 0
         }
      }
   }

   return 0;
}
