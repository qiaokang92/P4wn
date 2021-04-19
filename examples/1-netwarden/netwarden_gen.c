#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <klee/klee.h>

#define HASH_SIZE  64
#define NUM_LOOP   3
#define CMIN_THRES 2
#define PORT_SERVER 1
#define PORT_CLIENT 0
#define CPU_OUT 2

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

   int isLargeIPD[NUM_LOOP];
   klee_make_symbolic(isLargeIPD, sizeof isLargeIPD, "isLargeIPD");
   uint64_t tstamp[NUM_LOOP];
   uint32_t seq[NUM_LOOP];
   uint32_t ack[NUM_LOOP];
   uint16_t dataoffset[NUM_LOOP];
   uint16_t totallen[NUM_LOOP];
   uint32_t ingress_port[NUM_LOOP];
   uint32_t highwater[NUM_LOOP];
   uint32_t IPID[NUM_LOOP];
   uint32_t dstIP[NUM_LOOP];
   uint32_t dataCPU[NUM_LOOP];


   klee_make_symbolic(tstamp, sizeof tstamp, "tstamp");
   klee_make_symbolic(seq, sizeof seq, "seq");
   klee_make_symbolic(ack, sizeof ack, "ack");
   klee_make_symbolic(dataoffset, sizeof dataoffset, "dataoffset");
   klee_make_symbolic(totallen, sizeof totallen, "totallen");
   klee_make_symbolic(ingress_port, sizeof ingress_port, "ingress_port");
   klee_make_symbolic(highwater, sizeof highwater, "highwater");
   klee_make_symbolic(IPID, sizeof IPID, "IPID");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");
   klee_make_symbolic(dataCPU, sizeof dataCPU, "dataCPU");


   // initialize CMIN
   entry_t cmin1[HASH_SIZE];
   entry_t cmin2[HASH_SIZE];
   entry_t cmin3[HASH_SIZE];

   memset((void *)cmin1, 0, sizeof(entry_t) * HASH_SIZE);
   memset((void *)cmin2, 0, sizeof(entry_t) * HASH_SIZE);
   memset((void *)cmin3, 0, sizeof(entry_t) * HASH_SIZE);

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

      // apply (split_tstamp_high32_tab); //obtain timestamp for this packet
      uint32_t tstamp_high32 = tstamp[i] >> 32;
      // apply (split_seq_low16_tab);
      uint16_t seq_low16 = seq[i] >> 16;
      // apply (split_ack_low16_tab);
      uint16_t ack_low16 = ack[i] >> 16;
      // apply (convert_dataoffset_to_32_tab); // convert dataoffset to 32 bits
      uint32_t dataoffset32 = dataoffset[i];
      // apply (convert_totallen_to_32_tab); // convert totallen to 32 bits
      uint32_t totallen32 = totallen[i];

      int count1 = cmin1[*idx1].value;
      int count2 = cmin2[*idx2].value;
      int count3 = cmin3[*idx3].value;

      int count = MIN(MIN(count1, count2), count3);


      if (isLargeIPD[i]) {
         if (ingress_port[i] == PORT_SERVER){
            cmin1[*idx1].value ++;
            cmin2[*idx2].value ++;
            cmin3[*idx3].value ++;
            if (count >= CMIN_THRES) {
               printf("sending IPDs to CPU\n");
            }
         } else {
            dataoffset[i] = dataoffset[i] << 2;
            highwater[i] = totallen[i] + seq[i];
            if (ingress_port[i] == PORT_CLIENT){
               printf("compute RTT!\n");
            } else {
               highwater[i] -= dataoffset[i];
               if (dataCPU[i] == 0){
                  printf("update RTT!\n");
               }
            }
         }
      } else{
         printf("pkt[%d] misses on the conn_t table\n", i);
      }

      // forwarding
      if (dstIP[i] % 2 == 0) {
         printf("pkt[%d] go to port 1\n", i);
      } else {
         printf("pkt[%d] go to port 2\n", i);
      }
   }

   return 0;
}
