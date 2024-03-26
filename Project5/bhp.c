/**
* file: bhp.c
* author: Wesley Anastasi
* course: CSI 3336
* assignment: project 5
* due date: 3/11/2024
*
* date modified: 3/11/2024
* - file created
*
* This file will read contents of .bash_history and produce a summary
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char cmdName[13];
    int cmdCount;
} CmdRec;

int main(int argc, char *argv[]) {

    CmdRec *commands = NULL;

    int numUniqCommands = 0;

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        if (buffer[0] == '\n') {
            continue;
        }
        char *token = strtok(buffer, " \t\n");
        size_t len = strlen(token);

        if (token == NULL || len >= 13) {
            continue;
        }

        
        token[len] = '\0';

        int isFound = 0;
        int i = 0;
        while (i < numUniqCommands) {
            if (strcmp(commands[i].cmdName, token) == 0) {
                commands[i].cmdCount++;
                isFound = 1;
                break;
            }
            i++;
        }

        if (isFound == 0) {
            commands = realloc(commands, (numUniqCommands+1) * sizeof(CmdRec));
            strcpy(commands[numUniqCommands].cmdName, token);
            commands[numUniqCommands].cmdCount = 1;
            numUniqCommands++;
        }

    }

    int i = 0;
    while (i < numUniqCommands) {
        printf("%-12s %4d\n", commands[i].cmdName, commands[i].cmdCount);
        i++;
    }

    free(commands);

    return 0;
}