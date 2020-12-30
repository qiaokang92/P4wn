#include <stdio.h>
#include <memory.h>
#include <klee/klee.h>
#define HASH_SIZE 64
#define NUM_LOOP  5
#define THRES     (NUM_LOOP - 1)
#define REAL_THRES  5

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

   // Initialize the Blink flow table, modeled as a greybox
   klee_table_init(HASH_SIZE);
   klee_telescope_init(THRES, REAL_THRES);

   int nexthop = 0; int counter = 0;

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Loop %d ===\n", i);

      if (nexthop == 0) {
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      } else {
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      }

      // filter out SYN packets and ACK-only packets
      if (payload_len[i] > 0 && not_syn[i]) {         // 4.5 / 5 = 0.9

         // Move SW to the next bin if time out happens
         //if (is_sw_timeout[i]) {                        // 0.0405 / 5 = 0.0081
         //   sw_move(&sw);
         //}

         // Access the Flow Table
         ret = klee_table_access();
         if (ret == GREYBOX_HIT) {                         // 0.0100786 / 5 = 0.002
            printf("pkt[%d] hits the flow table\n", i);

            // reset the flow table entry upon FIN packets
            if (is_fin[i]) {                               // 0.000709535 / 5 = 0.00014
               printf("pkt[%d] is a FIN, resetting this entry\n", i);
               klee_table_write(0);

               // update the sw if the flow has sent a rtx during the last
               // time window
               if (is_rtx_before_fin[i]) {             // 7.09535e-10 / 5 = 1.41907e-10
                  if (counter >= 1) counter -= 1;
               }
            }
            // Check if this packet is a retransmission and update sw
            else {                                           // 0.00936908 / 5 = 0.0018
               if (is_rtx[i]) {       // query rtx           // 6.27729e-06/5 = 1.25e-06
                  // sw_add(&sw);
                  counter += 1;
               }
               else {                                          // 0.00936281 / 5 = 0.0019
                  // printf("pkt[%d] is not an rtx, skip\n", i);
               }
            }
         }

         // table miss, reset this entry
         else {    // 4.03992 / 5=0.807984
            // printf("pkt[%d] is not monitored by Blink!\n", i);
            // check if the flow has timeouted
            if (is_flow_timeout[i]) {             // 0.403992 / 5 = 0.081
               klee_table_write(0);
            }
         }

         if (counter >= THRES) {                   // 2.93651e-22 / 5 = 5.87302e-23
            // printf("pkt[%d] triggers fast rerouting to nexthop %d\n", i, nexthop);
            nexthop = 1;
         }
      }
      klee_telescope_pkt(i, counter);
   }
   klee_telescope(counter);

   return 0;
}
