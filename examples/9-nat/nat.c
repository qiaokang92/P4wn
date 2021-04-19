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
   uint8_t ingress_port[NUM_LOOP];
   uint8_t egress_port[NUM_LOOP];
   uint8_t ttl[NUM_LOOP];
   uint8_t dstIP[NUM_LOOP];
   uint8_t instance_type[NUM_LOOP];
   klee_make_symbolic(ingress_port, sizeof ingress_port, "ingress_port");
   klee_make_symbolic(egress_port, sizeof egress_port, "egress_port");
   klee_make_symbolic(ttl, sizeof ttl, "ttl");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");
   klee_make_symbolic(instance_type, sizeof instance_type, "instance_type");

   // Initialize the NAT table, modeled as a greybox
   klee_ma_init();

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      uint8_t if_index = ingress_port[i];
      // apply(if_info);

      // apply(nat);
      uint8_t forward=0;
      ret = klee_ma_access();
      if (ret == GREYBOX_HIT) {
         printf("translating addr\n");
         forward = 1;
      } else {
         printf("sending to CPU\n");
      }

      if (forward == 1) {
         if (ttl[i] > 0) {
            // apply(ipv4_lpm);
            uint8_t nhop_ipv4;
            if (dstIP[i] % 2 == 0) {
               printf("nhop_ipv4 to port 1\n");
               nhop_ipv4 = 1;
               egress_port[i] = 1;
            } else {
               printf("nhop_ipv4 to port 2\n");
               nhop_ipv4 = 2;
               egress_port[i] = 2;
            }

            ttl[i] -= 1;
            // apply(forward);
            if (nhop_ipv4 == 1) {
               printf("set_dmac to port 1\n");
            } else {
               printf("set_dmac to port 2\n");
            }
         }
      }

      // egress
      if (instance_type[i] == 0) {
         // apply(send_frame);
         if (egress_port[i] == 1) {
            printf("do_rewrite to port 1\n");
         } else {
            printf("do_rewrite to port 2\n");
         }
      } else {
         // apply(send_to_cpu);
         printf("CPU encap\n");
      }
   }

   return 0;
}
