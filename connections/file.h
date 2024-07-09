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

int countLines(FILE* fp);

void getRandomLine(FILE* fp, char** buffer);

bool loadData(char* filename, CONNECTION* connectionArr[TOTALCONNECTIONS]);