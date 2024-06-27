// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "connection.h"

#define FILE "connectionsData.txt"

int main(void) {
	// list of connections for game
	CONNECTION test;

	// read file data
	if (loadData(FILE) == false) {
		fprintf(stdout, "Error reading file data\n");
		exit(EXIT_FAILURE);
	}


	return 0;
}