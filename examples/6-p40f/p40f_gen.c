#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <klee/klee.h>

#define HASH_SIZE 64
#define NUM_LOOP  2

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

typedef struct {
	uint8_t isValid;
	uint8_t version;
	uint8_t ihl;
	uint8_t diffserv;
	uint32_t totalLen;
	uint32_t identification;
	uint8_t flags;
	uint32_t fragOffset;
	uint8_t ttl;
	uint8_t protocol;
	uint32_t hdrChecksum;
	uint32_t srcAddr;
	uint32_t dstAddr;
} ipv4_t;

typedef struct {
	uint8_t isValid;
	uint32_t srcPort;
	uint32_t dstPort;
	uint32_t seqNo;
	uint32_t ackNo;
	uint8_t dataOffset;
	uint8_t res;
	uint8_t ecn;
	uint8_t ctrl;
	uint32_t window;
	uint32_t checksum;
	uint32_t urgentPtr;
} tcp_t;

typedef struct {
   uint8_t ver;
   uint8_t ttl;
   uint16_t olen;
   uint16_t mss;
   uint16_t wsize;
   uint16_t wsize_div_mss;
   uint8_t scale;
   /*
   concatenate kind fields (cast to 4 bits) of tcp options
   */
   uint64_t olayout;

   /* quirks */
   uint8_t quirk_df;
   uint8_t quirk_nz_id;
   uint8_t quirk_zero_id;
   uint8_t quirk_ecn;
   uint8_t quirk_nz_mbz;
   uint8_t quirk_zero_seq;
   uint8_t quirk_nz_ack;
   uint8_t quirk_zero_ack;
   uint8_t quirk_nz_urg;
   uint8_t quirk_urg;
   uint8_t quirk_push;
   uint8_t quirk_opt_zero_ts1;
   uint8_t quirk_opt_nz_ts2;
   uint8_t quirk_opt_eol_nz;
   uint8_t quirk_opt_exws;
   // currently not used because we just reject
   // incorrectly-formatted packets
   uint8_t quirk_opt_bad;
   uint8_t pclass;
} p0f_metadata_t;


typedef struct  {
   uint8_t stop_flag;  // Stop searching for wsize_div_mss

   uint16_t lo;
   uint32_t lo_mss;   // lo * mss
   uint16_t hi;
   uint32_t hi_mss;   // hi * mss

   uint16_t mid;      // (lo + hi) / 2
   uint32_t mid_mss;  // mid * mss
} binary_search_t;

int collect_p0f_metadata(p0f_metadata_t* p0f_metadata, binary_search_t* binary_search, ipv4_t ipv4, tcp_t tcp, uint32_t packet_length){
   p0f_metadata->ver = ipv4.version;  /* ver */
   p0f_metadata->ttl = ipv4.ttl;      /* ttl */

   /* wsize */
   p0f_metadata->wsize = tcp.window;

   /* pclass */
   uint32_t ip_header_length;
   // IPv4 header length without options: 20 bytes
   ip_header_length = 20 + p0f_metadata->olen;
   uint32_t payload_length =
         packet_length        // whole packet
         - ((tcp.dataOffset) << 2) // TCP header
         - ip_header_length                      // IP header
         - 14;                                   // Ethernet header

   p0f_metadata->pclass = (payload_length > 0);

   /* quirks */
   /* IP-specific quirks */
   /* df: "don't fragment" set */
         /* df: "don't fragment" set */
   /* df: "don't fragment" set */
   p0f_metadata->quirk_df = ((ipv4.flags & 0x02) != 0);
   /* id+: df set but IPID not zero */
   p0f_metadata->quirk_nz_id = ((ipv4.flags & 0x02) != 0 && ipv4.identification != 0);
   /* id-: df not set but IPID zero */
   p0f_metadata->quirk_zero_id = ((ipv4.flags & 0x02) == 0 && ipv4.identification == 0);

   /* ecn support */
   p0f_metadata->quirk_ecn = ((ipv4.diffserv & 0x03) != 0);

   /* 0+: "must be zero field" not zero */
   // IPv4 flags == 100, 101, 110, 111
   p0f_metadata->quirk_nz_mbz =  ((ipv4.flags & 0x04) != 0);


   /* TCP-specific quirks */
   /* ecn: explicit congestion notification support */
   // CWR and ECE flags both set, or only NS flag set
   p0f_metadata->quirk_ecn = p0f_metadata->quirk_ecn | ((tcp.ecn & 0x03) != 0 || (tcp.ecn & 0x04) != 0);

   /* seq-: sequence number is zero */
   p0f_metadata->quirk_zero_seq = (tcp.seqNo == 0);
   /* ack-: ACK flag set but ACK number is zero */
   p0f_metadata->quirk_zero_ack = ((tcp.ctrl & 0x10) != 0 && tcp.ackNo == 0);
   /* ack+: ACK flag not set but ACK number nonzero */
   // ignore illegal ack numbers for RST packets
   // see p0f-3.09b:process.c:492
   p0f_metadata->quirk_nz_ack = ((tcp.ctrl & 0x10) == 0 && tcp.ackNo != 0 && (tcp.ctrl & 0x04) == 0);

   /* urgf+: URG flag set */
   p0f_metadata->quirk_urg = ((tcp.ctrl & 0x20) != 0);
   /* uptr+: URG pointer is non-zero, but URG flag not set */
   p0f_metadata->quirk_nz_urg = ((tcp.ctrl & 0x20) == 0 && tcp.urgentPtr != 0);

   /* pushf+: PUSH flag used */
   p0f_metadata->quirk_push =((tcp.ctrl & 0x08) != 0);

   /* wsize_div_mss */
   // Setup for binary search for wsize_div_mss
   // Invariant: wsize_div_mss must be between lo and hi
   // Assume that wsize_div_mss can be no larger than 64

   // Flag for when we should stop searching for wsize_div_mss
   // If mss < 100, set stop flag
   // Do not match on signatures without exact MSS (fp_tcp.c:55)
   binary_search->stop_flag = (p0f_metadata->mss < 100);

   binary_search->lo = 0;
   binary_search->lo_mss = 0;
   binary_search->hi = 1 << 6;  // 64
   binary_search->hi_mss = (p0f_metadata->mss) << 6;  // mss * 64
   return 0;
}


