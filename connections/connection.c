// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "connection.h"
#define FILENAME "connectionsData.txt"

// print connection for testing
void printConnection(CONNECTION c) {
	fprintf(stdout, "Name: %s\n", c.name);
	for (int i = 0; i < MAXCONNECTIONS; i++) {
		fprintf(stdout, "Connecetion %d: %s\n", i, c.words[i]);
	}
}

// create a connection with a category name and array of 4 words
CONNECTION createConnection(char name[MAXWORD], char wordList[MAXCONNECTIONS][MAXWORD]) {
	CONNECTION c;
	strncpy(c.name, name, MAXWORD);

	for (int i = 0; i < MAXCONNECTIONS; i++) {
		strncpy(c.words[i], wordList[i], MAXWORD);
	}

	// for testing
	//printf("Connection created:\n");
	//printConnection(c);

	return c;
}

// copy a connection from a source
CONNECTION copyConnection(CONNECTION src) {
	return createConnection(src.name, src.words);
}

// manual tests

// REQ_IO_001
bool countLinesTest(void) {
	printf("REQ_IO_001\n");
	printf("Count total lines from text file data shall be tested. \n");
	int expected = 0;

	FILE* fp = fopen(FILENAME, "r");
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