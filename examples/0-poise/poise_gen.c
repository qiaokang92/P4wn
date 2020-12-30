#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE 64
#define NUM_LOOP  2

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

typedef struct bf_t {
   uchar bits[HASH_SIZE];
} bf_t;

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

int main()
{
   int i;
   int ret;
   int isCtx[NUM_LOOP];
   int context[NUM_LOOP];
   int isNewFlow[NUM_LOOP];

   klee_make_symbolic(isCtx, sizeof isCtx, "isCtx");
   klee_make_symbolic(context, sizeof context, "ctx");
   klee_make_symbolic(isNewFlow, sizeof isNewFlow, "isNewFlow");

   entry_t table[HASH_SIZE];
   memset((void *)table, 0, sizeof(entry_t) * HASH_SIZE);

   bf_t bf;
   memset((void *)&bf, 0, sizeof(bf_t));

   for (i = 0; i < NUM_LOOP; i ++) {
      // decision get from the cache
      int dec      = POISE_DEC_INVALID;
      // decision get from security context
      int this_dec = POISE_DEC_INVALID;
      int port = POISE_PORT_INVALID;

      hash_key_t *key_expr = get_key_expr("key");
      idx_t *idx = get_idx("idx");

      hash_key_t *key_expr1 = get_key_expr("key1");
      idx_t *idx1 = get_idx("idx1");
      hash_key_t *key_expr2 = get_key_expr("key2");
      idx_t *idx2 = get_idx("idx2");
      hash_key_t *key_expr3 = get_key_expr("key3");
      idx_t *idx3 = get_idx("idx3");
      /*
      klee_assume(key_expr1->ip == key_expr2->ip);
      klee_assume(key_expr2->ip == key_expr3->ip);
      klee_assume(key_expr1->port == key_expr2->port);
      klee_assume(key_expr2->port == key_expr3->port);
      klee_assume(key_expr1->proto == key_expr2->proto);
      klee_assume(key_expr2->proto == key_expr3->proto);
      */
      printf("=== Processing pkt %d ===\n", i);

      if (isCtx[i]) {      // 0.3 / 3 = 0.1
         if (context[i] == 0) {   // 0.03 / 3 = 0.01
            this_dec = POISE_DEC_ALLOW;
         } else {                 // 0.27 / 3 = 0.09
            this_dec = POISE_DEC_DENY;
         }
         port = POISE_PORT_CTX;
      }

      // this packet hits on the conn_t table
      if (isNewFlow[i] == 0) {
         printf("pkt[%d] hits on the conn_t table\n", i);
      }

      // miss on the conn_t table
      else {
         printf("pkt[%d] misses on the conn_t table\n", i);

         // Invoke CP to insert a new entry
         if (isCtx[i]) {      // 0.03 / 3 = 0.01
            if (ret == GREYBOX_COL || ret == GREYBOX_MISS) {
               printf("pkt %d inserting %d to MA table\n", i, this_dec);
            }
         }

         hash_key_t this_key = table[*idx].key;
         dec = table[*idx].value;

         // miss the cache
         if (this_key.ip == 0) {
            // get dec from cache
            if (isCtx[i]) {
               table[*idx].key = *key_expr;
               table[*idx].value = this_dec;
            } else {
               dec = POISE_DEC_DENY;
            }
         }

         // hit
         else if (this_key.ip == key_expr->ip) {
            // do nothing
         }

         // collision
         else {
            if (isCtx[i]) {
               if (dec == POISE_DEC_DENY) {
                  bf.bits[*idx1] = 1;
                  bf.bits[*idx2] = 1;
                  bf.bits[*idx3] = 1;
               }
            } else {
               int bf_hit = (bf.bits[*idx1] == 1 && bf.bits[*idx2] == 1 &&
                             bf.bits[*idx3] == 1) ? 1 : 0;
               if (bf_hit == 0) {
                  printf("recirculating this pkt!\n");
               } else {
                  dec = POISE_DEC_DENY;
               }
            }
         }
      }

      // enforce the decision read from conn_t or the cache
      if (!isCtx[i]) {
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
