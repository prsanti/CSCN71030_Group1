#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFFER			250
#define MAXWORD				50
#define MAXCONNECTIONS		4
#define TOTALCONNECTIONS	4

// connection struct has a category name and an array of 4 words
typedef struct connection {
	char name[MAXWORD];
	char words[MAXCONNECTIONS][MAXWORD];
} CONNECTION;

// print connection for testing
void printConnection(CONNECTION c);

// create a connection with a category name and array of 4 words
CONNECTION createConnection(char name[MAXWORD], char wordList[MAXCONNECTIONS][MAXWORD]);

// copy a connection from a source
CONNECTION copyConnection(CONNECTION src);