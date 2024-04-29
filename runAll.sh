#!/usr/bin/bash

sudo make clean
make

docker compose up

./measure_disk.sh
./measure_mem.sh
./measure_network.sh