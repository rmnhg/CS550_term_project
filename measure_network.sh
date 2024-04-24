#!/usr/bin/bash

# Compile the different binaries
echo "Compiling the different binaries"
make

# Create logs folder
rm -rf logs
mkdir logs

# Create an array of the different file sizes:
declare -a sizes=("16" "32" "64" "128" "256")

# Remove old files if existent
rm -rf assets

# Create the folder hosting the files
mkdir assets

# Create files for the file server
for size in "${sizes[@]}"; do
    $(pwd)/createFile ${size} assets/${size}
done

# Start the Python file server
echo "Starting the file server"
cd assets
python3 -m http.server 8080 &
sleep 1
cd ..

echo ""

for size in "${sizes[@]}"; do
    echo "Working with a file size of ${size} MiB..."
    echo ""
    echo "Measuring time of a normal execution for ${size} MiB."
    $(pwd)/normNet localhost 8080 ${size} normal > logs/network_normal_${size}.txt
    echo ""

    echo "Measuring time of a virtines execution for ${size} MiB."
    $(pwd)/virtNet localhost 8080 ${size} virtines > logs/network_virtines_${size}.txt
    echo ""
    echo ""
done

echo "Killing file server..."
sudo pkill python3

echo "Generating figures..."
python3 $(pwd)/cleanDataNetwork.py

echo "All the experiments have been completed!"