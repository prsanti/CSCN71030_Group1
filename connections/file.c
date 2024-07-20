// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "file.h"
#include "connection.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countLines(FILE* fp) {
    int lines = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    // Reset file pointer to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    return lines;
}

void getRandomLine(FILE* fp, char* buffer) {
    int lines = countLines(fp);
    int randomLine = rand() % lines;
    int currentLine = 0;
    char ch;

    fseek(fp, 0, SEEK_SET);

    while (currentLine < randomLine && (ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            currentLine++;
        }
    }

    if (fgets(buffer, MAXBUFFER, fp) == NULL) {
        buffer[0] = '\0';
    }
}

bool loadData(char* filename, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        return false;
    }

    char buffer[MAXBUFFER];
    char name[MAXWORD];
    char words[MAXCONNECTIONS][MAXWORD];

    for (int i = 0; i < TOTALCONNECTIONS; i++) {
        getRandomLine(fp, buffer);
        buffer[strlen(buffer) - 1] = '\0'; // Remove newline character

        char* token = strtok(buffer, ":");
        strncpy(name, token, MAXWORD);

        int j = 0;
        while ((token = strtok(NULL, ", ")) != NULL) {
            strncpy(words[j], token, MAXWORD);
            j++;
        }

        connectionArr[i] = (CONNECTION*)malloc(sizeof(CONNECTION));
        if (connectionArr[i] == NULL) {
            fprintf(stderr, "Cannot allocate memory to connection array\n");
            return false;
        }

        *connectionArr[i] = createConnection(name, words);
    }

    fclose(fp);
    return true;
}
