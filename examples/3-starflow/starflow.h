// table tiRWShortVec_1 has two possible actions:
// aiRShortVec_1 and aiRWShortVec_1
// We don't know the per-action probability, so assuming it is 50%

#define SHORT_VEC(num)        \
void aiRShortVec_##num() {}       \
void aiRWShortVec_##num() {}     \
void tiRWShortVec_##num(symbol)           \
{                                     \
   if (symbol) {                                                 \
      aiRShortVec_##num();                                           \
   } else {                                                       \
      aiRWShortVec_##num();                                          \
   }                                                             \
}

SHORT_VEC(0)
SHORT_VEC(1)
SHORT_VEC(2)
SHORT_VEC(3)

void vector_actions()
{
   uint8_t symbol;                           \
   klee_make_symbolic(&symbol, sizeof symbol, "half");        \

   tiRWShortVec_0(symbol);
   tiRWShortVec_1(symbol);
   tiRWShortVec_2(symbol);
   tiRWShortVec_3(symbol);
}
