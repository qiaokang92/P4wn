#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>
// #include "starflow.h" // To prevent the file from discrupting the line num

#define HASH_SIZE 65536
#define NUM_LOOP  2

#define ETH_IPV4 0x0800
#define ROLLOVER_FLAG 2
#define SHORT_LEN 2
#define SF_MONITOR_PORT 3
#define SF_RECIRC_PORT 2
#define MASK 0xffffffff
#define ENTRY_NUM 2

// P4 source: https://github.com/jsonch/StarFlow

int main()
{
   int i, ret;
   uint8_t is_ipv4[NUM_LOOP];
   uint8_t egress_port[NUM_LOOP];
   uint8_t is_valid_sfExportStart[NUM_LOOP];

   klee_make_symbolic(is_ipv4, sizeof is_ipv4, "ipv4");
   klee_make_symbolic(egress_port, sizeof egress_port, "egress_port");
   klee_make_symbolic(is_valid_sfExportStart,
                      sizeof is_valid_sfExportStart,
                      "is_valid_sfExportStart");

   // Initialize a data plane cache,  modeled as a greybox
   klee_table_init(HASH_SIZE);

   uint8_t matchFlag[NUM_LOOP];
   uint32_t pktId[NUM_LOOP];
   uint32_t stackPtr[NUM_LOOP]={0};

   klee_make_symbolic(matchFlag, sizeof matchFlag, "matchFlag");
   klee_make_symbolic(pktId, sizeof pktId, "pktId");

   uint32_t siStackPop[1]; siStackPop[0] = 1;
   // klee_make_symbolic(siStackPop, sizeof siStackPop, "siStackPop");
   // uint32_t riStack[16];
   // klee_make_symbolic(riStack, sizeof riStack, "riStack");

   uint32_t widePtr[NUM_LOOP];
   uint32_t lastPktId[NUM_LOOP];
   klee_make_symbolic(widePtr, sizeof widePtr, "widePtr");
   klee_make_symbolic(lastPktId, sizeof lastPktId, "lastPktId");

   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      // metadata
      int inProcessing = 0;
      int collision = 0;
      int match = 0;

      // Query the ratio of IPV4 packets at line 36
      if (is_ipv4[i]) {
         // Check the cache
         ret = klee_table_access();
         if (ret == GREYBOX_COL) {
            collision = 1;
         }

         // add new flow into the data plane table
         if (ret != GREYBOX_HIT) {
            klee_table_write(1);
         }
         inProcessing = 1;
      }

      // set match flag based on hash table access
      // p4src/mainStarFlow.p4#L78
      if (inProcessing) {
         if (collision == 0) {
            match = 1;
         }
      }


      if (inProcessing == 1) {
         // apply(tiDecrementStackTop);
         uint32_t matchFlag_mask = matchFlag[i] & MASK;
         uint32_t pktId_mask = pktId[i] & MASK;

         if (matchFlag_mask == 1) {
            if (pktId_mask == SHORT_LEN) {
               if (siStackPop[0] != 0) {
                  stackPtr[i] = siStackPop[0];
                  siStackPop[0] -= 1;
               }
            }
         }


         // write in table tiUpdateStackArray and tiUpdateWidePointerArray
         // apply(tiUpdateStackArray);
         if (stackPtr[i]!=0){
            // widePtr = riStack[stackPtr];
            printf("siStackRead.execute_stateful_alu(sfMeta.stackPtr); \n");
         } else {
            printf("aiNoOp!\n");
         }

         // apply(tiUpdateWidePointerArray);
         if (pktId_mask==2){ // aiSavePtr
            printf("siSavePtr.execute_stateful_alu(sfMeta.hashVal);\n");
         }

         if (pktId_mask == 0){ // aiLoadPtr
            printf("siLoadPtr.execute_stateful_alu(sfMeta.hashVal);\n");
         }
      }
      else {
         siStackPop[0] += 1;
         printf("apply(tiFreeStackArray);\n");
      }

      // do vector stuff
      if (inProcessing == 1) {
         printf("vector_actions();"); // vector_actions();
      }

      if (inProcessing == 1) {
         uint32_t widePtr_mask = (widePtr[i] & MASK);
         uint32_t lastPktId_mask = (lastPktId[i] & MASK);
         uint32_t widePtr_mask_0 = (widePtr[i] & MASK);

         if (match == 0) {
            printf("evicting an entry!\n");

            // implement the two match-action tables?
            // apply(tiEvictDecision);
            if (widePtr_mask==0){
               if (lastPktId_mask==0){
                  printf("aiNoOp!\n");
               }
               if (lastPktId_mask==1){
                  printf("aiShortEvict!\n");
               }
               if (lastPktId_mask==ROLLOVER_FLAG){
                  printf("aiShortEvict!\n");
               }
            }

            if (widePtr_mask_0==0){
               if (lastPktId_mask==0){
                  printf("aiLongEvict!\n");
               }
               if (lastPktId_mask==1){
                  printf("aiLongEvict!\n");
               }
               if (lastPktId_mask==ROLLOVER_FLAG){
                  printf("aiLongEvict!\n");
               }
            }
         }
         else {
            // apply(tiRolloverDecision);
            if (widePtr_mask==0){
               if (lastPktId_mask==0){
                  printf("aiShortRollover!\n");
               }
               if (lastPktId_mask==1){
                  printf("aiShortRollover!\n");
               }
               if (lastPktId_mask==ROLLOVER_FLAG){
                  printf("aiShortRollover!\n");
               }
            }

            if (widePtr_mask_0==0){
               if (lastPktId_mask==ROLLOVER_FLAG){
                  printf("aiLongRollover!\n");
               }
            }
         }
      }

      is_valid_sfExportStart[i] = 1; // assume all exported headers are valid.
      if (is_valid_sfExportStart[i] == 1){
         if (egress_port[i] == SF_MONITOR_PORT){
            printf("aeDoNothing!\n");
         } else {
            printf("aeRemoveSfHeader!\n");
         }

         if (egress_port[i] == SF_RECIRC_PORT){
            printf("aeDoNothing!\n");
         } else {
            printf("aeRemoveSfHeader!\n");
         }
      }

      printf("=== pkt %d finished ===\n", i);
   }

   return 0;
}
