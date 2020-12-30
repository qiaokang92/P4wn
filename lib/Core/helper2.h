#ifndef HELPER_H
#define HELPER_H

#include <string.h>

#define LOG_MASK_HT       (1 << 0)
#define LOG_MASK_MKSYM    (1 << 1)
#define LOG_MASK_EXE      (1 << 2)
#define LOG_MASK_PROB     (1 << 3)
#define LOG_MASK_RT       (1 << 4)
#define LOG_MASK_ALL      (-1)

#define LOG_MASK_CUR   LOG_MASK_ALL

//#define LOG_MASK_CUR  (LOG_MASK_HT | LOG_MASK_PROB)

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
