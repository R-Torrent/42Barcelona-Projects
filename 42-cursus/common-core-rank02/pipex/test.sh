#!/bin/bash

make all

< test1.txt cat | sed -E "/^\s*$/d" | head -5 | cut -d " " -f 1 > result1a.txt
./pipex test1.txt cat 'sed -E "/^\s*$/d"' 'head -5' 'cut -d " " -f 1' result1b.txt

< test2.txt cat | grep "^He has refused" | wc > result2a.txt
./pipex test2.txt cat 'grep "^He has refused"' wc result2b.txt

< test3.txt ls -l .. | wc -l > result3a.txt
./pipex test3.txt 'ls -l ..' 'wc -l' result3b.txt

for i in $(seq 1 3);
do
	if diff -s result${i}a.txt result${i}b.txt &> /dev/null; then
		echo "Test $i passed! :D"
	else
		echo "Test $i failed... :("
	fi
done

rm result*.txt
