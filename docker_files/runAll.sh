#!/usr/bin/bash

# Create logs folder
rm -rf /scripts/logs
mkdir /scripts/logs

/scripts/measure_disk.sh
/scripts/measure_mem.sh
/scripts/measure_network.sh