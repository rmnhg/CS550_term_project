#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ATTEMPTS = 10;

void createTestFile(int size) {
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("testFile", "wb");

    if (fptr == NULL) {
        printf("There was an error opening the testFile to write it.\n");
        return;
    }

    // Write some text to the file
    for (int i = 0; i < size; i++)
        fprintf(fptr, "a"); // Write an ASCII character (1 byte)

    // Close the file
    fclose(fptr);
}

void readTestFile(int size) {
    FILE *fptr;
    char byte;

    // Open a file in writing mode
    fptr = fopen("testFile", "rb");

    if (fptr == NULL) {
        printf("There was an error opening the testFile to read it.\n");
        return;
    }

    // Write some text to the file
    for (int i = 0; i < size; i++)
        fread(&byte, sizeof(char), 1, fptr);

    // Close the file
    fclose(fptr);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error! You have not specified the required parameters.\n");
        printf("The first parameter must be the file size to be tested, and the second one the name of the execution environment:\n");
        printf("Ex: %s 200 virtines\n", argv[0]);
        return -1;
    }

    clock_t t;
    int size_MiB = atoi(argv[1]);
    int size = size_MiB * 1024 * 1024; // Convert to MiB

    // Create file
    double time_taken = 0;
    printf("Creating a file of %d MiB (%d bytes) from %s env...\n", size_MiB, size, argv[2]);
    for (int i = 0; i < ATTEMPTS; i++) {
        t = clock(); // Start time
        createTestFile(size);
        t = clock() - t; // Final time
        // Convert time to seconds and save as average
        time_taken += (((double) t)/CLOCKS_PER_SEC)/ATTEMPTS; // in seconds
    }
    printf("A file of %d MiB has been succesfully written in %f seconds (%f MiB/sec) in %s env!\n", size_MiB, time_taken, size_MiB/time_taken, argv[2]);

    // Read file
    time_taken = 0;
    printf("Reading the created file of %d MiB (%d bytes) from %s env...\n", size_MiB, size, argv[2]);
    for (int i = 0; i < ATTEMPTS; i++) {
        t = clock(); // Start time
        readTestFile(size);
        t = clock() - t; // Final time
        // Convert time to seconds and save as average
        time_taken += (((double) t)/CLOCKS_PER_SEC)/ATTEMPTS; // in seconds
    }
    printf("The file of %d MiB has been succesfully read in %f seconds (%f MiB/sec) in %s env!\n", size_MiB, time_taken, size_MiB/time_taken, argv[2]);
}