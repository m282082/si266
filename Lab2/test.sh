#!/bin/bash

make clean > /dev/null
make > /dev/null
OUTPUT=$(./part2)

EXPECTED="[42] Hopper, Grace (GPA: 5.00)"

if [ "$OUTPUT" == "$EXPECTED" ]; then
    echo "Info Check PASSED"
else
    echo "Info Check FAILED"
fi

valgrind --leak-check=full --error-exitcode=1 ./part2 > /dev/null 2> /dev/null
VAL=$?

if [ "$VAL" -eq 0 ]; then
    echo "Memory Check PASSED"
else
    echo "Memory Check FAILED"
fi
