#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
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
   int ret, i;
   int isSYNOnly[NUM_LOOP];
   int isHTTP[NUM_LOOP];
   int isKnown[NUM_LOOP];
   klee_make_symbolic(isSYNOnly, sizeof isSYNOnly, "isSYNOnly");
   klee_make_symbolic(isHTTP, sizeof isHTTP, "isHTTP");
   klee_make_symbolic(isKnown, sizeof isKnown, "isKnown");

   // init bf
   bf_t bf;
   memset((void *)&bf, 0, sizeof(bf_t));

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);

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

      // Query: ratio of SYN-only packet
      // SYN-only means:
      // if (hdr.tcp.ctrl == SYN_FLAG
      //     || hdr.tcp.ctrl == (SYN_FLAG | PSH_FLAG)
      //     || hdr.tcp.ctrl == (SYN_FLAG | URG_FLAG)
      //     || hdr.tcp.ctrl == (SYN_FLAG | PSH_FLAG | URG_FLAG))
      if (isSYNOnly[i]) {         // 0.0901333 / 2 = 0.45
         // this function call doesn't fork branches
         printf("calling collect_p0f_metadata()\n");

         // binary_search_iters: ignored
         printf("doing binary search..\n");

         if (isKnown[i] == 0) {
            printf("unknown signature of SYN, sending to CPU\n");
            bf.bits[*idx1] = 1;
            bf.bits[*idx2] = 1;
            bf.bits[*idx3] = 1;
         }
      }

      // send following HTTP packets to CPU
      if (isHTTP[i]) {
         int bf_hit = (bf.bits[*idx1] && bf.bits[*idx2] && bf.bits[*idx3])?
                      1:0;
         if (bf_hit) {
            printf("sending HTTP packet to CPU\n");
         }
      }
   }

   return 0;
}

