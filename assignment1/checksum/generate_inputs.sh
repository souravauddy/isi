#!/bin/bash

set -e;

cd "./tests";

number_of_inputs=`ls -l . | egrep -c '^-'`;
number_of_inputs=$((number_of_inputs / 2));

if [ -f "../generate_test.py" ]; then
    for i in $(seq 1 $number_of_inputs); do
        python3 ../generate_test.py > "input${i}.txt";
    done
fi
