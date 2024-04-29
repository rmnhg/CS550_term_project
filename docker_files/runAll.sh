#!/usr/bin/bash

# Create logs folder
rm -rf /scripts/logs
mkdir /scripts/logs

# Perform all the measurements
/scripts/measure_disk.sh
/scripts/measure_mem.sh
/scripts/measure_network.sh