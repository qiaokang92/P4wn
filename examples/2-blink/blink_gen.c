#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <klee/klee.h>

#define HASH_SIZE 64
#define NUM_LOOP  3
#define THRES     2

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

typedef struct sliding_window {
   int bin[10];
   int cur_idx;
   int prev_idx;
   int sum;
   int bin_timeout_ms;
} sw_t;

static void sw_init(sw_t *sw)
{
   memset(sw, 0, sizeof(sw_t));
   sw->cur_idx = 9;
   sw->prev_idx = 0;
   sw->sum = 0;
   // move to next bin every 80ms
   sw->bin_timeout_ms = 80;
}

static void sw_move(sw_t *sw)
{
   sw->sum -= sw->bin[sw->prev_idx];
   sw->bin[sw->prev_idx] = 0;
   sw->cur_idx  = (sw->cur_idx + 1) % 10;
   sw->prev_idx = (sw->prev_idx + 1) % 10;
}

static void sw_add(sw_t *sw)
{
   sw->bin[sw->cur_idx] += 1;
   sw->sum += 1;
}

int main()
{
   int i, ret;

   // the sliding window
   sw_t sw;
   sw_init(&sw);

   // hash table
   entry_t table[HASH_SIZE];
   memset((void *)table, 0, sizeof(entry_t) * HASH_SIZE);

   int is_rtx[NUM_LOOP];
   int is_fin[NUM_LOOP];
   int is_sw_timeout[NUM_LOOP];
   int payload_len[NUM_LOOP];
   int not_syn[NUM_LOOP];
   int is_rtx_before_fin[NUM_LOOP];
   int is_rtx_close[NUM_LOOP];
   int is_flow_timeout[NUM_LOOP];

   klee_make_symbolic(is_rtx, sizeof is_rtx, "is_rtx");
   klee_make_symbolic(is_fin, sizeof is_fin, "is_fin");
   klee_make_symbolic(is_sw_timeout, sizeof is_sw_timeout, "is_sw_timeout");
   klee_make_symbolic(payload_len, sizeof payload_len, "payload_len");
   klee_make_symbolic(not_syn, sizeof not_syn, "not_syn");
   klee_make_symbolic(is_rtx_before_fin, sizeof is_rtx_before_fin, "is_rtx_before_fin");
   klee_make_symbolic(is_rtx_close, sizeof is_rtx_close, "is_rtx_close");
   klee_make_symbolic(is_flow_timeout, sizeof is_flow_timeout, "is_flow_timeout");

   int nexthop = 0;

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Loop %d ===\n", i);

      hash_key_t *key_expr = get_key_expr("key");
      idx_t* idx = get_idx("idx");

      if (nexthop == 0) {
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      } else {
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      }

      // filter out SYN packets and ACK-only packets
      if (payload_len[i] > 0 && not_syn[i]) {

         // Move SW to the next bin if time out happens
         if (is_sw_timeout[i]) {
            sw_move(&sw);
         }

         // Access the Flow Table
         hash_key_t this_key = table[*idx].key;
         int this_value = table[*idx].value;

         // This entry is empty
         if (this_key.ip == 0) {
            table[*idx].key = *key_expr;

            if (is_rtx[i]) {
               table[*idx].value = 1;
               sw_add(&sw);
            } else {
               table[*idx].value = 0;
            }
         }

         // hit, update flag and sliding window
         else if (this_key.ip == key_expr->ip) {
            if (is_rtx[i]) {
               if (table[*idx].value == 0) {
                  table[*idx].value = 1;
                  sw_add(&sw);
               }
            }
         }

         // collision, check if timeouted
         else {
            if (is_flow_timeout[i]) {
               table[*idx].key = *key_expr;
               if (is_rtx[i] && table[*idx].value == 0) {
                  table[*idx].value = 1;
                  sw_add(&sw);
               } else {
                  table[*idx].value = 0;
               }
            }
         }

         if (sw.sum >= THRES) {
            printf("pkt[%d] triggers fast rerouting to nexthop %d\n", i, nexthop);
            nexthop = 1;
         }
      }
   }

   return 0;
}
