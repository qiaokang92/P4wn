#include <stdio.h>
#include <memory.h>
#include <klee/klee.h>

#define HASH_SIZE 64
#define NUM_LOOP  2
#define THRES     32

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

   uint8_t is_rtx[NUM_LOOP];
   uint8_t is_fin[NUM_LOOP];
   uint8_t is_sw_timeout[NUM_LOOP];
   uint8_t not_syn_ack_only[NUM_LOOP];
   uint8_t not_syn[NUM_LOOP];
   uint8_t is_rtx_before_fin[NUM_LOOP];
   uint8_t is_rtx_close[NUM_LOOP];
   uint8_t is_flow_timeout[NUM_LOOP];

   klee_make_symbolic(is_rtx, sizeof is_rtx, "rtx");
   klee_make_symbolic(is_fin, sizeof is_fin, "fin");
   klee_make_symbolic(is_sw_timeout, sizeof is_sw_timeout, "overall_to:80");
   klee_make_symbolic(not_syn_ack_only, sizeof not_syn_ack_only, "not_syn_ack_only");
   klee_make_symbolic(not_syn, sizeof not_syn, "not_syn");
   klee_make_symbolic(is_rtx_before_fin, sizeof is_rtx_before_fin, "rtx_before_fin");
   klee_make_symbolic(is_rtx_close, sizeof is_rtx_close, "is_rtx_close");
   klee_make_symbolic(is_flow_timeout, sizeof is_flow_timeout, "is_flow_timeout");

   // Initialize the Blink flow table, modeled as a greybox
   klee_table_init(HASH_SIZE);
   printf("initializing a hash table, size=%d\n", HASH_SIZE);

   int nexthop = 0;

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Loop %d ===\n", i);
      klee_update_iter(i);


      if (nexthop == 0) {
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      } else {
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      }


      // Add match==1 into the following if-branch

      // filter out SYN packets and ACK-only packets
      if (not_syn_ack_only[i]) {

         // Move SW to the next bin if time out happens
         if (is_sw_timeout[i]) {
            sw_move(&sw);
         }

         // Access the Flow Table
         ret = klee_table_access();
         if (ret == GREYBOX_HIT) {
            printf("pkt[%d] hits the flow table\n", i);

            // reset the flow table entry upon FIN packets
            if (is_fin[i]) {
               printf("pkt[%d] is a FIN, resetting this entry\n", i);
               klee_table_write(0);

               // update the sw if the flow has sent a rtx during the last
               // time window
               if (is_rtx_before_fin[i]) {
                  sw.bin[sw.cur_idx] -= 1;
               }
            }
            // Check if this packet is a retransmission and update sw
            else {
               if (is_rtx[i]) {       // query rtx
                  // case 1: timeout
                  // case 2: not timeout
                  // It updates the count accordingly
                  printf("pkt[%d] is an rtx\n", i);
                  sw_add(&sw);

               }
               else {
                  printf("pkt[%d] is not an rtx, skip\n", i);
               }
            }
         }

         // table miss, reset this entry
         else {
            printf("pkt[%d] is not monitored by Blink!\n", i);
            // check if the flow has timeouted

            if (is_flow_timeout[i]) {
               // during the last time window
               klee_table_write(0);

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
