#!/bin/bash

make clean
make
OUTPUT=$(./calc)

EXPECTED=">> System Ready for Lab 1"

if [ "$OUTPUT" == "$EXPECTED" ]; then
    echo -e "\033[0;32mPASS\033[0m"
else
    echo -e "\033[0;31mFAIL\033[0m"
    exit 1
fi