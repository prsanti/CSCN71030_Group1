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
    char guess[MAXBUFFER];                 // user input buffer
    char* splitGuess[MAX_WORDS_PER_GUESS]; // array where words will be stored
    int numWordsInGuess;                   // number of words in the guess

    // main game loop - 4 lives
    while (gameState->lives > 0)
    {
        // print player info
        printGameState(gameState);

        // ask user for input
        getUserInputGuess(guess, MAXBUFFER);

        // parse the guess into separate words
        splitGuessIntoWords(guess, splitGuess, MAX_WORDS_PER_GUESS);

        // reset guess
        resetGuess(guess, MAXBUFFER);


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

void splitGuessIntoWords(char* guess, char* splitGuess[], int max_words_per_guess)
{
    printf("printing the guess before split: %s\n", guess);

    int word_count = 0;
    char* word = strtok(guess, " ");

    while (word != NULL && word_count < max_words_per_guess) 
    {
        splitGuess[word_count] = word; // store the word
        word_count++;                                                           // currently maxes out at 4 even if you type more than 4
        word = strtok(NULL, " ");
    }

    printf("Number of words in guess: %d\n", word_count);

    printf("printing the guess after  split: \n");

    for (int i = 0; i < word_count; i++)
    {
        printf("%s\n", splitGuess[i]);
    }
}

void getUserInputGuess(char* guess, int size)
{
    // prompt the user for a guess - example "red blue green yellow"
    printf("Enter your guess (words separated by spaces): ");
    fgets(guess, size, stdin);
    guess[strcspn(guess, "\n")] = '\0'; // remove newline character
}

void resetGuess(char* guess, int size)
{
    memset(guess, 0, size); // clear the guess buffer
}