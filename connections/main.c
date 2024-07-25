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
#include "tests.h"

#define FILE "connectionsData.txt"

int main(int argc, char* argv[]) {
    // Check if the username is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Get the username from command line argument
    char* username = argv[1];

    // Randomize by time
    srand(time(NULL));

    // Create pointer array of connections
    CONNECTION* connectionArr[TOTALCONNECTIONS];

    // Read file data and load data into connection array
    if (!loadData(FILE, connectionArr)) {
        // Close program with error
        exit(EXIT_FAILURE);
    }

    NODE* head = NULL;
    GAME_STATE gameState;
    HIGHSCORE highScores;
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
            initializeGame(&gameState, head, &highScores, username);
            startGame(&gameState, &highScores);

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
        case 4:
            runTests();
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