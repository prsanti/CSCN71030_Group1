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
    //randomize by time
    srand(time(NULL));

    //create pointer array of connections
    CONNECTION* connectionArr[TOTALCONNECTIONS];

    //read file data and load data into connection array
    if (!loadData(FILENAME, connectionArr)) {
        //close program with error
        exit(EXIT_FAILURE);
    }

    NODE* head = NULL;
    GAME_STATE gameState;
    int choice;

    do {
        choice = displayMenu();
        switch (choice) {
        case 1:
            //allocate memory for the head node
            head = (NODE*)malloc(sizeof(NODE));
            if (head == NULL) {
                fprintf(stderr, "Error allocating memory for head node\n");
                exit(EXIT_FAILURE);
            }

            //create linked list
            createList(head, connectionArr);

            //initialize and start the game
            initializeGame(&gameState, head);
            printGameState(&gameState);
            startGame(&gameState);

            //free the linked list after the game ends
            deleteNode(head);
            free(head);
            head = NULL; //set head to NULL after freeing
            break;

        case 2:
            //print highscores (implement this function as needed)
            //printHighscores(highscore);
            break;

        case 3:
            printf("Exiting game. See you soon!!!\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 3);

    //free memory allocated for connections
    for (int i = 0; i < TOTALCONNECTIONS; i++) {
        free(connectionArr[i]);
    }

    return 0;
}

