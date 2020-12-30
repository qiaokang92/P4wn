#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 64
#define NUM_LOOP  5

#define ETH_IPV4 0x0800

// P4 source: https://github.com/jsonch/StarFlow

#define SHORT_VEC(num)        \
void aiRShortVec_##num() {}       \
void aiRWShortVec_##num() {}     \
void tiRWShortVec_##num()           \
{                                     \
   int symbol;                           \
   klee_make_symbolic(&symbol, sizeof symbol, "symbol");        \
   if (symbol) {                                                 \
      aiRShortVec_##num();                                           \
   } else {                                                       \
      aiRWShortVec_##num();                                          \
   }                                                             \
}

#define LONG_VEC(num)        \
void aiRLongVec_##num() {}       \
void aiRWLongVec_##num() {}     \
void tiRWLongVec_##num()           \
{                                     \
   int symbol;                           \
   klee_make_symbolic(&symbol, sizeof symbol, "symbol");        \
   if (symbol) {                                                 \
      aiRLongVec_##num();                                           \
   } else {                                                       \
      aiRWLongVec_##num();                                          \
   }                                                             \
}

SHORT_VEC(0)
SHORT_VEC(1)
SHORT_VEC(2)
SHORT_VEC(3)

LONG_VEC(0)
LONG_VEC(1)
LONG_VEC(2)
LONG_VEC(3)
LONG_VEC(4)
LONG_VEC(5)
LONG_VEC(6)
LONG_VEC(7)
LONG_VEC(8)
LONG_VEC(9)
LONG_VEC(10)
LONG_VEC(11)
LONG_VEC(12)
LONG_VEC(13)
LONG_VEC(14)
LONG_VEC(15)
LONG_VEC(16)
LONG_VEC(17)
LONG_VEC(18)
LONG_VEC(19)
LONG_VEC(20)
LONG_VEC(21)
LONG_VEC(22)
LONG_VEC(23)

void vector_actions()
{
   tiRWShortVec_0();
   tiRWShortVec_1();
   tiRWShortVec_2();
   tiRWShortVec_3();
/*
   tiRWLongVec_0();
   tiRWLongVec_1();
   tiRWLongVec_2();
   tiRWLongVec_3();
   tiRWLongVec_4();
   tiRWLongVec_5();
   tiRWLongVec_6();
   tiRWLongVec_7();
   tiRWLongVec_8();
   tiRWLongVec_9();
   tiRWLongVec_10();
   tiRWLongVec_11();
   tiRWLongVec_12();
   tiRWLongVec_13();
   tiRWLongVec_14();
   tiRWLongVec_15();
   tiRWLongVec_16();
   tiRWLongVec_17();
   tiRWLongVec_18();
   tiRWLongVec_19();
   tiRWLongVec_20();
   tiRWLongVec_21();
   tiRWLongVec_22();
   tiRWLongVec_23();
*/
}

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
   int ether_type[NUM_LOOP];

   klee_make_symbolic(ether_type, sizeof ether_type, "eth_type");

   // Initialize a data plane cache
   entry_t table[HASH_SIZE];
   memset((void *)table, 0, sizeof(entry_t) * HASH_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      // metadata
      int inProcessing = 0;
      int collision = 0;
      int match = 0;

      printf("=== Processing pkt %d ===\n", i);

      if (ether_type[i] == ETH_IPV4) {
         hash_key_t *key_expr = get_key_expr("key");
         idx_t *idx = get_idx("idx");

         // read the key and value from the table.
         hash_key_t this_key = table[*idx].key;

         // collision
         if (this_key.ip != 0 && this_key.ip != key_expr->ip) {
            table[*idx].key = *key_expr;
            collision = 1;
         }

         // miss
         else if (this_key.ip == 0) {
            table[*idx].key = *key_expr;
         }

         // hit
         else {

         }

         inProcessing = 1;
      }

      // set match flag based on hash table access
      // p4src/mainStarFlow.p4#L78
      if (inProcessing && collision == 0) {
         match = 1;
      }

      // do vector stuff
      if (inProcessing == 1) {
         vector_actions();
      }

      // attack target line: 186(if)
      if (inProcessing && match == 0) {
         printf("evicting an entry!\n");
      }
   }

   return 0;
}
