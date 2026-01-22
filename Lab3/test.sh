#!/bin/bash

make clean  > /dev/null
make > /dev/null

if [ -f "$parser" ]; then 
	exit 1
fi

./parser > temp.txt
cat temp.txt | grep "Sensor 0" > /dev/null

VAL1=$?
if [ "$VAL1" -ne 0 ]; then
	echo "Logic Check FAILED" 
	exit 1
fi 

cat temp.txt | grep "66.23" > /dev/null

VAL2=$?
if [ "$VAL2" -ne 0 ]; then
        echo "Logic Check FAILED"  
        exit 1 
fi 

valgrind --leak-check=full --error-exitcode=1 ./parser > /dev/null 2> /dev/null
VAL3=$?

if [ "$VAL3" -eq 0 ]; then
	echo "All Tests PASSED"
	exit 0
else
	echo "Memory Check FAILED"
	exit 1
fi

exit 2
