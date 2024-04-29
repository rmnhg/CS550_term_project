#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char cmd[256];
    if (argc == 4) {
        sprintf(cmd, "python3 %s/measure_network.py %s %s", argv[3], argv[1], argv[2]);
    } else {
        sprintf(cmd, "python3 ./measure_network.py %s %s", argv[1], argv[2]);
    }
    int status = system(cmd);
    if (status == -1) {
        printf("Command execution of the network tests through Python3 failed.\n");
        return 1;
    }
    return 0;
}