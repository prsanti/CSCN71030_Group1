// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "connection.h"

// print connection for testing
void printConnection(CONNECTION c) {
	fprintf(stdout, "Name: %s\n", c.name);
	for (int i = 0; i < MAXCONNECTIONS; i++) {
		fprintf(stdout, "Connecetion %d: %s\n", i, c.words[i]);
	}
	fprintf(stdout, "Is Guessed: %d\n", c.wasGuessed);
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

// manual test functions for connection module
bool createConnectionTest(void) {
	printf("REQ_CON_001\n");
	printf("Create Connection struct shall be tested.\n");

	bool expected = true;
	bool result = true;

	char name[MAXWORD] = "testName";
	char wordList[MAXCONNECTIONS][MAXWORD] = { "test1", "test2", "test3", "test4" };

	CONNECTION temp = createConnection(name, wordList);

	if (temp.name == '\0') {
		result = false;
	}

	for (int i = 0; i < MAXCONNECTIONS; i++) {
		if (temp.words[i] == '\0') {
			result = false;
		}
	}
	
	if (expected == result) {
		printf("Test passed\n");
		return true;
	}
	else {
		printf("Test failed\n");
		printf("Created CONNECTION: \n");
		printConnection(temp);
		return false;
	}
}