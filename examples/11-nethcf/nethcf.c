#include <stdio.h>
#include <assert.h>
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

// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   int i, ret;

   // Initialize the ip2hc table, modeled as a greybox
   klee_ma_init(); klee_table_init(65536);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      // apply(tag_packet_normal_table);
      int tag = NORMAL_FLAG;

      // apply(nethcf_enable_table);
      // Suppose NetHCF is always enabled

      ret = klee_ma_access();
      if (ret == GREYBOX_HIT) {                            // 0.999
         printf("packet hits the ip2hc table\n");

         // apply(hc_inspect_table);
         int normal;
         klee_make_symbolic(&normal, sizeof(normal), "normal");

         // Query: what's the distribution of normal
         if (normal) {                                       // 0.4995
            // apply(ip2hc_counter_update_table);
         } else {                                             // 0.4995
            // logic of handling abnormal packets
            // apply(session_monitor_prepare_table);
            // apply(session_monitor_table);

            ret = klee_table_access();
            printf("pkt[%d]: %d from klee_table_access\n", i, ret);

            // TODO: result is set by session_monitor_table, but we didn't find
            // concrete table entries from its source. If we know the entries,
            // we can potentially generate queires. Let's use hard-coded probs
            // to work around for now.
            int result;
            klee_make_symbolic(&result, sizeof(result), "result");

            if (result == SYNACK_WITHOUT_PROXY) {
               printf("SYNACK_WITHOUT_PROXY\n");
            } else if (result == ACK_WITHOUT_PROXY) {
               printf("ACK_WITHOUT_PROXY\n");
            } else if (result == ACK_WITH_PROXY) {
               printf("ACK_WITH_PROXY\n");
            } else if (result == SYN_AFTER_PROXY) {
               printf("SYN_AFTER_PROXY\n");
            } else if (result == MONITOR_ABNORMAL) {
               tag = ABNORMAL_FLAG;
               printf("MONITOR_ABNORMAL\n");
            } else {
               printf("else1\n");
            }
         }
      } else {                                              // 0.001
         printf("packet misses the ip2hc table, sending to CPU\n");
      }

      if (tag == NORMAL_FLAG) {                            // 0.984391
         printf("NORMAL_FLAG\n");
      }

      if (tag == ABNORMAL_FLAG) {                              // 0.0156094
         printf("ABNORMAL_FLAG\n");
      } else {                                              // 0.984391
         printf("else2\n");
      }
   }

   return 0;
}
