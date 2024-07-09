// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "connection.h"
#include "list.h"
#include "file.h"

#define FILE "connectionsData.txt"

int main(void) {
	// randomize by time
	srand(time(NULL));

	// initialize head of linked list
	NODE* head = (NODE*)malloc(sizeof(NODE));

	CONNECTION *connectionArr[TOTALCONNECTIONS];

	// read file data and load data into linked list
	if (loadData(FILE, &connectionArr) == false) {
		// close program with error
		exit(EXIT_FAILURE);
	}

	//for (int i = 0; i < TOTALCONNECTIONS; i++) {
	//	printConnection(*connectionArr[i]);
	//}

	createList(head, connectionArr);

	traverse(head);

	deleteNode(head);

	return 0;
}