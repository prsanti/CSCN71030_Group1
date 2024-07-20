#define _CRT_SECURE_NO_WARNINGS
// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli
#include <stdio.h>

#include <string.h>
#include "connection.h"

void printConnection(CONNECTION c) {
    fprintf(stdout, "Name: %s\n", c.name);
    for (int i = 0; i < MAXCONNECTIONS; i++) {
        fprintf(stdout, "Connection %d: %s\n", i, c.words[i]);
    }
}

CONNECTION createConnection(char name[MAXWORD], char wordList[MAXCONNECTIONS][MAXWORD]) {
    CONNECTION c;
    strncpy(c.name, name, MAXWORD);

    for (int i = 0; i < MAXCONNECTIONS; i++) {
        strncpy(c.words[i], wordList[i], MAXWORD);
    }

    return c;
}

CONNECTION copyConnection(CONNECTION src) {
    return createConnection(src.name, src.words);
}
