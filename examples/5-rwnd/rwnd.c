#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP      3
#define DUPACK_THRESH 20

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
   int i, ret;

   int dupAck[NUM_LOOP];
   klee_make_symbolic(dupAck, sizeof dupAck, "dupAck");
   int low_high[NUM_LOOP];
   klee_make_symbolic(low_high, sizeof low_high, "low_high");

   // Initialze the per-flow table, modeled as a greybox
   klee_table_init(HASH_SIZE);
   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      printf("=== Processing pkt %d ===\n", i);
      int reroute_bit = 0;

      // Check the conn_t table
      ret = klee_table_access();

      // this packet hits on the table
      if (ret == GREYBOX_HIT || ret == GREYBOX_COL) {    // 0.000152586 / 5 =3.05172e-05
         printf("pkt[%d]: hits on the conn_t table\n", i);

         // Query: number of dupAcks
         if (dupAck[i]) {            // 9.48675e-05 / 5 = 1.89735e-05
            klee_table_add();
         }

         ret = klee_read_larger_than(DUPACK_THRESH);
         if (ret) {                         // attack: 8.10022e-21 / 5 = 1.62e-21
            reroute_bit = 1;
         }

         // Query: half
         if (low_high[i]) {                             // 7.62928e-05 / 5 = 1.525e-05
            printf("pkt[%d]: low range\n", i);
         } else {                                       // 7.62928e-05 / 5 = 1.525e-05
            printf("pkt[%d]: high range\n", i);
         }

         if (reroute_bit) {        // attack: 8.10022e-21 / 5 = 1.62e-21
            printf("pkt[%d]: rerouting\n", i);
         } else {                   // 0.000152586 / 5 = 3.05172e-05
            printf("pkt[%d]: normal routing\n", i);
         }
      }
      // this packet misses on the conn_t table
      else  {                       // 4.99985 / 5 = 0.9997
         printf("pkt[%d] misses on the conn_t table\n", i);
         klee_table_write(0);
      }
   }

   return 0;
}
