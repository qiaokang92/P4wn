#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define HASH_SIZE 65536
#define BF_SIZE   65536
#define NUM_LOOP  3


// =======================================
// ======== switch control plane =========
// =======================================

// nothing here

// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   int ret, i;
   int isSYNOnly[NUM_LOOP];
   int isHTTP[NUM_LOOP];
   klee_make_symbolic(isSYNOnly, sizeof isSYNOnly, "isSYNOnly");
   klee_make_symbolic(isHTTP, sizeof isHTTP, "isHTTP");

   // the big result_match table
   klee_ma_init();
   klee_bf_init(BF_SIZE);

   for (i = 0; i < NUM_LOOP; i ++) {
      printf("=== Processing pkt %d ===\n", i);
      klee_update_iter(i);
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

         ret = klee_ma_access();
         if (ret == GREYBOX_MISS) {        // 0.0300444 / 2 = 0.015
            printf("sending SYN packet to CPU\n");
            klee_bf_access();
         }
      }

      // Query: ratio of HTTP packets (dstPort == 80)
      if (isHTTP[i]) {              // 0.0317333 / 2 = 0.0168
         ret = klee_bf_read();
         if (ret == GREYBOX_HIT) {        // 7.06512e-17 / 2 = 3.53256e-17
            printf("sending HTTP packet to CPU\n");
         }
      }
   }

   return 0;
}

