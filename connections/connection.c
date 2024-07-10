// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "connection.h"

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