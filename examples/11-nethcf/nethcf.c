#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP  1

/* States of NetHCF */
#define LEARNING_STATE 0
#define FILTERING_STATE 1

/* Flag of packets */
#define NORMAL_FLAG 0
#define ABNORMAL_FLAG 1
#define SYN_COOKIE_FLAG 2

/* States of TCP session monitor */
#define SESSION_INITIAL 0
#define HANDSHAKE_START 1
#define SYN_COOKIE_START 2
#define SYN_COOKIE_FINISH 3

/* Results of TCP session monitor */
#define PASS_AND_NOP 0
#define FIRST_SYN 1
#define SYNACK_WITHOUT_PROXY 2
#define ACK_WITHOUT_PROXY 3
#define ACK_WITH_PROXY 4
#define SYN_AFTER_PROXY 5
#define MONITOR_ABNORMAL 6

#define IP2HC_TABLE_SIZE 13
#define IP2HC_HOT_THRESHOLD 10

// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   int i, ret;

   uint32_t ingress_port[NUM_LOOP];
   uint32_t tcpsyn_ack[NUM_LOOP];
   uint32_t isenabled[NUM_LOOP];
   uint32_t srcIP[NUM_LOOP];
   uint32_t dstIP[NUM_LOOP];
   uint32_t reg_nethcf_state[1];
   klee_make_symbolic(ingress_port, sizeof ingress_port, "ingress_port");
   klee_make_symbolic(tcpsyn_ack, sizeof tcpsyn_ack, "nethcf_tcpsyn_ack");
   klee_make_symbolic(srcIP, sizeof srcIP, "srcIP");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");
   klee_make_symbolic(isenabled, sizeof isenabled, "nethcf_enable");
   klee_make_symbolic(reg_nethcf_state, sizeof reg_nethcf_state, "reg_nethcf_state");

   int normal[NUM_LOOP];
   int index[NUM_LOOP];
   klee_make_symbolic(normal, sizeof normal, "nethcf_normal");
   klee_make_symbolic(index, sizeof index, "index");

   uint32_t ip2hc_valid_flag[NUM_LOOP];
   uint32_t dirty_hc_hit_flag[NUM_LOOP];
   klee_make_symbolic(ip2hc_valid_flag, sizeof ip2hc_valid_flag, "ip2hc_valid_flag");
   klee_make_symbolic(dirty_hc_hit_flag, sizeof dirty_hc_hit_flag, "dirty_hc_hit_flag");


   // Initialize the ip2hc table, modeled as a greybox
   klee_ma_init(); klee_table_init(65536);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      // apply(tag_packet_normal_table);
      int tag = NORMAL_FLAG;

      // apply(nethcf_enable_table);
      int enabled=0;
      if (isenabled[i]) {
         enabled = 1;
      }

      if (enabled == 1){
         // apply(nethcf_prepare_table);
         uint32_t ip_for_match;
         uint32_t nethcf_state;
         if (tcpsyn_ack[i]) {
            ip_for_match = dstIP[i];
            nethcf_state = reg_nethcf_state[0];
         } else {
            ip_for_match = srcIP[i];
            nethcf_state = reg_nethcf_state[0];
         }


         ret = klee_ma_access();
         if (ret == GREYBOX_HIT) {
            printf("packet hits the ip2hc table\n");

            // apply(hc_inspect_table);
            // Query: what's the distribution of normal
            if (normal[i]) {
               // apply(ip2hc_counter_update_table);
               // reg_ip2hc_counter[index[i]] += 1;
               printf("apply(ip2hc_counter_update_table);\n");

            } else {
               // logic of handling abnormal packets
               // apply(session_monitor_prepare_table);
               // apply(session_monitor_table);

               ret = klee_table_access();
               printf("pkt[%d]: %d from klee_table_access\n", i, ret);
               if (ret != GREYBOX_MISS) {
                  klee_table_add();
                  printf("hash table hit or collision, adding 1 to this entry!\n");
               } else {
                  klee_table_write(0);
                  printf("hash table miss, creating a new entry!\n");
               }


               // concrete table entries from its source. If we know the entries,
               // we can potentially generate queires. Let's use hard-coded probs
               // to work around for now.
               int result;
               klee_make_symbolic(&result, sizeof(result), "result");

               if (result == FIRST_SYN) {
                  printf("FIRST_SYN\n");
                  if (nethcf_state == FILTERING_STATE) {
                     // SYN Cookie is enabled to defend SYN DDoS at filtering
                     // apply(syn_cookie_init_table);
                     printf("syn_cookie_init_table\n");
                  }
               }

               else if (result == SYNACK_WITHOUT_PROXY) {
                  // large register array
                  printf("SYNACK_WITHOUT_PROXY\n");
               } else if (result == ACK_WITHOUT_PROXY) {
                  // large register array
                  printf("ACK_WITHOUT_PROXY\n");
               } else if (result == ACK_WITH_PROXY) {
                  // large register array
                  printf("ACK_WITH_PROXY\n");
               } else if (result == SYN_AFTER_PROXY) {
                  // large register array
                  printf("SYN_AFTER_PROXY\n");
               } else if (result == MONITOR_ABNORMAL) {
                  tag = ABNORMAL_FLAG;
                  printf("MONITOR_ABNORMAL\n");
               } else {

                  printf("else1\n");
                  uint32_t ip2hc_valid_and_dirty_hc_hit = (ip2hc_valid_flag[i] & dirty_hc_hit_flag[i]);

                  if (ip2hc_valid_and_dirty_hc_hit == 1) {
                     // Only update hit count when the Hop Count is correct
                     // apply(ip2hc_counter_update_table);
                     printf("apply(ip2hc_counter_update_table);\n");
                  }
                  else {
                     // Suspicious packets with mismatched Hop Count value
                     if (nethcf_state == LEARNING_STATE) {
                        // apply(process_mismatch_at_learning_table);
                        printf("process_mismatch_at_learning_table\n");
                     }
                     else {
                        // apply(process_mismatch_at_filtering_table);
                        printf("process_mismatch_at_filtering_table\n");
                     }
                  }
               }
            }

            printf("report_bitarray_set_table\n");

         } else {
            printf("packet misses the ip2hc table, sending to CPU\n");
            if (nethcf_state == LEARNING_STATE) {
               //  apply(process_miss_at_learning_table);
               printf("process_miss_at_learning_table\n");
            }
            else {
               //  apply(process_miss_at_filtering_table);
               printf("process_miss_at_filtering_table\n");
            }
         }
      }

      if (tag == NORMAL_FLAG) {
         printf("NORMAL_FLAG\n");
         if (ingress_port[i] % 2 == 0) {
            printf("pkt[%d] go to port 1\n", i);
         } else{
            printf("pkt[%d] go to port 2\n", i);
         }
      }

      if (tag == ABNORMAL_FLAG) {
         printf("ABNORMAL_FLAG\n");
      } else {
         printf("else2\n");
      }
   }

   return 0;
}
