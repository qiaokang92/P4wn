# NetWarden

`nw.c` is a complete version of NW re-written in C.

```
clang-6.0 -I /home/qiaokang/dpattack-qiao/tools/klee-prob/include -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone nw.c

probklee --num-trace-pkt 10000 --real-trace 1 --program-num 1 nw.bc
```
