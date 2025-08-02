#!/bin/bash

set -e;

if [ -n "$1" ]; then 
    inputs=$1;
else 
    inputs=0;
fi

cd "./tests";

function _max() {
    a=$1;
    b=$2;

    if [ "$a" -ge "$b" ]; then
        echo "$a";
    else 
        echo "$b";
    fi
}

number_of_inputs=$(ls -1 input*.txt 2>/dev/null | wc -l);
number_of_inputs=$(_max $number_of_inputs $inputs);

if [ -f "../generate_test.py" ]; then
    for i in $(seq 1 $number_of_inputs); do
        python3 ../generate_test.py > "input${i}.txt";
    done
fi