// lo and hi must be even
void binary_search_iter(p0f_metadata_t* p0f_metadata, binary_search_t* binary_search) {
   if (binary_search->stop_flag == 1) {
      return;
   }

   // lo and hi are divisible by 2, so
   // mid = (lo + hi) >> 1 = (lo + hi) / 2
   binary_search->mid = (binary_search->lo + binary_search->hi) >> 1;
   // mid_mss = floor((lo_mss + hi_mss) / 2)
   //         = floor(mss * (lo + hi) / 2)
   //         = mss * (lo + hi) / 2
   //         = mss * mid
   binary_search->mid_mss = (binary_search->lo_mss + binary_search->hi_mss) >> 1;

   uint32_t wsize = p0f_metadata->wsize;

   if (wsize < binary_search->mid_mss) {
      binary_search->hi = binary_search->mid;
      binary_search->hi_mss = binary_search->mid_mss;
   } else if (wsize > binary_search->mid_mss) {
      binary_search->lo = binary_search->mid;
      binary_search->lo_mss = binary_search->mid_mss;
   } else {  // wsize == mid * mss
      p0f_metadata->wsize_div_mss = binary_search->mid;
      binary_search->stop_flag = 1;
   }
}

void binary_search_iter_final(p0f_metadata_t* p0f_metadata, binary_search_t* binary_search) {
   if (binary_search->stop_flag == 1) {
      return;
   }

   // lo and hi are divisible by 2, so
   // mid = (lo + hi) >> 1 = (lo + hi) / 2
   binary_search->mid = (binary_search->lo + binary_search->hi) >> 1;
   // mid_mss = floor((lo_mss + hi_mss) / 2)
   //         = floor(mss * (lo + hi) / 2)
   //         = mss * (lo + hi) / 2
   //         = mss * mid
   binary_search->mid_mss = (binary_search->lo_mss + binary_search->hi_mss) >> 1;

   uint32_t wsize = p0f_metadata->wsize;

   // if wsize is divisible by mss, then
   // wsize must be lo_mss, mid_mss, or hi_mss
   if (wsize == binary_search->lo_mss) {
      p0f_metadata->wsize_div_mss = binary_search->lo;
   }
   if (wsize == binary_search->hi_mss) {
      p0f_metadata->wsize_div_mss = binary_search->hi;
   }
   if (wsize == binary_search->mid_mss) {
      p0f_metadata->wsize_div_mss = binary_search->mid;
   }

}

int nhop(dstip, i){
   if (dstip % 2 == 0) {
      printf("pkt[%d] go to port 1\n", i);
   } else {
      printf("pkt[%d] go to port 2\n", i);
   }
   return 0;
}

int main()
{
   int ret, i;
   int isSYNOnly[NUM_LOOP];
   int isHTTP[NUM_LOOP];
   int isKnown[NUM_LOOP];
   ipv4_t ipv4;
   tcp_t tcp;
   p0f_metadata_t p0f_metadata;
   binary_search_t binary_search;
   int packet_length[NUM_LOOP];
   klee_make_symbolic(isSYNOnly, sizeof isSYNOnly, "isSYNOnly");
   klee_make_symbolic(isHTTP, sizeof isHTTP, "isHTTP");
   klee_make_symbolic(isKnown, sizeof isKnown, "isKnown");
   klee_make_symbolic(&ipv4, sizeof(ipv4_t), "ipv4");
   klee_make_symbolic(&tcp, sizeof(tcp_t), "tcp");
   klee_make_symbolic(packet_length, sizeof packet_length, "packet_length");

   int inDrop[NUM_LOOP];
   klee_make_symbolic(inDrop, sizeof inDrop, "inDrop");

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
         collect_p0f_metadata(&p0f_metadata, &binary_search, ipv4, tcp, packet_length[i]);

         printf("doing binary search..\n");
         binary_search_iter(&p0f_metadata, &binary_search);
         binary_search_iter(&p0f_metadata, &binary_search);
         binary_search_iter(&p0f_metadata, &binary_search);
         binary_search_iter(&p0f_metadata, &binary_search);
         binary_search_iter(&p0f_metadata, &binary_search);
         binary_search_iter_final(&p0f_metadata, &binary_search);

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


      if (ipv4.isValid) {
         if (!inDrop[i]) {
            nhop(ipv4.dstAddr, i);
         }
      }


   }

   return 0;
}

