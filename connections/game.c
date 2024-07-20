#pragma once
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Define grid dimensions
#define GRID_WIDTH 4
#define GRID_HEIGHT 4

void initializeGame(GAME_STATE* gameState, NODE* head) {
    gameState->head = head; // set the connections
    strcpy(gameState->player.name, "samplePlayer"); // set the name
    gameState->player.score = 0; // set the score
    gameState->lives = MAX_LIVES; // set the lives
}

void startGame(GAME_STATE* gameState) {
    char guess[200];

    // main game loop - 4 lives
    while (gameState->lives > 0) {
        printGameState(gameState); // Print game state once per iteration

        // prompt the user for a guess - example "red blue green yellow"
        printf("Enter your guess (words separated by spaces): ");
        fgets(guess, sizeof(guess), stdin);
        guess[strcspn(guess, "\n")] = '\0'; // remove newline character

        // parse the guess into separate words
        char* words[MAX_WORDS_PER_GUESS]; // array where words will be stored
        int numWords = splitGuessIntoWords(guess, words, MAX_WORDS_PER_GUESS);

        printf("Number of words in guess: %d\n\n", numWords);

        // Add game logic to validate guess and update game state here

        if (gameState->lives <= 0) {
            printf("No lives left, Game Over!\n");
            break;
        }
    }
}

void printGameState(const GAME_STATE* gameState) {
    printf("\nPlayer: %s\n", gameState->player.name);
    printf("Score: %d\n", gameState->player.score);
    printf("Lives: %d\n\n", gameState->lives);

    // Create an array to store the words
    char* words[GRID_WIDTH * GRID_HEIGHT];
    int count = 0;

    NODE* ptr = gameState->head;
    while (ptr != NULL && count < GRID_WIDTH * GRID_HEIGHT) {
        words[count] = ptr->c.words[count % MAXCONNECTIONS];
        count++;
        if (count % GRID_WIDTH == 0) {
            ptr = ptr->next; // Move to the next node after filling a row
        }
    }

    // Shuffle the words
    shuffleArray(words, GRID_WIDTH * GRID_HEIGHT);

    // Print the grid
    printf("+------------------+------------------+------------------+------------------+\n");
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        printf("| %-16s ", words[i] ? words[i] : ""); // Print word or empty space
        if ((i + 1) % GRID_WIDTH == 0) {
            printf("|\n");
            printf("+------------------+------------------+------------------+------------------+\n");
        }
    }
}

void shuffleArray(char* array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int validateGuess(GAME_STATE* gameState, const char* guess) {
    //implement validation logic here
    return 0; //placeholder return value
}

int splitGuessIntoWords(char* guess, char* words[], int max_words_per_guess) {
    int word_count = 0;
    char* word = strtok(guess, " ");

    while (word != NULL && word_count < max_words_per_guess) {
        words[word_count] = word; //store the word
        word_count++;
        word = strtok(NULL, " ");
    }
    return word_count;
}

