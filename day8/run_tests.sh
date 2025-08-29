#! /bin/bash

test_passed=0;

for i in $(seq 1 4); do 
    ./find_trees < ./test-cases/input5-$i.txt > output$i.txt;
    diff --color=always output$i.txt ./test-cases/output5-$i.txt;

    echo "Program output $i:";
    pygmentize -g output$i.txt;
    echo "Actual output: ";
    pygmentize -g ./test-cases/output5-$i.txt;

    if [[ $? -eq 0 ]]; then
        test_passed=$((test_passed + 1));
    fi

    echo "-----------------------------------------------------------------------------------------";
done

echo "test cases passed = $test_passed";
