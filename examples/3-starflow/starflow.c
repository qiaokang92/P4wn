#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>
#include "starflow.h"

#define HASH_SIZE 65536
#define NUM_LOOP  3

#define ETH_IPV4 0x0800

// P4 source: https://github.com/jsonch/StarFlow

int main()
{
   int i, ret;
   uint8_t is_ipv4[NUM_LOOP];

   klee_make_symbolic(is_ipv4, sizeof is_ipv4, "ipv4");

   // Initialize a data plane cache,  modeled as a greybox
   klee_table_init(HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      // metadata
      int inProcessing = 0;
      int collision = 0;
      int match = 0;

      // Query the ratio of IPV4 packets at line 36
      if (is_ipv4[i]) {         // 1.9772 / 2 = 0.9886
         // Check the cache
         ret = klee_table_access();
         if (ret == GREYBOX_COL) {      // 2.27552e-10 / 2 = 1.13776e-10
            collision = 1;
         }

         // add new flow into the data plane table
         if (ret == GREYBOX_COL || ret == GREYBOX_MISS) {  // 1.9772 / 2 = 0.9886
            klee_table_write(1);
         }
         inProcessing = 1;
      }

      // set match flag based on hash table access
      // p4src/mainStarFlow.p4#L78
      if (inProcessing && collision == 0) {           // 1.9772 / 2 = 0.9886
         match = 1;
      }

      // do vector stuff
      if (inProcessing == 1) {                  // 0.9886 / 2 = 0.49
         vector_actions();
      }

      if (inProcessing && match == 0) {           // 2.27552e-10 / 2 = 1.13776e-10
         printf("evicting an entry!\n");
      }

      // printf("=== pkt %d finished ===\n", i);
   }

   return 0;
}
