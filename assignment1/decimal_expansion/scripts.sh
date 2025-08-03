#!/bin/bash

filename=${1};

if [ -f "$filename.cpp" ]; then
    clang++ -std=c++20 -Wall "$filename.cpp" -o "$filename";
fi

current_directory=${PWD##*/};

if [[ $current_directory != "tests" ]]; then
    cd ./tests;
fi

number_of_inputs=$(ls -1 input*.txt 2>/dev/null | wc -l);

for i in $(seq 1 $number_of_inputs); do
    ../$filename < ./input$i.txt > ./output$i.txt;
done
