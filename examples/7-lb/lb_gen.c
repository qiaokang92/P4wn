#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE  64
#define NUM_LOOP 1

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
   int ret, i;
   int pktID[NUM_LOOP];
   klee_make_symbolic(pktID, sizeof pktID, "pktID");

   for (i = 0; i < NUM_LOOP; i ++) {
      hash_key_t *key_expr = get_key_expr("key");
      idx_t* idx = get_idx("idx");
      // ecmp_group.apply();
      uint8_t ecmp_select;
      uint8_t egress_port;
      if (*idx%2 == 0){
         ecmp_select = 1;
      } else {
         ecmp_select = 2;
      }

      // ecmp_nhop.apply();
      if (ecmp_select == 1){
         printf("forwarding to port 1\n");
         egress_port = 1;
      } else {
         printf("forwarding to port 2\n");
         egress_port = 2;
      }

      // send_frame.apply();
      if (egress_port == 1){
         printf("rewrite_mac to port 1\n");
      } else {
         printf("rewrite_mac to port 2\n");
      }
   }

   return 0;
}
