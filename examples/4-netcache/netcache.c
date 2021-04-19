#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

#define CMIN_SIZE  256
#define BF_SIZE    512
#define NUM_LOOP   2
#define CMIN_THRES 16

#define NC_READ_REQUEST     0
#define NC_READ_REPLY       1
#define NC_HOT_READ_REQUEST 2
#define NC_WRITE_REQUEST    4
#define NC_WRITE_REPLY      5
#define NC_UPDATE_REQUEST   8
#define NC_UPDATE_REPLY     9

// =======================================
// ======== switch control plane =========
// =======================================
int cp_ma_table_insert(int val)
{
   // this operation inserts one entry to the MA table
   // following klee_access_ma calls should see a different MA table
   klee_ma_insert(val);
   return 0;
}

// =======================================
// ========= switch data plane ===========
// =======================================

int main()
{
   // packet headers
   uint8_t is_read[NUM_LOOP];
   uint8_t instance_type[NUM_LOOP];
   uint8_t egress_port[NUM_LOOP];
   uint8_t dstIP[NUM_LOOP];
   klee_make_symbolic(is_read, sizeof is_read, "nc_read");
   klee_make_symbolic(instance_type, sizeof instance_type, "instance_type");
   klee_make_symbolic(egress_port, sizeof egress_port, "egress_port");
   klee_make_symbolic(dstIP, sizeof dstIP, "dstIP");

   uint8_t is_exist[NUM_LOOP];
   uint8_t is_exist_read[NUM_LOOP];
   uint8_t is_valid[NUM_LOOP];
   klee_make_symbolic(is_exist, sizeof is_exist, "nc_exist");
   klee_make_symbolic(is_exist_read, sizeof is_exist_read, "nc_exist_read");
   klee_make_symbolic(is_valid, sizeof is_valid, "nc_valid");

   int i;
   int ret;

   // Initialize the BF, modeled as a greybox
   klee_bf_init(BF_SIZE);

   klee_cmin_init(CMIN_SIZE);
   for (i = 0; i < NUM_LOOP; i ++) {
      klee_update_iter(i);
      // process_cache();
      // Query the ratio of hit, NetCache paper says it's less than 50%
      if (is_exist[i]) {
         // Suppose 90%
         if (is_read[i]) {
            printf("checking cache valid\n");
         }

         // The original version is else if (is_write).
         else {
            printf("setting cache valid\n");
            is_valid[i] = 1;
         }
      }


      // process_value();
      if (is_read[i]) {
         if (is_valid[i]) {
            // apply (reply_read_hit_before);
            printf("apply (reply_read_hit_before);\n");
         }
      }

      // HANDLE_VALUE(1, 2)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }

      // HANDLE_VALUE(2, 3)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }

      // HANDLE_VALUE(3, 4)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }
      // HANDLE_VALUE(4, 5)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }

      // HANDLE_VALUE(5, 6)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }

      // HANDLE_VALUE(6, 7)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }
      // HANDLE_VALUE(7, 8)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }

      // HANDLE_VALUE(8, 9)
      if (is_exist[i]) {
         if (is_read[i]) {
            if (is_valid[i]) {
               printf("apply (add_value_header_##1);\n");
               printf("apply (read_value_##1##_1);\n");
               printf("apply (read_value_##1##_2);\n");
               printf("apply (read_value_##1##_3);\n");
               printf("apply (read_value_##1##_4);\n");
            }
         }
         else {
            printf("apply (write_value_##1##_1);\n");
            printf("apply (write_value_##1##_2);\n");
            printf("apply (write_value_##1##_3);\n");
            printf("apply (write_value_##1##_4);\n");
            printf("apply (remove_value_header_##1);\n");
         }
      }


      if (is_read[i]) {
         if (is_valid[i]){
            // apply (reply_read_hit_after);
            printf("apply (reply_read_hit_after);\n");
         }
      }


      // ipv4_route();
      if (dstIP[i] == 1) {
         printf("pkt[%d] go to port 1\n", i);
      } else {
         printf("pkt[%d] go to port 2\n", i);
      }

      // egress
      if (is_read[i]) {
         if (is_exist[i] != 1){
            // if (is_exist_read) {
            // heavy_hitter();
            if (instance_type[i] == 0){
               klee_cmin_add();
               if (klee_cmin_larger_than(CMIN_THRES)) {
                  ret = klee_bf_access();
                  if (ret != BF_ACCESS_HIT) {
                     printf("sending HH report to CPU\n");
                  }
               }
            } else {
               printf("report_hot_step_2();\n");
            }
         }
      }

      // apply (ethernet_set_mac);
      if (egress_port[i] == 1) {
         printf("apply (ethernet_set_mac); port=%d\n", i);
      } else {
         printf("apply (ethernet_set_mac); port=%d\n", i);
      }
   }

   return 0;
}
