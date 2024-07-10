// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// linked list functions

#include "list.h"

// create linked list
void createList(NODE* ptr, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
	// loop through total connections
	for (int i = 0; i < TOTALCONNECTIONS; i++) {
		// set pointer to connection of array
		ptr->c = *connectionArr[i];
		
		// allocate memory for next node
		ptr->next = (NODE*)malloc(sizeof(NODE));

		// print error messege for allocating memory
		if (ptr->next == NULL) {
			printf("Error allocating memory\n");
			break;
		}

		// set pointer to next
		ptr = ptr->next;
	}

	// set last pointer next to NULL
	ptr->next = NULL;
}

// print and traverse connection of each node
void traverse(NODE* ptr) {
	while (ptr->next != NULL) {
		printConnection(ptr->c);
		ptr = ptr->next;
	}
}

// traverse and free each node
void deleteNode(NODE* ptr) {
	while (ptr->next != NULL) {
		NODE* temp;
		temp = ptr;

		// for testing free node
		//printf("Deleting node:\n");
		//printConnection(temp->c);

		// set pointer to next node
		ptr = ptr->next;

		// free current node
		free(temp);
	}
}
