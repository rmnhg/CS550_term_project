#!/usr/bin/python3
import urllib3
import time
import sys

chunk_size = 32 * 1024
number_of_attempts = 10
http = urllib3.PoolManager()
averages = {}
filesize = int(sys.argv[1])
averages[filesize] = 0
for attempts in range(number_of_attempts):
    r = http.request('GET', f"https://srv.ramonhg.es/files/{filesize}MB", preload_content=False)

    start_time = time.time()
    size = 0
    while True:
        data = r.read(chunk_size)
        size += len(data)
        if not data:
            stop_time = time.time()
            break

    r.release_conn()
    total_time = stop_time - start_time
    total_speed_MiBsec = size/total_time
    averages[filesize] += total_time/number_of_attempts
total_speed_MiBsec = size/total_time
print(f"Downloaded file of {size} bytes ({int(size/(1024 * 1024))} MiBs) in {averages[filesize]} seconds ({'{:.2f}'.format(size/averages[filesize])} Bps or {'{:.2f}'.format((size * 1024 * 1024)/averages[filesize])} MiBps) in the {sys.argv[2]} environment.")