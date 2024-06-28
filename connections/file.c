// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "file.h"

// function to count the number of lines in a file
// allows us to add more connections without having a static count
int countLines(FILE* fp) {
	int lines = 0;
	char ch;

	// loop until end of file
	while (!feof(fp)) {
		ch = fgetc(fp);
		// read each line until '\n'
		if (ch == '\n') {
			// increment lines by 1
			lines++;
		}
	}

	// reset file pointer to beginning of file
	fseek(fp, 0, SEEK_SET);

	return lines;
}

bool loadData(char* filename) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file\n");
		return false;
	}

	// get total lines from file
	int lines = countLines(fp);
	printf("lines: %d\n", lines);

	CONNECTION c1, c2, c3, c4;

	char buffer[MAXBUFFER] = '\0';

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
		strncpy(name, token, MAXWORD);
		fprintf(stdout, "name: %s\n", token);

		while (token != NULL) {
			// get string up to ', '
			token = strtok(NULL, ", ");

			// check if token is null and end loop (last word bug)
			if (token == NULL) {
				return;
			}

			fprintf(stdout, "word: %s\n", token);
			// set

		}
	}

	return true;
}