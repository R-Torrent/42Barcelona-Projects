#!/bin/bash

# Run script by typing
#    ./test.sh XXX
# where XXX stands for the number of random, disordered integers in the 'a' stack

if [ -n "$1" ]; then N=$1; else N=0; fi

ARG=$(od -An -N$((4*$N)) -i /dev/random | tr -d '\n')
echo $ARG >input.dat

./push_swap $ARG >output.dat
RES=$?
if [ $RES -ne 0 ]; then
	echo "*Error* detected: Exit code $RES"
else
	echo "Number of instructions: $(cat output.dat | wc -l)"
	echo "MAC checker: $(./checker_Mac $ARG <output.dat)"
	if [ -f "checker" ]; then
		echo "BONUS checker: $(./checker $ARG <output.dat)"
	fi
fi
