#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP  1


// =======================================
// ========= switch data plane ===========
// =======================================


int main()
{
   int i, ret;

   // Initialize the ACL table, modeled as a greybox
   klee_ma_init();

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      ret = klee_ma_access();
      if (ret == GREYBOX_HIT) {            // 0.75
         printf("enforcing ACL\n");
      } else {                             // 0.25
         printf("sending to CPU\n");
      }
   }

   return 0;
}
