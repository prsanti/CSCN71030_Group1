// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "file.h"
#include "connection.h"
#include "list.h"
#define FILENAME "connectionsData.txt"

// function to count the number of lines in a file
// allows us to add more connections without having a static count
int countLines(FILE* fp) {
	// potential debug
	// set lines to 1 and adjust file to start at 1
	int lines = 1;
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

// read line from text file data and change buffer to it
void readRandomLine(FILE* fp, int line, char** buffer) {
	// get total lines from file
	int lines = countLines(fp);
	int currentLine = 1;

	char ch = { '\0' };

	// reset file pointer to beginning of file
	fseek(fp, 0, SEEK_SET);

	// loop until current line reaches random line or end of file
	while (currentLine < line && !feof(fp)) {
		// get char of each character of line until end of line
		ch = fgetc(fp);
	
		if (ch == '\n') {
			// increment current line
			currentLine++;
		}
	}

	// if error or no line is read set buffer back to null
	// set buffer to read line
	if (fgets(buffer, MAXBUFFER, fp) == NULL) {
		buffer[0] = '\0';
	}
}

// get and return random line from file
int getRandomLine(FILE* fp) {
	// get total lines from file
	int lines = countLines(fp);
	int currentLine = 1;

	// generate random line and set min line to 1
	int randomLine = 1 + (rand() % lines);

	return randomLine;
}

// assign random line to array
bool assignLines(FILE* fp, int readLines[]) {
	// true by default
	bool isMatching = true;

	while (isMatching) {
		readLines[0] = getRandomLine(fp);
		readLines[1] = getRandomLine(fp);
		readLines[2] = getRandomLine(fp);
		readLines[3] = getRandomLine(fp);

		// if all lines are different then break out of loop
		if (readLines[0] != readLines[1] && readLines[0] != readLines[2] && readLines[0] != readLines[3] && readLines[1] != readLines[2] && readLines[1] != readLines[3] && readLines[2] != readLines[3]) {
			isMatching = false;
		}
	}

	return true;
}

// load data from connectionData.txt
// set data to connectionArr to be used for creating linked list
bool loadData(char* filename, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
	// read connectionsData.txt
	FILE* fp = fopen(filename, "r");

	// print error if cannot open file
	if (fp == NULL) {
		fprintf(stderr, "Error opening file\n");
		return false;
	}

	// char buffer
	char buffer[MAXBUFFER] = { '\0' };

	// chars to assign to array of connections
	char name[MAXWORD];
	char words[MAXCONNECTIONS][MAXWORD];

	// random lines used
	int readLines[MAXLINES];

	// assign random lines to array until they are different
	while (assignLines(fp, readLines) != true);

	for (int i = 0; i < TOTALCONNECTIONS; i++) {
		readRandomLine(fp, readLines[i], buffer);
		// set last char of buffer to null char
		buffer[strlen(buffer) - 1] = '\0';
		//fprintf(stdout, "line: %s\n", buffer);

		// get string up to ':'
		char* token = strtok(buffer, ":");
		strncpy(name, token, MAXWORD);
		//fprintf(stdout, "name: %s\n", token);

		// loop counter for words array
		int j = 0;

		while (token != NULL) {
			// get string up to ', '
			token = strtok(NULL, ", ");

			// check if token is null and end loop (last word bug)
			if (token == NULL) {
				break;
			}

			//fprintf(stdout, "word: %s\n", token);
			// set word array to token
			strncpy(words[j], token, MAXWORD);
			//fprintf(stdout, words[j]);

			j++;
		}

		// Allocate memory for each connection
		connectionArr[i] = (CONNECTION*)malloc(sizeof(CONNECTION));

		// print error if cannot allocate memory to array
		if (connectionArr[i] == NULL) {
			fprintf(stderr, "Cannot allocate memory to connection array\n");
			return false;
		}

		// create connection and set to array
		*connectionArr[i] = createConnection(name, words);
		// for testing created connections
		//printConnection(*connectionArr[i]);
	}

	// successful read and assigning data to array
	return true;
}

