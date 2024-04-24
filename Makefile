CC=gcc
VCC=vcc

all:
	make normalDisk virtinesDisk normalNet virtinesNet normalMem virtinesMem createFile

normalDisk:
	$(CC) -o normDisk disk_speed.c

virtinesDisk:
	$(VCC) -o virtDisk disk_speed.c

normalNet:
	$(CC) -o normNet network_speed.c

virtinesNet:
	$(VCC) -o virtNet network_speed.c

normalMem:
	$(CC) -o normMem memory_speed.c

virtinesMem:
	$(VCC) -o virtMem memory_speed.c

createFile:
	$(CC) -o createFile createFile.c

clean:
	rm -rf normdisk virtDisk normNet virtNet normMem virtMem testFile createFile assets logs docker_files/assets docker_files/logs *.png