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

// get random line from text file data
void getRandomLine(FILE* fp, char** buffer) {
	// get total lines from file
	int lines = countLines(fp);
	int currentLine = 0;

	// generate random line
	//Unhandled exception at 0x00007FF7F8331D31 in connections.exe: 0xC0000094 : Integer division by zero. (see line 11)
	int randomLine = rand() % lines;

	char ch = { '\0' };

	// reset file pointer to beginning of file
	fseek(fp, 0, SEEK_SET);

	// loop until current line reaches random line or end of file
	while (currentLine < randomLine && !feof(fp)) {
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

	for (int i = 0; i < TOTALCONNECTIONS; i++) {
		// read random line of text and set it to buffer
		getRandomLine(fp, buffer);
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

// manual tests
// REQ_IO_001
bool countLinesTest(void) {
	printf("REQ_IO_001\n");
	printf("Count total lines from text file data shall be tested. \n");
	// lines start at 0
	int expected = 43;

	FILE* fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		fprintf(stderr, "Test failed: Error opening file\n");
		return false;
	}

	int result = countLines(fp);

	if (expected == result) {
		printf("Test passed\n");
		return true;
	}
	else {
		printf("Test failed\n");
		return false;
	}
}

// REQ_IO_002
bool getRandomLineTest(void) {
	printf("REQ_IO_002\n");
	printf("Get random line from text file shall be tested.\n");

	// a random num from 0 to 43 will be the return
	char testBuffer[MAXBUFFER] = { '\0' };

	FILE* fp = fopen(FILENAME, "r");

	// print error if cannot open file
	if (fp == NULL) {
		fprintf(stderr, "Test failed: Error opening file\n");
		return false;
	}
	
	getRandomLine(fp, testBuffer);

	// check if buffer is assigned a correct line:
	if (testBuffer != '\0') {
		printf("Test passed\n");
		printf("Buffer returned: %s\n", testBuffer);
		return true;
	}
	else {
		printf("test failed\n");
		printf("Buffer returned: %s\n", testBuffer);
		return false;
	}
}

// REQ_IO_003
bool loadDataTest(void) {
	printf("REQ_IO_003\n");
	printf("Load data from text file and set data to an array of Connections shall be tested\n");

	bool expected = true;

	CONNECTION* connectionArr[TOTALCONNECTIONS];

	bool result = loadData(FILENAME, connectionArr);

	// manually check if connections are made in the array
	for (int i = 0; i < MAXCONNECTIONS; i++) {
		printConnection(*connectionArr[i]);
		// check if name and wasGuessed marker are valid when initialized
		if (*connectionArr[i]->name == '\0' || connectionArr[i]->wasGuessed == true) {
			result = false;
		}

		// check each connection words if they exist and are valid
		for (int j = 0; j < TOTALCONNECTIONS; j++) {
			if (connectionArr[i]->words[j] == '\0') {
				result = false;
			}
		}
	}

	if (expected == result) {
		printf("Test passed\n");
		return true;
	}
	else {
		printf("Test failed\n");
		return false;
	}
}