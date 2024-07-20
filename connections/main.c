// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "connection.h"
#include "list.h"
#include "file.h"
#include "game.h"
#include "menu.h"

#define FILENAME "connectionsData.txt"

int main(void) {
    // Randomize by time
    srand(time(NULL));

    // Create pointer array of connections
    CONNECTION* connectionArr[TOTALCONNECTIONS];

    // Read file data and load data into connection array
    if (!loadData(FILENAME, connectionArr)) {
        // Close program with error
        exit(EXIT_FAILURE);
    }

    NODE* head = NULL;
    GAME_STATE gameState;
    int choice;

    do {
        choice = displayMenu();
        switch (choice) {
        case 1:
            // Allocate memory for the head node
            head = (NODE*)malloc(sizeof(NODE));
            if (head == NULL) {
                fprintf(stderr, "Error allocating memory for head node\n");
                exit(EXIT_FAILURE);
            }

            // Create linked list
            createList(head, connectionArr);

            // Initialize and start the game
            initializeGame(&gameState, head);
            startGame(&gameState);

            // Free the linked list after the game ends
            deleteNode(head);
            free(head);
            head = NULL; // Set head to NULL after freeing
            break;

        case 2:
            // Print highscores (implement this function as needed)
            // printHighscores(highscore);
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
