// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// linked list functions

#include "list.h"

void addToList(NODE* ptr, CONNECTION connectArr[MAXCONNECTIONS]) {
	//for (int i = 0; i < counter; i++) {
	//	ptr->c = connect;
	//	ptr->next = (NODE*)malloc(sizeof(struct node));

	//	if (ptr->next == NULL) {
	//		printf("Error allocating memory\n");
	//		break;
	//	}

	//	ptr = ptr->next;
	//}
	//ptr->next = NULL;

	// print connection
	//for (int i = 0; i < MAXCONNECTIONS; i++) {
	//	printf("print in list\n");
	//	printConnection(connectArr[i]);
	//}

	for (int i = 0; i < MAXCONNECTIONS; i++) {
		ptr->c = connectArr[i];
		ptr->next = (NODE*)malloc(sizeof(struct node));

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
	}
}