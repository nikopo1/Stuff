#!/bin/bash

rm *.tmp

for size in `seq 1000 10000 100000`
do
	for i in `seq 1 1 100`
	do
		./cache linear $size | grep "delta" >> linear.tmp
		./cache binary $size | grep "delta" >> binary.tmp
	done

	LINEAR_AVG=`cat linear.tmp | awk '{ total += $3; count++ } END { print total/count}'`
	BINARY_AVG=`cat binary.tmp | awk '{ total += $3; count++ } END { print total/count}'`

	echo $size $LINEAR_AVG $BINARY_AVG
	echo $size $LINEAR_AVG $BINARY_AVG >> results.out

	rm *tmp
done

cat results.out
