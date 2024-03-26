/**
* file: newHead.c
* author: Wesley Anastasi
* course: CSI 3336
* assignment: homework 8
* due date: 3/22/2024
*
* date modified: 3/22/2024
* - file created
*
* This file will print n lines of a file based on the options provided
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    int total_lines = 0;
    int t_count = 0;
    int f_count = 0;
    int o_count = 0;
    char *filename = NULL;

    while ((opt = getopt(argc, argv, "tfoi:")) != -1) {
        switch (opt) {
            case 't':
                t_count++;
                break;
            case 'f':
                f_count++;
                break;
            case 'o':
                o_count++;
                break;
            case 'i':
                filename = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-t] [-f] [-o] [-i filename]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (filename == NULL) {
        fprintf(stderr, "Usage: %s [-t] [-f] [-o] [-i filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    total_lines += t_count * 10;
    total_lines += f_count * 5;
    total_lines += o_count;

    printf("Total lines: %d\n", total_lines);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int lines_printed = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL && lines_printed < total_lines) {
        printf("%s", buffer);
        lines_printed++;
    }

    fclose(file);

    return 0;
}

