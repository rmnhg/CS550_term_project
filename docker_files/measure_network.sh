#!/usr/bin/bash

# Create an array of the different file sizes:
declare -a sizes=("16" "32" "64" "128" "256")

for size in "${sizes[@]}"; do
    echo "Working with a file size of ${size} MiB for network speed..."
    echo ""
    echo "Measuring time of a docker execution for ${size} MiB."
    /scripts/normNet ${size} docker /scripts > /scripts/logs/network_docker_${size}.txt
    echo ""
done

echo "All the network experiments have been completed!"