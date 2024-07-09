// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "file.h"
#include "connection.h"
#include "list.h"

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

// get random line from text file data
void getRandomLine(FILE* fp, char** buffer) {
	// get total lines from file
	int lines = countLines(fp);
	int currentLine = 0;

	// generate random line
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

bool loadData(char* filename, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file\n");
		return false;
	}

	//CONNECTION connectionArr[MAXCONNECTIONS];

	char buffer[MAXBUFFER] = { '\0' };

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
		if (connectionArr[i] == NULL) {
			fprintf(stderr, "Cannot allocate memory to connection array\n");
			//fclose(fp);
			return false;
		}

		// create connection and set to array
		*connectionArr[i] = createConnection(name, words);
		//printConnection(*connectionArr[i]);
	}

	// for testing created connections
	//for (int i = 0; i < TOTALCONNECTIONS; i++) {
	//	printf("testing connection array\n");
	//	printConnection(connectionArr[i]);
	//}

	//addToList(ptr, connectionArr);

	return true;
}