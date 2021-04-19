#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP      2
#define DUPACK_THRESH 20
#define PORT_SERVER 1
#define PORT_CLIENT 0
#define PORT_CPU 2

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

int nhop(dstip, i){
   if (dstip % 2 == 0) {
      printf("pkt[%d] go to port 1\n", i);
   } else {
      printf("pkt[%d] go to port 2\n", i);
   }
   return 0;
}

// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   int i, ret;

   int dupAck[NUM_LOOP];
   int low_high[NUM_LOOP];
   uint32_t dstIP[NUM_LOOP];
   uint32_t ingress_port[NUM_LOOP];
   uint32_t recv_wind[NUM_LOOP];

   klee_make_symbolic(dupAck, sizeof dupAck, "dupack");
   klee_make_symbolic(low_high, sizeof low_high, "half");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");
   klee_make_symbolic(ingress_port, sizeof ingress_port, "ingress_port");
   klee_make_symbolic(recv_wind, sizeof recv_wind, "recv_wind");


   // Initialze the per-flow table, modeled as a greybox
   klee_table_init(HASH_SIZE);
   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      printf("=== Processing pkt %d ===\n", i);
      int reroute_bit = 0;

      if (ingress_port[i] == PORT_CPU){
         nhop(dstIP[i], i);
      } else {
         // Check the conn_t table
         ret = klee_table_access();


         // this packet hits on the table
         if (ret != GREYBOX_MISS) {
            printf("pkt[%d]: hits on the conn_t table\n", i);

            ret = klee_read_larger_than(DUPACK_THRESH);
            if (ret) {
               reroute_bit = 1;
            }

            if (ingress_port[i] == PORT_SERVER){
               // Query: number of dupAcks
               if (dupAck[i]) {
                  klee_table_add();
               }
               // Query: half
               if (low_high[i]) {
                  printf("pkt[%d]: low range\n", i);
                  // example table entries
                  if (recv_wind[i] < 32768) {
                     recv_wind[i] = 32768;
                  } else {
                     recv_wind[i] = 65535;
                  }
               } else {
                  printf("pkt[%d]: high range\n", i);
                  // example table entries
                  if (recv_wind[i] < 32768) {
                     recv_wind[i] = 4096;
                  } else {
                     recv_wind[i] = 32768;
                  }
               }

               printf("pkt[%d]: update checksum\n", i);
            }
         }
         // this packet misses on the conn_t table
         else  {
            printf("pkt[%d] misses on the conn_t table\n", i);
            klee_table_write(0);
         }
      }

      if (reroute_bit) {
         printf("pkt[%d]: rerouting\n", i);
      } else {
         printf("pkt[%d]: normal routing\n", i);
         nhop(dstIP[i], i);
      }
   }

   return 0;
}
