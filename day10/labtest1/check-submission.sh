#!/usr/bin/env bash

if [ $# != 1 ]; then
    echo -e "Usage: ./check-submission <your roll number, e.g., cs2707>"
    exit 1
fi

rollno="$@"

if [[ -d q1 && -d q2 && -d q3 && -d q4 ]]; then
    echo ""
else
    echo "One or more of required subdirectories missing."
    exit 1
fi

for i in {1..3}; do
    cd q$i
    progfile=$rollno-q$i.c
    echo "Checking Question $i"
    if [[ -f $progfile ]]; then
        gcc -g -Wall $progfile && \
        for f in input*.txt; do
            ./a.out < $f | diff -bBwsq - output${f#input}
            # echo DEBUGINFOD_URLS = $DEBUGINFOD_URLS
            valgrind --tool=memcheck --leak-check=full --log-file=valgrind-log-q$i.txt ./a.out < $f > /dev/null
        done
    else
        echo "Could not find $progfile in $(pwd)"
    fi
    echo ""
    cd ..
done

# cd q4
# echo "Checking Question 4"
# for i in {a..c}; do
#     if [[ -f q4$i.c ]]; then
#         gcc -g -Wall $rollno-q4$i.c && \
#         for f in input-$i-*.txt; do
#             ./a.out < $f | diff -bBwsq - output${f#input}
#             echo DEBUGINFOD_URLS = $DEBUGINFOD_URLS
#             valgrind --tool=memcheck --leak-check=full --log-file=valgrind-log-q4$i.txt ./a.out < $f > /dev/null
#         done
#     else
#         echo "Could not find q4$i.c in $(pwd)"
#     fi
#     echo ""
# done
