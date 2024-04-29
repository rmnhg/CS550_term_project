#!/usr/bin/bash

# Compile the different binaries
echo "Compiling the different binaries"
make

# Create logs folder
rm -rf logs
mkdir logs

# Create an array of the different file sizes:
declare -a sizes=("16" "32" "64" "128" "256")

# Remove old file if existent
rm testFile

for size in "${sizes[@]}"; do
    echo "Working with a file size of ${size} MiB for disk speed..."
    echo ""
    echo "Measuring time of a normal execution for ${size} MiB."
    $(pwd)/normDisk ${size} normal > logs/disk_normal_${size}.txt
    rm testFile

    echo ""

    echo "Measuring time of a virtines execution for ${size} MiB."
    $(pwd)/virtDisk ${size} virtines > logs/disk_virtines_${size}.txt
    rm testFile
    echo ""
    echo ""
done

echo "Generating figures..."
python3 $(pwd)/cleanDataDisk.py

echo "All the disk experiments have been completed!"