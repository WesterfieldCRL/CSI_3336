/**
* file: newTail.c
* author: Wesley Anastasi
* course: CSI 3336
* assignment: homework 8
* due date: 3/22/2024
*
* date modified: 3/22/2024
* - file created
*
* This file will print the last n characters of a file or the last 120 characters if n is not specified
*/

#include <stdio.h>
#include <stdlib.h>

void printTail(FILE *file, int numChars) {
    fseek(file, -numChars, SEEK_END);
    printf("Printing last %d characters:\n", numChars);
    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    int numChars;

    if (argc == 2) {
        numChars = 120;
        file = fopen(argv[1], "r");
    } else if (argc == 3) {
        numChars = atoi(argv[1]);
        file = fopen(argv[2], "r");
    } else {
        printf("Usage: %s [num_chars] filename\n", argv[0]);
        return 1;
    }

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printTail(file, numChars);

    fclose(file);
    return 0;
}
