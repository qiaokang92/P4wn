#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP  2


// =======================================
// ========= switch data plane ===========
// =======================================


int main()
{
   int i, ret;
   int is_timeout[NUM_LOOP];
   int pktID[NUM_LOOP];
   klee_make_symbolic(is_timeout, sizeof is_timeout, "perflow_to:5000000");
   klee_make_symbolic(pktID, sizeof pktID, "pktID");

   // Initialize the cache, modeled as a greybox
   klee_table_init(HASH_SIZE);

   uint8_t last_flowid = 0;
   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      printf("=== Processing pkt %d ===\n", i);
      ret = klee_table_access();

      if (ret != GREYBOX_MISS) {
         ret = klee_table_read();
      } else {
         klee_table_write(0);
      }

      uint8_t flowid;
      // Query the ratio of per-flow IPD > 5ms
      if (is_timeout[i]) {
         klee_table_add();
         flowid = last_flowid+1;
         last_flowid += 1;
      } else {
         flowid = last_flowid;
      }

      // apply(ecmp_group);
      uint8_t egress_port;
      uint8_t nhop_ipv4;
      // apply(ecmp_nhop);
      if ((pktID[i]+flowid) % 2 == 0){
         printf("forwarding to port 1");
         egress_port = 1;
         nhop_ipv4 = 1;
      } else {
         printf("forwarding to port 2");
         egress_port = 2;
         nhop_ipv4 = 2;
      }

      // apply(forward);
      if (nhop_ipv4 == 1) {
         printf("set_dmac to port 1\n");
      } else {
         printf("set_dmac to port 2\n");
      }

      // send_frame.apply();
      if (egress_port == 1){
         printf("rewrite_mac to port 1");
      } else{
         printf("rewrite_mac to port 2");
      }

   }

   return 0;
}
