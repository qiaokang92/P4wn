#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE     64
#define NUM_LOOP      5
#define DUPACK_THRESH 4

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

int main()
{
   int i, ret;

   int dupAck[NUM_LOOP];
   klee_make_symbolic(dupAck, sizeof dupAck, "dupAck");
   int low_high[NUM_LOOP];
   klee_make_symbolic(low_high, sizeof low_high, "low_high");

   entry_t table[HASH_SIZE];
   memset((void *)table, 0, sizeof(entry_t) * HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);
      int reroute_bit = 0;

      hash_key_t *key_expr = get_key_expr("key");
      idx_t* idx = get_idx("idx");

      hash_key_t this_key = table[*idx].key;
      int this_val = table[*idx].value;

      // miss the cache
      if (this_key.ip == 0) {
         table[*idx].key = *key_expr;
         table[*idx].value = 0;
      }

      // hits the table
      else {
         if (dupAck[i]) {
            table[*idx].value += 1;
         }

         if (table[*idx].value >= DUPACK_THRESH) {
            reroute_bit = 1;
         }

         if (reroute_bit) {
            printf("pkt[%d]: rerouting\n", i);
         }
      }
   }

   return 0;
}
