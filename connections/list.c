// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// linked list functions

#include "list.h"

void createList(NODE* ptr, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
	for (int i = 0; i < TOTALCONNECTIONS; i++) {
		ptr->c = *connectionArr[i];
		
		ptr->next = (NODE*)malloc(sizeof(NODE));

		if (ptr->next == NULL) {
			printf("Error allocating memory\n");
			break;
		}

		ptr = ptr->next;
	}

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
