#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

//#define DEBUG 1
#define LOG_LVL 10

#if DEBUG
#define assert(x)     \
    if(!(x)) {        \
        printf("assertion failed: %s at %s:%s:%d.\n",         \
               #x, __FILE__, __FUNCTION__, __LINE__);            \
        exit(-1);                                                 \
    }
#else
#define assert(x)   if(!(x)) {}
#endif

#define LOG(lev, fmt, ...) {                                          \
    if (lev <= LOG_LVL) {                                        \
       printf("[LOG] %s:%s:%d: "fmt"\n",                        \
              __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);     \
    }  \
}

#define WARN(fmt, ...) {                                                \
    printf(0, "[WARN] %s:%s:%d: "fmt"\n",                   \
                __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
}

#define ERR(fmt, ...)                                                  \
    fprintf(stderr, "[ERROR] "fmt"\n", ##__VA_ARGS__);                  \

#endif

