#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createTestFile(int size, char *name) {
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen(name, "wb");

    if (fptr == NULL) {
        printf("There was an error opening the %s to write it.\n", name);
        return;
    }

    // Write some text to the file
    for (int i = 0; i < size; i++)
        fprintf(fptr, "a"); // Write an ASCII character (1 byte)

    // Close the file
    fclose(fptr);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error! You have not specified the required parameters.\n");
        printf("The first parameter must be the file size in Mibytes to be tested, and the second one the name of the file to be created:\n");
        printf("Ex: %s 200 example.txt\n", argv[0]);
        return -1;
    }
    int size_MiB = atoi(argv[1]);
    int size = size_MiB * 1024 * 1024; // Convert to MiB

    printf("Creating file of %d Mibytes with name %s...\n", size_MiB, argv[2]);
    createTestFile(size, argv[2]);
    printf("The file %s of %d Mibytes has been created successfully!\n", argv[2], size_MiB);
}