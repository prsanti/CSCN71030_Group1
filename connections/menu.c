#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "menu.h"

int displayMenu() {
    int choice;
    char inputBuffer[100];
    printf("Welcome to Connections\n");
    printf("Please proceed by entering the number of the option you wish to execute\n");
    printf("1) Start Game\n");
    printf("2) Show Highscores\n");
    printf("3) Exit\n");
    printf("Enter choice: ");
    // Use fgets to get input and handle the buffer
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) {
        // Convert the input to an integer
        choice = atoi(inputBuffer); // atoi returns 0 if input is not a valid integer
    }
    else {
        choice = 0; // Default value if input failed
    }

    return choice;
}