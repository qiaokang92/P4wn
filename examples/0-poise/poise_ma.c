#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define NUM_LOOP  5
#define NUM_FLOWS 10

// Note: This program only contains the logic of M/A table for testing purpoise,
// No cache in this program

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
   int is_context[NUM_LOOP];
   int context[NUM_LOOP];

   klee_make_symbolic(is_context, sizeof is_context, "isCtx");
   klee_make_symbolic(context, sizeof context, "ctx");

   // Initialze the conn_t MA table, also modeled as a greybox
   // TODO: Do we want to model the max size of MA tables?
   klee_ma_init(NUM_FLOWS);

   for (i = 0; i < NUM_LOOP; i ++) {
      // decision get from the cache
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

      // Check the conn_t table
      ret = klee_ma_access();

      // this packet hits on the conn_t table
      if (ret == GREYBOX_HIT) {
         // this call may fork two branches: dec = 0 or 1
         dec = klee_ma_read();
         printf("pkt[%d] hits on the conn_t table, dec=%d\n", i, dec);
      }

      // this packet misses on the conn_t table
      else if (ret == GREYBOX_MISS) {
         if (is_context[i]) {
            cp_ma_table_insert(this_dec);
         }
         dec = POISE_DEC_DENY;
         printf("pkt[%d] misses on the conn_t table, dec=%d\n", i, dec);
      }

      // enforce the decision read from conn_t
      if (!is_context[i]) {
         if (dec == POISE_DEC_ALLOW) {
            printf("setting port to %d\n", 0);
            port = POISE_PORT_ALLOW;
         } else {
            port = POISE_DEC_DENY;
            printf("setting port to %d\n", 1);
         }
      }

      printf("=== %s pkt[%d] sent to port %d ===\n",
             is_context[i] ? "context" : "data", i, port);
   }

   return 0;
}
