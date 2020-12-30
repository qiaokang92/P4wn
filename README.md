# P4wn: A Probabilistic Profiler for Stateful P4 programs

Publication: [ASPLOS'2021](https://asplos-conference.org/abstracts/asplos21-paper1594-extended_abstract.pdf)

## Setup

### Installing KLEE dependencies

P4wn is built upon KLEE, so we need to install KLEE dependencies first.
Follow the instructions [here](http://klee.github.io/releases/docs/v2.0/build-llvm60/).
Note that we only need to do the first 3 steps.

### Install LattE

LattE provides model counting support for P4wn.
Install LattE from [here](https://github.com/latte-int/latte-distro).

### Build P4wn

```
mkdir build
cd build
cmake -DENABLE_SOLVER_STP=ON -DLLVM_CONFIG_BINARY=/usr/bin/llvm-config-6.0 -DENABLE_UNIT_TESTS=OFF -DENABLE_SYSTEM_TESTS=OFF ..
make -j<N>
```

Add the following line in the `.bashrc` file:
```
alias p4wn="<p4wn_folder>/build/bin/klee"
```

## Using P4wn to profile network programs

First compile the program:
```
# compile
clang-6.0 -I <path_to_klee_include_folder> -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone <program.c>
# or
clang-6.0 -I /home/qiaokang/dpattacks/tools/klee-prob/include -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone <program.c>
```

It will generate a `.bc` file. Then use p4wn to run this file:
```
p4wn --real-trace <trace-on> --num-trace-pkt <pkt-num> --program-num <num> --num-loop <loop> --converge-delta <delta> <program.bc>
```

Then the per-branch probabilities will be printed in sorted order.

Explanation of parameters:
- `trace-on`: if true, then P4wn will query the trace for header distribution;
otherwise it invokes the model counter.
- `pkt-num`: if `trace-on` is set, then it specifies the number of pkts
when checking the trace.
- `num`: program number.
- `loop`: number of symbolic packets to explore
- `delta`: specifies whether the per-path probabilities have converged:
In N+1 round, if the diff of all probs is less than delta, then we say the
profile has converged.


## Telescoping

After running P4wn we will find that it fails to profile certain code blocks
because they need very long pkt sequences to trigger.
We use "telescoping" to trigger them.

### Blink (no greybox)

First, we use `telescope/blink-single-flow.c` to try telescoping.

```
p4wn --program-num 99 --real-trace 1 --enable-ts 1 blink-single-flow.bc
```

The telescope result is `1e-96`, which is exactly the ground truth.


### Blink (counter)

First, we run without TS. Since we cannot compute the ground truth for
32 packets, we use 5 packet version instead.

```
p4wn --program-num 2 --real-trace 1 --enable-ts 0 blink-counter.bc
```

The result is 2.93651e-22. Then we enable TS:
```
p4wn --program-num 2 --real-trace 1 --enable-ts 1 blink-counter.bc
```
The result is also 2.93651e-22. 100% accurate!


### Blink (with sw)

Telescope the full Blink of 32 packets.

```
p4wn --program-num 2 --real-trace 1 --enable-ts 1 blink.bc
```
Result is 2.28091e-160.

## License

P4wn retains KLEE's [University of Illinois/NCSA
Open Source License](https://github.com/klee/klee/blob/master/LICENSE.TXT).
