#!/usr/bin/bash

# Compile the different binaries
echo "Compiling the different binaries"
make

# Create logs folder
rm -rf logs
mkdir logs

# Create an array of the different file sizes:
declare -a sizes=("16" "32" "64" "128" "256")

echo ""

for size in "${sizes[@]}"; do
    echo "Working with a file size of ${size} MiB for network speed..."
    echo ""
    echo "Measuring time of a normal execution for ${size} MiB."
    $(pwd)/normNet ${size} normal > logs/network_normal_${size}.txt
    echo ""

    echo "Measuring time of a virtines execution for ${size} MiB."
    $(pwd)/virtNet ${size} virtines > logs/network_virtines_${size}.txt
    echo ""
    echo ""
done

echo "Generating figures..."
python3 $(pwd)/cleanDataNetwork.py

echo "All the network experiments have been completed!"