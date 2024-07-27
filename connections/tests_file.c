#include "tests_file.h"
#define FILENAME "connectionsData.txt"

// manual tests
// REQ_IO_001
bool countLinesTest(void) {
	printf("REQ_IO_001\n");
	printf("Count total lines from text file data shall be tested. \n");
	int expected = 44;

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

void runAllFileTests() {
	countLinesTest();
	getRandomLineTest();
	loadDataTest();
}