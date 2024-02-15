#!/bin/bash

# Run script by typing
#    ./test.sh XXX
# where XXX stands for the number of random, disordered integers in the 'a' stack

if [ -n "$1" ]; then N=$1; else N=0; fi

ARG=$(od -An -N$((4*$N)) -i /dev/random | tr -d '\n')

echo $ARG
./push_swap $ARG > output.txt
cat output.txt | wc -l
