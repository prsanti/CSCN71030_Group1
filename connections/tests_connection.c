#include "tests_connection.h"

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