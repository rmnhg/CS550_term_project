CC=gcc
VCC=vcc

all:
	make normal virtines normalNet virtinesNet

normal:
	$(CC) -o norm disk_speed.c

virtines:
	$(VCC) -o virt disk_speed.c

normalNet:
	$(CC) -o normDL dl.c

virtinesNet:
	$(VCC) -o virtDL dl.c

clean:
	rm -rf norm virt normDL virtDL testFile logs