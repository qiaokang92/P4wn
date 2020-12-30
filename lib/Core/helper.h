#ifndef HELPER_H
#define HELPER_H

#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define LOG_MASK_HT       (1 << 0)
#define LOG_MASK_MKSYM    (1 << 1)
#define LOG_MASK_EXE      (1 << 2)
#define LOG_MASK_PROB     (1 << 3)
#define LOG_MASK_SSE      (1 << 4)
#define LOG_MASK_BF       (1 << 5)
#define LOG_MASK_CMIN     (1 << 6)
#define LOG_MASK_MA       (1 << 7)
#define LOG_MASK_QUERY    (1 << 8)
#define LOG_MASK_TS       (1 << 9)
#define LOG_MASK_ALL      (-1)

//#define LOG_MASK_CUR  (LOG_MASK_CMIN | LOG_MASK_MA)

#define LOG_MASK_CUR  (-1)
//#define LOG_MASK_CUR  (LOG_MASK_BF)
//#define LOG_MASK_CUR  (LOG_MASK_SSE)
// #define LOG_MASK_CUR  (LOG_MASK_SSE)
//#define LOG_MASK_CUR  (LOG_MASK_EXE | LOG_MASK_QUERY)
//#define LOG_MASK_CUR  (LOG_MASK_TS)
//#define LOG_MASK_CUR  (LOG_MASK_CMIN | LOG_MASK_BF | LOG_MASK_MA | LOG_MASK_QUERY | LOG_MASK_HT)

//#define LOG_MASK_CUR   LOG_MASK_ALL

#define LOG(mask, fmt, ...)                          \
   if (mask & LOG_MASK_CUR) {                        \
      printf("[LOG] %s:%d: " fmt "\n", __FUNCTION__,    \
             __LINE__, ##__VA_ARGS__);                  \
   }

#define ERR(fmt, ...)                          \
      printf("[ERR] %s:%d: " fmt "\n", __FUNCTION__,    \
             __LINE__, ##__VA_ARGS__);

#define WARN(fmt, ...)                          \
      printf("[WARN] %s:%d: " fmt "\n", __FUNCTION__,    \
             __LINE__, ##__VA_ARGS__);


#endif
