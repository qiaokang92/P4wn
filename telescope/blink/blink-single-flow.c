#include <stdio.h>
#include <klee/klee.h>

#define NUM_PKT     4
#define ALARM_THRES NUM_PKT
#define REAL_THRES  32

typedef unsigned char uchar;
typedef unsigned int uint;

int main()
{
   int i = 0;
   int sum = 0;
   // input packets
   // 0: normal; 1: retransmission
   uchar pkt_re_flag[NUM_PKT];

   // Make the input symbolic.
   klee_make_symbolic(pkt_re_flag, sizeof pkt_re_flag, "pkt_re_flag");

   klee_telescope_init(ALARM_THRES, REAL_THRES);

   // iteration for each packet
   for (i = 0; i < NUM_PKT; i ++) {
     // printf("prcessing packet %d\n", i);

     klee_assume(pkt_re_flag[i] <= 1);
     klee_assume(pkt_re_flag[i] >= 0);

     if (pkt_re_flag[i]) {
        sum += 1;
     }

     if (sum >= ALARM_THRES) {
        printf("%s\n", "alarming!");
     }

     klee_telescope_pkt(i, sum);
   }

   klee_telescope(sum);

   return 0;
}
