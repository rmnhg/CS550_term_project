#!/usr/bin/bash

# Compile the different binaries
echo "Compiling the different binaries"
make

# Create logs folder
rm -rf logs
mkdir logs

# Create an array of the different memory variable sizes:
declare -a sizes=("16" "32" "64" "128" "256")

for size in "${sizes[@]}"; do
    echo "Working with a memory variable size of ${size} MiB..."
    echo ""
    echo "Measuring time of a normal execution for ${size} MiB."
    $(pwd)/normMem ${size} normal > logs/mem_normal_${size}.txt

    echo ""

    echo "Measuring time of a virtines execution for ${size} MiB."
    $(pwd)/virtMem ${size} virtines > logs/mem_virtines_${size}.txt
    echo ""
    echo ""
done

echo "Generating figures..."
python3 $(pwd)/cleanDataMem.py


echo "All the experiments have been completed!"