#!/usr/bin/env python2

# TODO: add processing of --keep-files
#   keep-files => if not set, remove klee-* and *.json files

import argparse
import time
from os import path, devnull
from subprocess import call

parser = argparse.ArgumentParser()
parser.add_argument('p4file', type=str, help='path to p4 program (.p4)')
parser.add_argument('commands', type=str, help='path to dataplane commands', nargs='?', 
    default='')
# parser.add_argument('-v', '--validate', action='store_const', const=True)
# parser.add_argument('-k', '--keep-files', action='store_const', const=True)
args = parser.parse_args()

p4file = args.p4file
commands = args.commands
# validate = args.validate
# cleanup = not args.keep_files

basename = path.basename(p4file)
p4filename = path.splitext(basename)[0]

start = time.time()

# TODO: treat errors inside inner calls
with open(devnull, 'w') as devnull:
    # calling p4c-bm2-ss
    print('Generating {}.json...'.format(p4filename))
    call('p4c-bm2-ss {} --toJSON {}.json'.format(p4file, p4filename).split())

    # calling p4->C translation script
    print('Translating to C code...')
    if len(commands) == 0:
        call('python ./src/P4_to_C.py {}.json'.format(p4filename).split())
    else:
        call('python ./src/P4_to_C.py {}.json {}'.format(p4filename, commands).split())

    # calling clang
    print('Creating LLVM representation for KLEE...')
    call('clang -emit-llvm -g -c {}.c'.format(p4filename).split(), 
        stdout=devnull, stderr=devnull)

    # running symbolic execution
    print('Running KLEE...\n')
    call('klee --search=dfs --no-output --optimize {}.bc'.format(p4filename).split(),
        stderr=devnull)

print('\nElapsed time: {:.3}s'.format(time.time() - start))