#pragma once

#include "game.h"


void initializeGame(GAME_STATE* gameState, NODE* head)
{
    gameState->head = head; // set the connections
    strcpy(gameState->player.name, "samplePlayer");	// set the name
    gameState->player.score = 0;	// set the score
    gameState->lives = MAX_LIVES; // set the lives
}

void startGame(GAME_STATE* gameState)
{
    char guess[200];

    // main game loop - 4 lives
    while (gameState->lives > 0)
    {
        printGameState(gameState);

        // prompt the user for a guess - example "red blue green yellow"
        printf("Enter your guess (words separated by spaces): ");
        fgets(guess, sizeof(guess), stdin);
        guess[strcspn(guess, "\n")] = '\0'; // remove  newline character

        // parse the guess into separate words
        char* words[MAX_WORDS_PER_GUESS];      // array where words will be stored
        int test = splitGuessIntoWords(guess, words, MAX_WORDS_PER_GUESS);

        printf("Number of words in guess: %d\n\n\n\n", test);

        if (gameState->lives <= 0) {
            printf("No lives left, Game Over!\n");
            break;
        }
    }
}

void printGameState(const GAME_STATE* gameState)
{
    printf("\nPlayer: %s\n", gameState->player.name);
    printf("Score: %d\n", gameState->player.score);
    printf("Lives: %d\n\n", gameState->lives);
    traverse(gameState->head);
}

int validateGuess(GAME_STATE* gameState, const char* guess)
{

}

int splitGuessIntoWords(char* guess, char* words[], int max_words_per_guess)
{
    int word_count = 0;
    char* word = strtok(guess, " ");

    while (word != NULL && word_count < max_words_per_guess) {
        words[word_count] = word; // store the word
        word_count++;
        word = strtok(NULL, " ");
    }
    return word_count;
}