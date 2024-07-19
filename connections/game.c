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

        // capitalize the string;
        capitalizeString(guess);

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



int splitGuessIntoWords(char* guess, char* splitGuess[], int max_words_per_guess)
{
    printf("\nprinting the guess before split: %s\n", guess);

    int word_count = 0;
    char* word = strtok(guess, " ");
    while (word != NULL && word_count < max_words_per_guess) 
    {
        splitGuess[word_count] = word;  // store each word in an array index
        word_count++;                   // ************BUG: currently maxes out at 4 words even if you type more than 4 because 4 is the exit conidtion
        word = strtok(NULL, " ");
    }

    printWordsAfterSplit(splitGuess, word_count);

    return word_count;
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





//// check if each word in the split word array is in a connection - check if there is 4 matches. 
//bool isGuessAConnection(GAME_STATE* gameState, char* splitGuess[])
//{
//    // loop through each word in the split guess array
//    for (int i = 0; i < MAX_WORDS_PER_GUESS; i++)
//    {
//        // check if that word is in the connection list
//        if(splitGuess[i] ==)
//    }
//
//}

void capitalizeString(char* str)
{
    while (*str) 
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
}







// This function is just for helping me test
void printWordsAfterSplit(char* splitGuess[], int word_count) 
{
    printf("Number of words in guess: %d\n", word_count);


    printf("Printing the guess after split:\n");
    for (int i = 0; i < word_count; i++) 
    {
        
        printf("Word %d: %s\n", i + 1, splitGuess[i]);
    }
}

