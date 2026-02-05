#!/bin/bash

#*********TAKEN FROM GIVEN TEST SCRIPT**********
# Regex for number (integer or float)
val="[0-9]+(\.[0-9]+)?"

# Full regex (use string literals to ensure the fields are present)
REGEX="^CPU_USAGE:$val,MEM_USED:$val,MEM_AVAIL:$val,MEM_FREE:$val,MEM_CACHED:$val,SWAP_USED:$val,SWAP_FREE:$val,LOAD_1:$val,LOAD_5:$val,LOAD_15:$val,PROC_RUN:$val,PROC_TOTAL:$val$"

STRING=$(./gatherer)

# Perform the check (you need to replace $STRING with your actual output variable!)
if [[ "$STRING" =~ $REGEX ]]; then
  echo "Valid! All keys present in the correct order."
else
  echo "Invalid! Missing keys or incorrect order."
fi