#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE  64
#define NUM_LOOP   4
#define CMIN_THRES 2

#define NC_READ_REQUEST     0
#define NC_READ_REPLY       1
#define NC_HOT_READ_REQUEST 2
#define NC_WRITE_REQUEST    4
#define NC_WRITE_REPLY      5
#define NC_UPDATE_REQUEST   8
#define NC_UPDATE_REPLY     9

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
   // packet headers
   int op[NUM_LOOP];
   klee_make_symbolic(op, sizeof op, "op");

   int i;
   int ret;

   // init bf and cmin
   bf_t bf;
   memset((void *)&bf, 0, sizeof(bf_t));

   entry_t cmin1[HASH_SIZE];
   entry_t cmin2[HASH_SIZE];
   entry_t cmin3[HASH_SIZE];

   memset((void *)cmin1, 0, sizeof(entry_t) * HASH_SIZE);
   memset((void *)cmin2, 0, sizeof(entry_t) * HASH_SIZE);
   memset((void *)cmin3, 0, sizeof(entry_t) * HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
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

      // process_cache();
      int exist;
      klee_make_symbolic(&exist, sizeof exist, "exist");

      // Query the ratio of hit, NetCache paper says it's less than 50%
      if (exist) {
         // Suppose 90%
         if (op[i] == NC_READ_REQUEST) {     // 2.25 / 5  = 0.45
            printf("checking cache valid\n");
         } else {                              // 0.25 / 5 = 0.05
            printf("setting cache valid\n");
         }
      }

      // process_value();
      if (exist) {
         // Suppose 90%
         if (op[i] == NC_READ_REQUEST) {              // 2.25 / 5 = 0.45
            printf("reading value from cache\n");
         } else {                                     // 0.25 / 5 = 0.05
            printf("writing value to cache\n");
         }
      }

      // ipv4_route();

      // egress
      if (op[i] == NC_READ_REQUEST && exist == 0) {       // 2.25 / 5 = 0.45
         // heavy_hitter();
         cmin1[*idx1].value ++;
         cmin2[*idx2].value ++;
         cmin3[*idx3].value ++;

         int count1 = cmin1[*idx1].value;
         int count2 = cmin2[*idx2].value;
         int count3 = cmin3[*idx3].value;
         int count = MIN(MIN(count1, count2), count3);

         if (count >= CMIN_THRES) {
            printf("hot key detected, checking BF\n");
            int bf_hit = (bf.bits[*idx1] == 1 && bf.bits[*idx2] == 1 && bf.bits[*idx3] == 1) ? 1 : 0;
            if (bf_hit == 0) {
               printf("sending HH report to CPU\n");
               bf.bits[*idx1] = 1;
               bf.bits[*idx2] = 1;
               bf.bits[*idx3] = 1;
            }
         }
      }
   }

   return 0;
}
