#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP  3


// =======================================
// ========= switch data plane ===========
// =======================================


int main()
{
   int i, ret;
   int is_timeout[NUM_LOOP];
   int pktID[NUM_LOOP];

   klee_make_symbolic(is_timeout, sizeof is_timeout, "is_timeout");
   klee_make_symbolic(pktID, sizeof pktID, "pktID");

   // Initialize the cache, modeled as a greybox
   klee_table_init(HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      printf("=== Processing pkt %d ===\n", i);
      ret = klee_table_access();
      // Query the ratio of per-flow IPD > 5ms
      if (is_timeout[i]) {            // 0.0466667 / 2 = 0.023
         klee_table_add();
      }

      if (ret != GREYBOX_MISS) {      // 1.56148e-05 / 2 = 7.8074e-06
         ret = klee_table_read();
         // Query: P4wn should just query half or use LattE to compute the prob,
         // the result is 50% because pktID follows uniform distribution
         if ((pktID[i] + ret) % 2 == 0) {     // Attack (never timeout) 7.80741e-06 / 2 = 3.9e-06
            printf("sending to port 0\n");
         } else {                             // Attack (never timeout) 7.80741e-06 / 2 = 3.9e-06
            printf("sending to port 1\n");
         }
      } else {                         // 1.99998 / 2 = 0.99999
         klee_table_write(0);
      }
   }

   return 0;
}
