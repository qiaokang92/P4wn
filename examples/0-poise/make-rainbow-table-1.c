#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define NAT_IP "192.168.0.1"
//#define TABLE_SIZE (1 << 16)
// TODO: to make developmenet faster, we use 64-entry hash tables all the time
#define TABLE_SIZE (1 << 6)

typedef struct __attribute__((packed)) {
  uint32_t src_ip;
  uint8_t proto;
  uint16_t src_port;
} hash_key_t;

#define hash_function_rot(x, k) (((x) << (k)) | ((x) >> (32 - (k))))

#define hash_function_mix(a, b, c)                                             \
  {                                                                            \
    a -= c;                                                                    \
    a ^= hash_function_rot(c, 4);                                              \
    c += b;                                                                    \
    b -= a;                                                                    \
    b ^= hash_function_rot(a, 6);                                              \
    a += c;                                                                    \
    c -= b;                                                                    \
    c ^= hash_function_rot(b, 8);                                              \
    b += a;                                                                    \
    a -= c;                                                                    \
    a ^= hash_function_rot(c, 16);                                             \
    c += b;                                                                    \
    b -= a;                                                                    \
    b ^= hash_function_rot(a, 19);                                             \
    a += c;                                                                    \
    c -= b;                                                                    \
    c ^= hash_function_rot(b, 4);                                              \
    b += a;                                                                    \
  }

#define hash_function_final(a, b, c)                                           \
  {                                                                            \
    c ^= b;                                                                    \
    c -= hash_function_rot(b, 14);                                             \
    a ^= c;                                                                    \
    a -= hash_function_rot(c, 11);                                             \
    b ^= a;                                                                    \
    b -= hash_function_rot(a, 25);                                             \
    c ^= b;                                                                    \
    c -= hash_function_rot(b, 16);                                             \
    a ^= c;                                                                    \
    a -= hash_function_rot(c, 4);                                              \
    b ^= a;                                                                    \
    b -= hash_function_rot(a, 14);                                             \
    c ^= b;                                                                    \
    c -= hash_function_rot(b, 24);                                             \
  }

uint32_t hash_function(hash_key_t *key) {
  // Based on Bob Jenkins' lookup3 algorithm.
  uint32_t a, b, c;

  //a = b = c = 0xdeadbeef + ((uint32_t)sizeof(hash_key_t));
  a = b = c = 0xdeadbaaf + ((uint32_t)sizeof(hash_key_t));

  a += key->src_ip;
  b += key->proto;
  c += key->src_port;

  hash_function_final(a, b, c);
  return c;
}

void generate_entry(hash_key_t *key) {
  //int hash = hash_function(key) % TABLE_SIZE;
  uint16_t hash = hash_function(key) % TABLE_SIZE;

  printf("%08X", hash);
  for (int i = 0; i < sizeof(*key); i++) {
    printf(" %02hhX", ((char *)key)[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  long long num_entries;
  if (argc == 1) {
    num_entries = LLONG_MAX;
  } else if (argc == 2) {
    num_entries = atoll(argv[1]);
  } else {
    fprintf(stderr, "Usage: %s [entries]\n", argv[0]);
    exit(1);
  }

  srand(time(NULL));

  hash_key_t key;

  for (long long count = 0; count < num_entries; count += 2) {
    for (int b = 0; b < sizeof(key); b++) {
      ((char *)&key)[b] = rand();
    }

    generate_entry(&key);
  }

  return 0;
}
