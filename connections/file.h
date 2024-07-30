#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// file signatures

#define _CRT_SECURE_NO_WARNINGS
#include "connection.h"
#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 4

// function to count the number of lines in a file
// allows us to add more connections without having a static count
int countLines(FILE* fp);

// read random line from text file data
void readRandomLine(FILE* fp, int line, char** buffer);

// get random line from text file
int getRandomLine(FILE* fp);

// asign random line and ensure no duplicates
bool assignLines(FILE* fp, int readLines[]);

// load data from connectionData.txt
// set data to connectionArr to be used for creating linked list
bool loadData(char* filename, CONNECTION* connectionArr[TOTALCONNECTIONS]);
