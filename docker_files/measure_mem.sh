#!/usr/bin/bash

# Create an array of the different memory variable sizes:
declare -a sizes=("16" "32" "64" "128" "256")

for size in "${sizes[@]}"; do
    echo "Working with a memory variable size of ${size} MiB..."
    echo ""
    echo "Measuring time of a docker execution for ${size} MiB."
    /scripts/normMem ${size} docker > /scripts/logs/mem_docker_${size}.txt
    echo ""
done

echo "All the experiments have been completed!"