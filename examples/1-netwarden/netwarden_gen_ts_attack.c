#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE  64
#define NUM_LOOP   10
#define CMIN_THRES 10

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
   int i;
   int ret;

   uint64_t ipd64[NUM_LOOP];
   klee_make_symbolic(ipd64, sizeof ipd64, "ipd64");

   // initialize CMIN
   entry_t cmin1[HASH_SIZE];
   entry_t cmin2[HASH_SIZE];
   entry_t cmin3[HASH_SIZE];

   memset((void *)cmin1, 0, sizeof(entry_t) * HASH_SIZE);
   memset((void *)cmin2, 0, sizeof(entry_t) * HASH_SIZE);
   memset((void *)cmin3, 0, sizeof(entry_t) * HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

      uint32_t ipd32 = ipd64[i] >> 16;

      hash_key_t *key_expr1 = get_key_expr("key1");
      idx_t* idx1 = get_idx("idx1");
      hash_key_t *key_expr2 = get_key_expr("key2");
      idx_t* idx2 = get_idx("idx2");
      hash_key_t *key_expr3 = get_key_expr("key3");
      idx_t* idx3 = get_idx("idx3");

      /*
      klee_assume(key_expr1->ip == key_expr2->ip);
      klee_assume(key_expr2->ip == key_expr3->ip);
      klee_assume(key_expr1->port == key_expr2->port);
      klee_assume(key_expr2->port == key_expr3->port);
      klee_assume(key_expr1->proto == key_expr2->proto);
      klee_assume(key_expr2->proto == key_expr3->proto);
      */

      if (ipd32 > 4) {
         printf("pkt[%d] enlarging cmin\n", i);
         cmin1[*idx1].value ++;
         cmin2[*idx2].value ++;
         cmin3[*idx3].value ++;
      }

      // we don't have to check hash key in CMIN
      int count1 = cmin1[*idx1].value;
      int count2 = cmin2[*idx2].value;
      int count3 = cmin3[*idx3].value;

      int count = MIN(MIN(count1, count2), count3);

      if (count >= CMIN_THRES) {
         // send IPDs to CPU
         printf("sending IPDs to CPU\n");
      }
   }

   return 0;
}
