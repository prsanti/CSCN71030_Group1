// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "connection.h"
#include "list.h"
#include "file.h"
#include "menu.h"
#include "game.h"

#define FILE "connectionsData.txt"

int main(void) {
	// randomize by time
	srand(time(NULL));

	// create pointer array of connections
	CONNECTION* connectionArr[TOTALCONNECTIONS];

	// read file data and load data into linked list
	if (loadData(FILE, &connectionArr) == false) {
		// close program with error
		exit(EXIT_FAILURE);
	}

	// initialize head of linked list
	NODE* head = NULL;

	//initialize game state
	GAME_STATE gameState;

	int choice;

	do {
		choice = displayMenu();
		switch (choice) {
		case 1:
			head = (NODE*)malloc(sizeof(NODE));		//allocate mem for head
			if (head == NULL) {
				fprintf(stderr, "Error allocating memory for head node\n");
				exit(EXIT_FAILURE);
			}

			// create linked list
			createList(head, connectionArr);

			// initialize and start the game
			initializeGame(&gameState, head);
			startGame(&gameState);

			// free the linked list after the game ends
			deleteNode(head);
			free(head);
			head = NULL; // set head to NULL after freeing
			break;
		case 2:
			// Print highscores (implement this function as needed
			break;

		case 3:
			printf("Exiting game. See you soon!!!\n");
			break;

		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 3);

	// Free memory allocated for connections
	for (int i = 0; i < TOTALCONNECTIONS; i++) {
		free(connectionArr[i]);
	}

	return 0;
}