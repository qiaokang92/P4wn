#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define BF_SIZE   256
#define NUM_LOOP  3


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
   uint8_t is_context[NUM_LOOP];
   uint8_t context[NUM_LOOP];
   uint64_t tstamp[NUM_LOOP];

   klee_make_symbolic(is_context, sizeof is_context, "ctx");
   klee_make_symbolic(context, sizeof context, "ctx_deny");
   klee_make_symbolic(tstamp, sizeof tstamp, "tstamp");

   // Initialize the BF, modeled as a greybox
   klee_bf_init(BF_SIZE);

   // Initialize the cache, modeled as a greybox
   klee_table_init(HASH_SIZE);


   // Initialze the conn_t MA table, also modeled as a greybox
   klee_ma_init();

   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      int dec      = POISE_DEC_INVALID;
      // decision get from security context
      int this_dec = POISE_DEC_INVALID;
      int port = POISE_PORT_INVALID;

      printf("=== Processing pkt %d ===\n", i);

      // Query: what's the distribution of ctx packet
      if (is_context[i]) {
         // Query: what's the distribution of contexts
         if (context[i] == 0) {
            this_dec = POISE_DEC_ALLOW;
         } else {
            this_dec = POISE_DEC_DENY;
         }
         // send context packets to a special port
         port = POISE_PORT_CTX;
      }

      // apply(split_tstamp_tab);
      uint32_t tstamp_high32 = tstamp[i] >> 32;

      // ============== FULL CONN TABLE ==============
      ret = klee_ma_access();

      // this packet hits on the conn_t table
      if (ret == GREYBOX_HIT) {
         // this call may fork two branches: dec = 0 or 1
         dec = klee_ma_read();
         printf("pkt[%d] hits on the conn_t table, dec=%d\n", i, dec);
      }

      // this packet misses on the conn_t table
      else {
         printf("pkt[%d] misses on the conn_t table, dec=%d\n", i, dec);

         // ============== CACHE ==============
         // klee_table_access may fork 3 branches: hit/miss/col,
         // table content is not changed in this step
         ret = klee_table_access();
         printf("pkt[%d]: %d from klee_table_access\n", i, ret);

         // klee_table_read may fork 1 or 2 paths, based on what value we
         // can read from the table
         dec = klee_table_read();

         // klee_table_write doesn't fork paths, it just updates the table
         if (is_context[i]) {
            klee_table_write(this_dec);
         }

         // Invoke CP to insert a new entry
         if (is_context[i]) {
            if (ret == GREYBOX_COL || ret == GREYBOX_MISS) {
               printf("pkt %d inserting %d to MA table\n", i, this_dec);
               cp_ma_table_insert(this_dec);
            }
         }


         // collision on the cache: we should check the greybox
         if (ret == GREYBOX_COL) {
            if (is_context[i]) {
               if (dec == POISE_DEC_DENY) {
                  // this call writes to BF and returns 4 paths.
                  ret = klee_bf_access();
               }
            } else {
               // this call reads BF and forks 2 paths (hit or miss)
               // different from klee_bf_access, this call doesn't change BF
               ret = klee_bf_read();
               if (ret == GREYBOX_HIT) {
                  dec = POISE_DEC_DENY;
               } else {
                  printf("recirculating this packet!\n");
               }
            }
         }

         // misses on the cache
         // this is an unseen packet, we should set the decision to unseen
         if (ret == GREYBOX_MISS) {
            dec = POISE_DEC_DENY;
         }
      }

      // enforce the decision read from conn_t or the cache
      // assert(dec != POISE_DEC_INVALID);
      if (!is_context[i]) {
         if (dec == POISE_DEC_ALLOW) {
            port = POISE_PORT_ALLOW;
         } else {
            port = POISE_DEC_DENY;
         }
      }

      //printf("=== %s pkt[%d] sent to port %d ===\n",
      //       is_context[i] ? "context" : "data", i, port);
   }

   return 0;
}
