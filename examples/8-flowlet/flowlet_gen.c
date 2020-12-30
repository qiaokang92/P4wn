#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE 64
#define NUM_LOOP  4

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
   int is_timeout[NUM_LOOP];

   klee_make_symbolic(is_timeout, sizeof is_timeout, "is_timeout");

   // initialize the perflow table
   entry_t table[HASH_SIZE];
   memset((void *)table, 0, sizeof(entry_t) * HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      hash_key_t *key_expr1 = get_key_expr("key1");
      idx_t* idx1 = get_idx("idx1");

      hash_key_t this_key = table[*idx1].key;
      int this_val = table[*idx1].value;

      // miss
      if (this_key.ip == 0) {
         table[*idx1].key = *key_expr1;
         table[*idx1].value = 0;
      }
      else if (this_key.ip == this_key.ip) {
         if (is_timeout[i]) {
            table[*idx1].value += 1;
         }
      } else {
         table[*idx1].key = *key_expr1;
         table[*idx1].value = 0;
      }

      hash_key_t *key_expr2 = get_key_expr("key2");
      idx_t* idx2 = get_idx("idx2");

      // compute ECMP idx using a re-organized key
      klee_assume(key_expr1->ip == key_expr2->ip);
      klee_assume(key_expr1->port == key_expr2->port);
      klee_assume(key_expr1->proto == key_expr2->proto);

      if ((*idx2 + table[*idx1].value) % 2 == 0) {
         printf("sending to port 0\n");
      } else {
         printf("sending to port 1\n");
      }
   }

   return 0;
}
