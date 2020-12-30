#include <stdio.h>
#include <klee/klee.h>

#define NUM_LOOP 1

int main()
{
   int ret, i;
   int pktID[NUM_LOOP];
   klee_make_symbolic(pktID, sizeof pktID, "pktID");

   for (i = 0; i < NUM_LOOP; i ++) {
      if (pktID[i] == 0) {              // 0.5
         printf("forwarding to port 0");
      } else {                       // 0.5
         printf("forwarding to port 1");
      }
   }

   return 0;
}
