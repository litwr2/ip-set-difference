#!/bin/bash
for ((i = 0; i < 5; i++))
do
	echo PASS $i
	mkdir test$i
	cd test$i
	../gen-test-case
	sort 3 >r-true
	../dhcp-diff-set 1 2| sort >r-set
	../dhcp-diff-list 1 2| sort >r-list
#	../dhcp-diff-vector 1 2| sort >r-vector
	diff r-true r-set >diff-set || echo ERROR with diff-set
	diff r-true r-list >diff-list || echo ERROR with deff-list
#	diff r-true r-vector >diff-vector
	if ! [ -s diff-set -o -s diff-list ]; then echo NO ERRORS DETECTED; fi
	cd ..
	echo
done
