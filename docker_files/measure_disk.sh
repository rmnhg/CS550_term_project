#!/usr/bin/bash

# Create an array of the different file sizes:
declare -a sizes=("16" "32" "64" "128" "256")

# Remove old file if existent
rm /scripts/testFile

for size in "${sizes[@]}"; do
    echo "Working with a file size of ${size} MiB for disk speed..."
    echo ""
    echo "Measuring time of a docker execution for ${size} MiB."
    /scripts/normDisk ${size} docker > /scripts/logs/disk_docker_${size}.txt
    rm /scripts/testFile
    echo ""
done

echo "All the disk experiments have been completed!"