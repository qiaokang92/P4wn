#!/bin/bash

if [ "$#" -lt "1" ]; then
    echo "ERROR: no P4 program specified!"
    echo "    usage: $0 /path/to/program.p4 [forwarding_rules.txt]"
    exit 1
fi

if [ -z "$2" ]; then
    echo "No forwarding rules supplied."
fi

dir=$(dirname $1)
filename=$(basename $1)
program=$(echo $filename | cut -f 1 -d '.')

echo "Generating $program.json..."
p4c-bm2-ss $1 --toJSON $program.json > /dev/null

echo "Translating to C code..."
if [ -z "$2" ]; then
    python ./src/P4_to_C.py $program.json
else
    python ./src/P4_to_C.py $program.json $2
fi

echo "Creating LLVM representation for KLEE..."
# clang -I $dir/../../include -emit-llvm -g -c $program.c
clang -emit-llvm -g -c $program.c > /dev/null

echo "Running KLEE..."
klee --search=dfs --no-output --optimize $program.bc