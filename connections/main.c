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
	NODE* head = (NODE*)malloc(sizeof(struct node));

	// read file data and load data into linked list
	if (loadData(FILE, head) == false) {
		// close program with error
		exit(EXIT_FAILURE);
	}

	traverse(head);



	free(head);

	return 0;
}