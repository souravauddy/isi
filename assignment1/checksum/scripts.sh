filename=${1};

if [ -f "$filename.cpp" ]; then
    echo "sourav";
    clang++ -std=c++20 -Wall "$filename.cpp" -o "$filename";
fi

cd ./tests;

number_of_inputs=`ls -l . | egrep -c '^-'`;
number_of_inputs=$((number_of_inputs / 2));

for i in $(seq 1 $number_of_inputs); do
    ../$filename < ./input$i.txt > ./output$i.txt;
done