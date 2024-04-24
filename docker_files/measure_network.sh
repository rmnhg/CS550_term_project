#!/usr/bin/bash

# Create an array of the different file sizes:
declare -a sizes=("16" "32" "64" "128" "256")

# Remove old files if existent
rm -rf /scripts/assets

# Create the folder hosting the files
mkdir /scripts/assets

# Create files for the file server
for size in "${sizes[@]}"; do
    /scripts/createFile ${size} /scripts/assets/${size}
done

# Start the Python file server
echo "Starting the file server"
cd /scripts/assets
python3 -m http.server 8080 &
sleep 2
cd ..

echo ""

for size in "${sizes[@]}"; do
    echo "Working with a file size of ${size} MiB..."
    echo ""
    echo "Measuring time of a docker execution for ${size} MiB."
    /scripts/normNet localhost 8080 ${size} docker > logs/network_docker_${size}.txt
    echo ""
done

echo "Killing file server..."
pkill python3

echo "All the experiments have been completed!"