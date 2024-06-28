#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXBUFFER			250
#define MAXWORD				50
#define MAXCONNECTIONS		4
#define TOTALCONNECTIONS	4

typedef struct connection {
	char name[MAXWORD];
	char words[MAXCONNECTIONS][MAXWORD];
} CONNECTION;

void printConnection(CONNECTION c);

CONNECTION createConnection(char* name, char* word1, char* word2, char* word3, char* word4);