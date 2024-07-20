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
    // where result is stored
    // main game loop - 4 lives
    while (gameState->lives > 0)
    {


        char guess[MAXBUFFER] = { 0 };                  // user input buffer
        char* splitGuess[MAX_WORDS_PER_GUESS] = { 0 };  // array where words will be stored
        int numWordsInGuess = 0;                        // number of words in the guess


        GUESS_RESULT guessResult;


        // print player info
        printGameState(gameState);

        do {
            // reset the guess buffer and splitGuess array for each new attempt
            resetGuessBuffers(guess, splitGuess, MAXBUFFER, MAX_WORDS_PER_GUESS);

            // ask user for input
            getUserInputGuess(guess, MAXBUFFER);

            // capitalize the string;
            capitalizeString(guess);

            // parse the guess into separate words
            numWordsInGuess = splitGuessIntoWords(guess, splitGuess, MAX_WORDS_PER_GUESS);

            if (numWordsInGuess < 4) {
                printf("Error: Please enter exactly 4 words. Example: red blue green yellow\n");
            }

        } while (numWordsInGuess < 4); // Repeat until exactly 4 words are entered

        // check guess in connection
        guessResult = isGuessAConnection(gameState, splitGuess);

        //check if guess was already guessed
        //if (guessResult.matchedConnection->c.wasGuessed == true)
        //{
        //    printf("Connection already Guessed\n");
        //}
        //check if guess was correct
        if (guessResult.isConnection)
        {
            printf("Correct Guess!\n");
            printf("Connection made: %s\n", guessResult.matchedConnection->c.name);
        }
        else 
        {
            printf("Incorrect Guess!\n");
            gameState->lives--; // Decrement lives for incorrect guess
        }

        if (gameState->lives <= 0) 
        {
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
    //printf("\nprinting the guess before split: %s\n", guess);

    int word_count = 0;
    char* word = strtok(guess, " ");
    while (word != NULL && word_count < max_words_per_guess) 
    {
        splitGuess[word_count] = word;  // store each word in an array index
        word_count++;                   // ************BUG: currently maxes out at 4 words even if you type more than 4 because 4 is the exit conidtion
        word = strtok(NULL, " ");
    }

    //printWordsAfterSplit(splitGuess, word_count);

    return word_count;
}

void getUserInputGuess(char* guess, int size)
{
    // prompt the user for a guess - example "red blue green yellow"
    printf("Enter your guess (words separated by spaces): ");
    fgets(guess, size, stdin);
    guess[strcspn(guess, "\n")] = '\0'; // remove newline character
}


// BUG - works only if user types in 4 guesses, otherwise theres an issue.
// check if each word in the split word array is in a connection (PROCESS 1 guess)
GUESS_RESULT isGuessAConnection(GAME_STATE* gameState, char* splitGuess[])
{
    GUESS_RESULT result = { false, NULL };

    int matchCount = 0;

    // start at the first set of connections (1 of 4)
    NODE* currentNode = gameState->head;

    // traverse the linked list
    while (currentNode != NULL)
    {
        // loop through each word in the array of split guesses
        for (int i = 0; i < MAX_WORDS_PER_GUESS; i++)
        {
            // loop through the words in the current node's connection
            for (int j = 0; j < WORDS_IN_ONE_CONNECTION; j++)
            {
                // check if the word matches
                if (strcmp(splitGuess[i], currentNode->c.words[j]) == 0)
                {
                    matchCount++;
                    break; // exit inner loop if a match is found
                }
            }
        }

        // check if there are at least 4 matches in this connection
        if (matchCount >= 4)
        {
            result.isConnection = true;
            result.matchedConnection = currentNode;
            result.matchedConnection->c.wasGuessed = true;
            return result; // return early since a valid connection was found
        }

        // go to the next node in the linked list
        currentNode = currentNode->next;
    }
    // Check if there are at least 4 matches
    return result;
}

 

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


void resetGuessBuffers(char guess[], char* splitGuess[], int guessSize, int splitGuessSize)
{
    memset(guess, 0, guessSize); // reset initial guess array

    for (int i = 0; i < splitGuessSize; i++)  // reset the splitGuess array;
    {
        splitGuess[i] = NULL;
    }
}



// writing this so i dont forget later
// iterate through the linked list
// check the bool flag of each connection,
// if all are made, make a new game