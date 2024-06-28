// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "connection.h"

void printConnection(CONNECTION c) {
	fprintf(stdout, "Name: %s\n", c.name);
	for (int i = 0; i < MAXCONNECTIONS; i++) {
		fprintf(stdout, "Connecetion %d: %s\n", i, c.words[i]);
		//fprintf(stdout, "Connecetion %d %s\n", i, c.words[i]);
		//fprintf(stdout, "Connecetion %d %s\n", i, c.words[i]);
		//fprintf(stdout, "Connecetion %d %s\n", i, c.words[i]);
	}
}

CONNECTION createConnection(char name[MAXWORD], char wordList[MAXCONNECTIONS][MAXWORD]) {
	CONNECTION c;
	strncpy(c.name, name, MAXWORD);

	for (int i = 0; i < MAXCONNECTIONS; i++) {
		strncpy(c.words[i], wordList[i], MAXWORD);
	}

	// for testing
	printConnection(c);

	return c;
}