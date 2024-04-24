#!/usr/bin/bash

sudo make clean
make

docker compose up -d
sleep 3

./measure_disk.sh
./measure_mem.sh
./measure_network.sh