#include "tests_list.h"
#define FILENAME "connectionsData.txt"

// manual test functions for list module
bool createListTest(void) {
	printf("REQ_LIST_001\n");
	printf("Create a linked list by creating nodes and linking them together to make a linked list.\n");

	NODE* head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL) {
		fprintf(stderr, "Error allocating memory for head node\n");
		exit(EXIT_FAILURE);
	}

	// Create pointer array of connections
	CONNECTION* connectionArr[TOTALCONNECTIONS];

	// Read file data and load data into connection array
	if (!loadData(FILENAME, connectionArr)) {
		// Close program with error
		exit(EXIT_FAILURE);
	}

	// Create linked list
	createList(head, connectionArr);

	// check each node
	traverse(head);

	// Free the linked list after the game ends
	deleteNode(head);

	printf("test passed\n");
}