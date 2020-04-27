#!/bin/bash

echo "Building..."

make > build.txt

pop_sizes=(25 50 100)
test_sizes=(250 500 1000)

echo "Running tests..."

for i in 0 1 2; do
    ./virusim_0 ${pop_sizes[$i]} ${test_sizes[$i]} 101 > output.txt

    TIME=$(awk '/./{line=$0} END{print line}' output.txt)

    echo "./virusim_0 ${pop_sizes[$i]} ${test_sizes[$i]} = $TIME" 

    ./virusim_1 ${pop_sizes[$i]} ${test_sizes[$i]} 101 > output.txt

    TIME=$(awk '/./{line=$0} END{print line}' output.txt)

    echo "./virusim_1 ${pop_sizes[$i]} ${test_sizes[$i]} = $TIME" 

    ./virusim_2 ${pop_sizes[$i]} ${test_sizes[$i]} 101 > output.txt

    TIME=$(awk '/./{line=$0} END{print line}' output.txt)

    echo "./virusim_2 ${pop_sizes[$i]} ${test_sizes[$i]} = $TIME" 
done

echo "Cleaning up..."

make clean
rm output.txt
rm build.txt