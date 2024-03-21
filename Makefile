CC=gcc
VCC=vcc

all:
	make normal virtines

normal:
	$(CC) -o norm disk_speed.c

virtines:
	$(VCC) -o virt disk_speed.c

clean:
	rm -rf norm virt testFile logs