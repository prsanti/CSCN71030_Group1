// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "connection.h"

void printConnection(CONNECTION c) {
	fprintf(stdout, "Name: %s\n", c.name);
	for (int i = 0; i < MAXCONNECTIONS; i++) {
		fprintf(stdout, "Connecetion %d: %s\n", i, c.words[i]);
		fprintf(stdout, "Connecetion %d %s\n", i, c.words[i]);
		fprintf(stdout, "Connecetion %d %s\n", i, c.words[i]);
		fprintf(stdout, "Connecetion %d %s\n", i, c.words[i]);
	}
}

CONNECTION createConnection(char* name, char* word1, char* word2, char* word3, char* word4) {
	CONNECTION c;
	strncpy(c.name, name, MAXWORD);
	return c;
}