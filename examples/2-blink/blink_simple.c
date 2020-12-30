#include <stdio.h>
#include <memory.h>
#include <klee/klee.h>

#define HASH_SIZE 64
#define NUM_LOOP  7
#define THRES     6

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

static void sw_add(sw_t *sw, int timeout)
{
   sw->bin[sw->cur_idx] += 1;
   sw->sum += 1;

   // move the bin by one if timeout happens
   // ret = klee_query(QUERY_OVERALL_TO_80);
   if (timeout) {        // 0.00190167 / 8 = 0.0002377
      sw->sum -= sw->bin[sw->prev_idx];
      sw->bin[sw->prev_idx] = 0;
      sw->cur_idx  = (sw->cur_idx + 1) % 10;
      sw->prev_idx = (sw->prev_idx + 1) % 10;
   }
}

int main()
{
   int i, ret;
   //char rtx[NUM_LOOP];
   //klee_make_symbolic(rtx, sizeof rtx, "rtx");

   // the sliding window
   sw_t sw;
   sw_init(&sw);

   int is_rtx[NUM_LOOP];
   int is_fin[NUM_LOOP];
   int is_sw_timeout[NUM_LOOP];

   klee_make_symbolic(is_rtx, sizeof is_rtx, "is_rtx");
   klee_make_symbolic(is_fin, sizeof is_fin, "is_fin");
   klee_make_symbolic(is_sw_timeout, sizeof is_sw_timeout, "is_sw_timeout");

   // Initialize the Blink flow table, modeled as a greybox
   klee_table_init(HASH_SIZE);
   printf("initializing a hash table, size=%d\n", HASH_SIZE);

   int nexthop = 0;

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Loop %d ===\n", i);

      if (nexthop == 0) {   // 7 / 8 = 0.875
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      } else if (nexthop == 1) {  // 1 / 8 = 0.125
         printf("pkt[%d]: sending to nexthop %d\n", i, nexthop);
      }

      // Access the Flow Table
      ret = klee_table_access();
      if (ret == GREYBOX_HIT) {            // 0.314717 / 8 = 0.039
         printf("pkt[%d] hits the flow table\n", i);
         if (is_rtx[i]) {       // query rtx    // 0.024464 / 8 = 0.0031
            printf("pkt[%d] is an rtx\n", i);
            if (is_sw_timeout[i]) {       // query timeout   // 0.00190167 / 8 = 0.000238
               sw_add(&sw, 1);
            } else {                      // 0.0225623 / 8 = 0.00282
               sw_add(&sw, 0);
            }
         } else {                         // 0.290253 / 8 = 0.0363
            printf("pkt[%d] is not an rtx, skip\n", i);
         }

         // reset the flow table entry upon FIN packets
         if (is_fin[i]) {                 // query fin   // 0.0221561 / 8 = 0.00277
            printf("pkt[%d] is a FIN, TODO\n", i);
         }
      } else if (ret == GREYBOX_MISS) {     // 6.68029 / 8 = 0.8350
         printf("pkt[%d] misses the flow table!\n", i);
         klee_table_write(0);
      } else if (ret == GREYBOX_COL) {      // 0.00499551 / 8 = 0.000624
         // TODO: check if the existing entry is timeouted
      }

      if (sw.sum >= THRES) {        // 2.92097e-18 / 8 = 3.651e-19
         printf("pkt[%d] triggers fast rerouting to nexthop %d\n", i, nexthop);
      }
   }

   return 0;
}
