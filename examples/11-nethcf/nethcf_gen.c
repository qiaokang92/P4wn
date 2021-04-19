#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE 64
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

typedef unsigned char uchar;
typedef unsigned int uint;

typedef uint16_t idx_t;
#define IDX_LEN (sizeof(idx_t))

typedef struct __attribute__((packed))  hash_key_t {
   uint32_t ip;
   uint16_t port;
   uint8_t  proto;
} hash_key_t;
#define KEY_LEN (sizeof(hash_key_t))

typedef struct entry_t {
   hash_key_t key;
   int value;
} entry_t;

static hash_key_t *get_key_expr(char *name)
{
   hash_key_t *key_expr = malloc(sizeof(hash_key_t));
   klee_make_symbolic((void *)key_expr, sizeof(hash_key_t), name);
   return key_expr;
}

static idx_t* get_idx(char *name)
{
   idx_t *idx = malloc(IDX_LEN);
   klee_make_symbolic((void *)idx, sizeof(uint16_t), name);
   klee_assume(*idx <= HASH_SIZE - 1);
   klee_assume(*idx >= 0);

   return idx;
}


typedef unsigned int uint;


// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   // hash table
   entry_t table[HASH_SIZE];
   memset((void *)table, 0, sizeof(entry_t) * HASH_SIZE);

   int i, ret;
   int isKnown[NUM_LOOP];
   uint32_t ingress_port[NUM_LOOP];
   uint32_t tcpsyn_ack[NUM_LOOP];
   uint32_t isenabled[NUM_LOOP];
   uint32_t srcIP[NUM_LOOP];
   uint32_t dstIP[NUM_LOOP];
   uint32_t reg_nethcf_state[1];

   klee_make_symbolic(ingress_port, sizeof ingress_port, "ingress_port");
   klee_make_symbolic(isenabled, sizeof isenabled, "isenabled");
   klee_make_symbolic(tcpsyn_ack, sizeof tcpsyn_ack, "tcpsyn_ack");
   klee_make_symbolic(srcIP, sizeof srcIP, "srcIP");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");
   klee_make_symbolic(reg_nethcf_state, sizeof reg_nethcf_state, "reg_nethcf_state");

   klee_make_symbolic(isKnown, sizeof isKnown, "isKnown");
   int normal[NUM_LOOP];
   int index[NUM_LOOP];
   klee_make_symbolic(normal, sizeof normal, "normal");
   klee_make_symbolic(index, sizeof index, "index");

   uint32_t ip2hc_valid_flag[NUM_LOOP];
   uint32_t dirty_hc_hit_flag[NUM_LOOP];
   klee_make_symbolic(ip2hc_valid_flag, sizeof ip2hc_valid_flag, "ip2hc_valid_flag");
   klee_make_symbolic(dirty_hc_hit_flag, sizeof dirty_hc_hit_flag, "dirty_hc_hit_flag");

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      hash_key_t *key_expr = get_key_expr("key");
      idx_t* idx = get_idx("idx");

      // apply(tag_packet_normal_table);
      int tag = NORMAL_FLAG;

      // apply(nethcf_enable_table);

      int enabled=0;
      if (isenabled[i] == 1) {
         enabled = 1;
      }

       if (enabled == 1){
          uint32_t ip_for_match;
          uint32_t nethcf_state;
          if (tcpsyn_ack[i] == 1) {
             ip_for_match = dstIP[i];
             nethcf_state = reg_nethcf_state[0];
          } else {
             ip_for_match = srcIP[i];
             nethcf_state = reg_nethcf_state[0];
          }

          if (isKnown[i]) {
             printf("packet hits the ip2hc table\n");

             // apply(hc_inspect_table);

             // Query: what's the distribution of normal
             if (normal[i]) {
                printf("apply(ip2hc_counter_update_table);\n");
             // apply(ip2hc_counter_update_table);
             } else {
                // Access the Flow Table
                hash_key_t this_key = table[*idx].key;
                int this_value = table[*idx].value;

                // greybox operations
                if (this_key.ip != 0) {
                   table[*idx].value += 1;
                } else {
                   table[*idx].key = *key_expr;
                   table[*idx].value = 1;
                }

             // apply(session_monitor_prepare_table);
             // apply(session_monitor_table);
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
                   printf("SYNACK_WITHOUT_PROXY\n");
                }
                else if (result == ACK_WITHOUT_PROXY) {
                   printf("ACK_WITHOUT_PROXY\n");
                }
                else if (result == ACK_WITH_PROXY) {
                   printf("ACK_WITH_PROXY\n");
                }
                else if (result == SYN_AFTER_PROXY) {
                   printf("SYN_AFTER_PROXY\n");
                }
                else if (result == MONITOR_ABNORMAL) {
                   tag = ABNORMAL_FLAG;
                   printf("MONITOR_ABNORMAL\n");
                } else {
                   printf("else1\n");
                   if ((ip2hc_valid_flag[i] & dirty_hc_hit_flag[i]) == 1) {
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
             // Hot IP2HC entry process

             printf("report_bitarray_set_table\n");

          } else {
             printf("packet misses the ip2hc table, sending to CPU\n");

             if (nethcf_state == LEARNING_STATE) {
                printf("process_miss_at_learning_table\n");
             } else {
                printf("process_miss_at_filtering_table\n");
             }
          }
      }
      if (tag == NORMAL_FLAG) {
         printf("NORMAL_FLAG\n");
         if (ingress_port[i] % 2 == 0) {
            printf("pkt[%d] go to port 1\n", i);
         } else {
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
