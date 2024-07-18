// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "connection.h"
#include "list.h"
#include "file.h"

#include "game.h"

#define FILE "connectionsData.txt"

int main(void) {
	// randomize by time
	srand(time(NULL));

	// initialize head of linked list
	NODE* head = (NODE*)malloc(sizeof(NODE));

	// create pointer array of connections
	CONNECTION *connectionArr[TOTALCONNECTIONS];

	// read file data and load data into linked list
	if (loadData(FILE, &connectionArr) == false) {
		// close program with error
		exit(EXIT_FAILURE);
	}

	// create linked list
	createList(head, connectionArr);

	// traverse linked list
	//traverse(head);

	//initialize game state
	GAME_STATE gameState;
	initializeGame(&gameState, head);
	printGameState(&gameState);
	startGame(&gameState);

	// delete and free nodes from linked list
	deleteNode(head);

	return 0;
}