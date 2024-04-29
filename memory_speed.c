#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ATTEMPTS = 10;

void writeBigVariable(int size, char *variable) {
    // Write a character to each position of the array
    for (int i = 0; i < size; i++) {
        *(variable + i) = 'a';
    }
}

void readBigVariable(int size, char *variable) {
    // Read a character from each position of the array
    for (int i = 0; i < size; i++) {
        if (*(variable + i) == 'a')
            ;
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error! You have not specified the required parameters.\n");
        printf("The first parameter must be the memory size to be tested, and the second one the name of the execution environment:\n");
        printf("Ex: %s 200 virtines\n", argv[0]);
        return -1;
    }

    clock_t t;
    int size_MiB = atoi(argv[1]);
    int size = size_MiB * 1024 * 1024; // Convert to MiB
    char *memoryAllocation = malloc(size);

    // Create memory variable
    double time_taken = 0;
    printf("Creating a memory variable of %d MiB (%d bytes) from %s env...\n", size_MiB, size, argv[2]);
    for (int i = 0; i < ATTEMPTS; i++) {
        t = clock(); // Start time
        writeBigVariable(size, memoryAllocation);
        t = clock() - t; // Final time
        // Convert time to seconds and save as average
        time_taken += (((double) t)/CLOCKS_PER_SEC)/ATTEMPTS; // in seconds
    }
    printf("A memory variable of %d MiB has been succesfully written in %f seconds (%f MiB/sec) in %s env!\n", size_MiB, time_taken, size_MiB/time_taken, argv[2]);

    // Read memory variable
    time_taken = 0;
    printf("Reading the created memory variable of %d MiB (%d bytes) from %s env...\n", size_MiB, size, argv[2]);
    for (int i = 0; i < ATTEMPTS; i++) {
        t = clock(); // Start time
        readBigVariable(size, memoryAllocation);
        t = clock() - t; // Final time
        // Convert time to seconds and save as average
        time_taken += (((double) t)/CLOCKS_PER_SEC)/ATTEMPTS; // in seconds
    }
    printf("The memory variable of %d MiB has been succesfully read in %f seconds (%f MiB/sec) in %s env!\n", size_MiB, time_taken, size_MiB/time_taken, argv[2]);
}