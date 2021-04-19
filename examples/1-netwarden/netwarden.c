#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE  128
#define NUM_LOOP   2
#define CMIN_THRES 20
#define PORT_SERVER 1
#define PORT_CLIENT 0
#define CPU_OUT 2

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
   int i;
   int ret;

   uint64_t tstamp[NUM_LOOP];
   uint32_t seq[NUM_LOOP];
   uint32_t ack[NUM_LOOP];
   uint16_t dataoffset[NUM_LOOP];
   uint16_t totallen[NUM_LOOP];
   uint32_t port_server[NUM_LOOP];
   uint32_t port_client[NUM_LOOP];
   uint32_t highwater[NUM_LOOP];
   uint32_t IPID[NUM_LOOP];
   uint32_t dstIP[NUM_LOOP];
   uint32_t dataCPU[NUM_LOOP];

   klee_make_symbolic(tstamp, sizeof tstamp, "tstamp");
   klee_make_symbolic(seq, sizeof seq, "seq");
   klee_make_symbolic(ack, sizeof ack, "ack");
   klee_make_symbolic(dataoffset, sizeof dataoffset, "dataoffset");
   klee_make_symbolic(totallen, sizeof totallen, "totallen");
   klee_make_symbolic(port_server, sizeof port_server, "timing_port_server");
   klee_make_symbolic(port_client, sizeof port_client, "timing_port_client");
   klee_make_symbolic(highwater, sizeof highwater, "highwater");
   klee_make_symbolic(IPID, sizeof IPID, "IPID");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");
   klee_make_symbolic(dataCPU, sizeof dataCPU, "timing_data_cpu");


   // Initialze the per-flow MA table, modeled as a greybox
   klee_ma_init();

   // Create a Sketch, which is internally represented by three hash tables
   // Each hash table has total size N, cur size k and k (vi, pi) pairs.
   klee_cmin_init(HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);
      klee_update_iter(i);

      // apply (split_tstamp_high32_tab); //obtain timestamp for this packet
      uint32_t tstamp_high32 = tstamp[i] >> 32;
      // apply (split_seq_low16_tab);
      uint16_t seq_low16 = seq[i] >> 16;
      // apply (split_ack_low16_tab);
      uint16_t ack_low16 = ack[i] >> 16;
      // apply (convert_dataoffset_to_32_tab); // convert dataoffset to 32 bits
      uint32_t dataoffset32 = dataoffset[i];
      // apply (convert_totallen_to_32_tab); // convert totallen to 32 bits
      uint32_t totallen32 = totallen[i];

      // Check the conn_t table
      ret = klee_ma_access();

      // this packet hits on the conn_t table
      if (ret == GREYBOX_HIT) {
         printf("pkt[%d]: hits on the conn_t table\n", i);
         // from server to client
         if (port_server[i]){
            ret = klee_ma_read();
            // Query: Large IPD ratio
            if (ret == NW_IPD_LARGE) {
               printf("pkt[%d]: this is a large IPD, adding to CMIN\n", i);
               klee_cmin_add();
            }

            if (klee_cmin_larger_than(CMIN_THRES)) {
               // send IPDs to CPU
               printf("sending IPDs to CPU\n");
            }

         } else {
            // apply (shift_dataoffset_tab); // dataoffset << 2
            dataoffset[i] = dataoffset[i] << 2;
            // apply (add_totallen_seq_tab); // highwater = totallen + tcp.seq
            highwater[i] = totallen[i] + seq[i];

            // from client to the server, ack packets
            if (port_client[i]){
               printf("compute RTT!\n");
            }
            // from CPU and it is data packet sent to the client
            // we update the highwater and tstamp
            // else if (ingress_port[i] == CPU_OUT) {
            else {
               // Check the table that stores all IPs of CPU packets
               highwater[i] -= dataoffset[i];
               // data CPU
               if (dataCPU[i]){
                  printf("update RTT!\n");
               }
            }
         }
      }

      // this packet misses on the conn_t table
      else {
         printf("pkt[%d] misses on the conn_t table\n", i);
         // Invoke CP to insert a new entry
         cp_ma_table_insert(NW_IPD_SMALL);
      }

      // forwarding
      if (dstIP[i] % 2 == 0) {
         printf("pkt[%d] go to port 1\n", i);
      } else {
         printf("pkt[%d] go to port 2\n", i);
      }
   }

   return 0;
}
