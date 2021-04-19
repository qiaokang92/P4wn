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
   uint8_t drop_flag;
   klee_make_symbolic(&drop_flag, sizeof drop_flag, "drop_flag");

   uint8_t hitConnTable[NUM_LOOP];
   klee_make_symbolic(hitConnTable, sizeof hitConnTable, "hitConnTable");

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      if (hitConnTable[i] == 1) {
         printf("enforcing ACL\n");
         if (drop_flag) {
            printf("apply(drop_stats);\n");
         }
      } else {
         printf("sending to CPU\n");
      }
   }

   return 0;
}
