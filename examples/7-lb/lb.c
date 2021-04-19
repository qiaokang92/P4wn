#include <stdio.h>
#include <klee/klee.h>

#define NUM_LOOP 1

int main()
{
   int ret, i;
   int pktID[NUM_LOOP];
   klee_make_symbolic(pktID, sizeof pktID, "pktID");

   for (i = 0; i < NUM_LOOP; i ++) {
      // ecmp_group.apply();
      uint8_t ecmp_select;
      uint8_t egress_port;
      if (pktID[i] % 2 == 0){ // 0.5->0.25
         ecmp_select = 1;
      } else {                // 0.5->0.25
         ecmp_select = 2;
      }

      // ecmp_nhop.apply();
      if (ecmp_select == 1){  // 0.5->0.25
         printf("forwarding to port 1");
         egress_port = 1;
      } else {                // 0.5->0.25
         printf("forwarding to port 2");
         egress_port = 2;
      }

      // send_frame.apply();
      if (egress_port == 1){  // 0.5->0.25
         printf("rewrite_mac to port 1");
      } else {                // 0.5->0.25
         printf("rewrite_mac to port 2");
      }
   }

   return 0;
}
