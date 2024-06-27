// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "file.h"

bool loadData(char* filename) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file\n");
		return false;
		//exit(EXIT_FAILURE);
	}

	CONNECTION c1, c2, c3, c4;

	char buffer[MAXBUFFER];

	char name[MAXWORD];
	char w1[MAXWORD], w2[MAXWORD], w3[MAXWORD], w4[MAXWORD];

	for (int i = 0; i < TOTALCONNECTIONS; i++) {
		// read line of text and set it to buffer
		fgets(buffer, MAXWORD, fp);
		// set last char of buffer to null char
		buffer[strlen(buffer) - 1] = '\0';
		fprintf(stdout, "line: %s\n", buffer);

		// get string up to ':'
		char* token = strtok(buffer, ":");
		fprintf(stdout, "name: %s\n", token);

		while (token != NULL) {
			fprintf(stdout, "word: %s\n", token);
			// get string up to ', '
			token = strtok(NULL, ", ");
			// set
		}
	}

	return true;
}