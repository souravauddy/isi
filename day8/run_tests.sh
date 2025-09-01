: 'filename=$1;
test_passed=0;

if [ ! -e $filename ]; then
    exit;
fi

for i in $(seq 1 4); do 
    ./$filename < ./test-cases/input5-$i.txt > output$i.txt;
    colordiff output$i.txt ./test-cases/output5-$i.txt;

    echo "Program output $i:";
    cat output$i.txt
    echo "Actual output: ";
    cat ./test-cases/output5-$i.txt;

    if [[ $? -eq 0 ]]; then
        echo "Test Passed."
        test_passed=$((test_passed + 1));
    fi

    echo "-----------------------------------------------------------------------------------------";
done

echo "test cases passed = $test_passed";
'

#!/bin/bash

# Define some colors
RED='\033[0;31m';
GREEN='\033[0;32m';
YELLOW='\033[1;33m';
BLUE='\033[0;34m';
GREY='\033[90m';
NC='\033[0m'; # No Color

filename=$1;
test_passed=0;
total=$2;

if [ ! -e "test-cases" ]; then
    cd ./$filename;
fi

# clang++ -std=c++23 -Wall -DLOCAL "$filename.cpp" -o "$filename";

if [ $# -lt 2 ]; then 
    total=$(ls -1 ./test-cases/input*.txt 2>/dev/null | wc -l | xargs);
fi

for i in $(seq 1 $total); do
    ./$filename < ./test-cases/input$i.txt > ./test-cases/program-output$i.txt;

    echo "${BLUE}Program output ($i):${NC}";
    cat ./test-cases/program-output$i.txt;

    echo "${YELLOW}Expected output:${NC}";
    cat ./test-cases/output$i.txt;

    if diff --color=always -u ./test-cases/program-output$i.txt ./test-cases/output$i.txt > diff$i.txt; then
        echo "${GREEN}✅ Test $i passed${NC}";
        test_passed=$((test_passed + 1));
    else
        echo "${RED}❌ Test $i failed${NC}";

        echo "${RED}Diff:${NC}";
        cat diff$i.txt;
    fi

    echo "${GREY}-----------------------------------------------------------------------------------------${NC}";

    rm diff$i.txt;
done

echo "${GREEN}Total test cases passed = ($test_passed / ${total})${NC}";
