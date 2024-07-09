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

bool loadData(char* filename, NODE* ptr) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file\n");
		return false;
	}

	//CONNECTION c1 = { '\0', {'\0'} }, c2 = { '\0', {'\0'} }, c3 = { '\0', {'\0'} }, c4 = { '\0', {'\0'} };
	CONNECTION connectionArr[MAXCONNECTIONS];

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
			//connectionArr[i] = createConnection(name, words);

			j++;
		}
		// create connection
		//CONNECTION newConnection = createConnection(name, words);
		connectionArr[i] = createConnection(name, words);
		//printConnection(newConnection);
		//switch (i) {
		//	case 0:
		//		c1 = newConnection;
		//		break;
		//	case 1:
		//		c2 = newConnection;
		//		break;
		//	case 2:
		//		c3 = newConnection;
		//		break;		
		//	default:
		//		c4 = newConnection;
		//		break;
		//}

		//CONNECTION connectionArr[MAXCONNECTIONS] = { c1, c2, c3, c4 };

		
		/*connectionArr[i] = newConnection;*/

		// create connection and create linked list
		//CONNECTION newConnection = createConnection(name, words);
		////addToList(ptr, newConnection, MAXCONNECTIONS);
		//ptr->c = newConnection;
		//ptr->next = (NODE*)malloc(sizeof(struct node));

		//if (ptr->next == NULL) {
		//	printf("Error allocating memory\n");
		//	break;
		//}

		//ptr = ptr->next;
	}

	//ptr->next = NULL;

	//connectionArr[0] = c1;
	//connectionArr[1] = c2;
	//connectionArr[2] = c3;
	//connectionArr[3] = c4;

	//addToList(ptr, connectionArr);

	//for (int i = 0; i < 4; i++) {
	//	printf("print con in file\n");
	//	printConnection(connectionArr[i]);
	//}

	addToList(ptr, connectionArr);

	return true;
}