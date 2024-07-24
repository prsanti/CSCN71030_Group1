#pragma once

#include "game.h"


void initializeGame(GAME_STATE* gameState, NODE* head)
{
    gameState->head = head; // set the connections
    strcpy(gameState->player.name, "samplePlayer");	// set the name
    gameState->player.score = 0;	// set the score
    gameState->lives = MAX_LIVES; // set the lives

    initializeConnections(head); // set the connections flag to false
}

void initializeConnections(NODE* head)
{
    NODE* currentNode = head;
    while (currentNode != NULL) {
        currentNode->c.wasGuessed = false; // set the connections flag to false
        currentNode = currentNode->next;
    }
}

void startGame(GAME_STATE* gameState)
{
    while (gameState->lives > 0) 
    {
        printGameState(gameState); // print the game
        processGuess(gameState);   // get a guess and process it
        if (gameState->lives <= 0) // after 4 lives are finished game is done
        {
            printf("No lives left, Game Over!\n");
        }
    }
}

void processGuess(GAME_STATE* gameState)
{
    // initialize variables
    char guess[MAXBUFFER] = { 0 };                  // used for getting input
    char* splitGuess[MAX_WORDS_PER_GUESS] = { 0 };  // used for putting words into an array
    int numWordsInGuess = 0;                        // used for counting if user typed in correct number of guesses
    GUESS_RESULT guessResult;                       // used for returning which node is a connection


    // get user input and make sure it is 4 words
    // at the same time it puts each word into a string and capitalizes everything
    do {
        resetGuessBuffers(guess, splitGuess, MAXBUFFER, MAX_WORDS_PER_GUESS);
        getUserInputGuess(guess, MAXBUFFER);
        capitalizeString(guess);
        numWordsInGuess = splitGuessIntoWords(guess, splitGuess, MAX_WORDS_PER_GUESS);

        if (numWordsInGuess < MAX_WORDS_PER_GUESS) {
            printf("Error: Please enter exactly 4 words. Example: red blue green yellow\n");
        }
    } while (numWordsInGuess < MAX_WORDS_PER_GUESS);    // will run until user enters 4 words

    // process guess
    guessResult = isGuessAConnection(gameState, splitGuess); // this returns the correctly guessed node

    if (guessResult.isConnection)
    {
        handleCorrectGuess(gameState, guessResult);
    }
    else
    {
        handleIncorrectGuess(gameState);
    }
}

void handleCorrectGuess(GAME_STATE* gameState, GUESS_RESULT guessResult)
{
    // if connection was already guessed
    if (guessResult.matchedConnection->c.wasGuessed)
    {
        printGuessFeedback(guessResult, true);
    }
    else // first time being guessed
    {
        printGuessFeedback(guessResult, false);
        guessResult.matchedConnection->c.wasGuessed = true;
        gameState->player.score += 10; // Example score increment
    }
}

void printGuessFeedback(const GUESS_RESULT guessResult, bool isAlreadyGuessed)
{
    if (isAlreadyGuessed)
    {
        printf("\033[33mConnection already guessed: %s\033[0m\n", guessResult.matchedConnection->c.name);
    }
    else
    {
        printf("\033[32mCorrect Guess!\n");
        printf("Connection made: %s\033[0m\n", guessResult.matchedConnection->c.name);
    }
}

void handleIncorrectGuess(GAME_STATE* gameState)
{
    printf("\033[31mIncorrect Guess!\n\033[0m");
    gameState->lives--;
}

void printGameState(const GAME_STATE* gameState)
{
    printf("\nPlayer: %s\n", gameState->player.name);
    printf("Score: %d\n", gameState->player.score);
    printf("Lives: %d\n\n", gameState->lives);
    traverse(gameState->head);
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
    NODE* currentNode = gameState->head;

    // Iterate through each connection node in the linked list
    while (currentNode != NULL)
    {
        int matchCount = 0;  // Reset matchCount for each connection

        // Iterate through each word in the split guess
        for (int i = 0; i < MAX_WORDS_PER_GUESS; i++)
        {
            // Iterate through each word in the current connection
            for (int j = 0; j < WORDS_IN_ONE_CONNECTION; j++)
            {
                // Check if the guessed word matches any word in the connection
                if (strcmp(splitGuess[i], currentNode->c.words[j]) == 0)
                {
                    matchCount++;  // Increment match count for each matching word
                    break;  // Stop checking this guessed word against other words in the same connection
                }
            }
        }

        // If all guessed words match the connection, mark it as a valid connection
        if (matchCount == MAX_WORDS_PER_GUESS)
        {
            result.isConnection = true;
            result.matchedConnection = currentNode;
            return result; // Return early since a valid connection was found
        }

        currentNode = currentNode->next; // Move to the next node in the linked list
    }

    // If no valid connection was found, return result with isConnection set to false
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
