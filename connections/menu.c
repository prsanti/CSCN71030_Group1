#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "menu.h"
int displayMenu() {
    int choice;
    printf("Welcome to Connections\n");
    printf("Please proceed by entering the number of the option you wish to execute\n");
    printf("1) Start Game\n");
    printf("2) Show Highscores\n");
    printf("3) Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    return choice;
}