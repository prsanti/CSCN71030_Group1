#pragma once

#include "game.h"


void initializeGame(GAME_STATE* gameState, NODE* head, HIGHSCORE* highscore)
{
    gameState->head = head; // set the connections
    strcpy(gameState->player.name, "samplePlayer");	// set the name
    gameState->player.score = 0;	// set the score
    gameState->lives = MAX_LIVES; // set the lives
    gameState->isGameOver = false;

    initializeConnections(head); // set the connections flag to false
    loadHighscores(highscore, "highscores.txt"); // Load existing high scores

    // Shuffle words once here for display
    storeShuffledWords(gameState);
}

void initializeConnections(NODE* head)
{
    NODE* currentNode = head;
    while (currentNode != NULL) {
        currentNode->c.wasGuessed = false; // set the connections flag to false
        currentNode = currentNode->next;
    }
}

void startGame(GAME_STATE* gameState, HIGHSCORE* highscore)
{
    while (!gameState->isGameOver) 
    {
        printGameState(gameState); // print the game
        processGuess(gameState);   // get a guess and process it

        if (gameState->isGameOver) // Check if the game is over due to "EXIT" command
        {
            printf("Exiting the game...\n");
            endGameHighScore(gameState, highscore); // End the game and handle high scores
            return; // Exit the loop and function
        }
        if (gameState->lives <= 0) // after 4 lives are finished game is done
        {
            printf("No lives left, Game Over!\n");
            endGameHighScore(gameState, highscore); // End the game and handle high scores
            return; // Exit the loop and function
        }
        if (areAllConnectionsGuessed(gameState->head)) // Check if all connections are guessed
        {
            printf("Congratulations! You've guessed all connections correctly!\n");
            endGameHighScore(gameState, highscore); // End the game and handle high scores
            return; // Exit the loop and function
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
        // prompt the user for a guess - example "red blue green yellow"
        printf("Enter your guess (words separated by spaces): ");
        if (getUserInputGuess(guess, MAXBUFFER)) {
            // Exit command received
            gameState->isGameOver = true; // Set the flag to true
            return; // Exit the function
        }
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


void printGameState(const GAME_STATE* gameState) {
    printf("\nPlayer: %s\n", gameState->player.name);
    printf("Streak: %d\n", gameState->player.score);
    printf("Lives: %d\n\n", gameState->lives);
    traverse(gameState->head);

    // Print the grid using the stored shuffled order
    printf("+------------------+------------------+------------------+------------------+\n");
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        printf("| %-16s ", gameState->shuffledWords[i] ? gameState->shuffledWords[i] : "");
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

bool getUserInputGuess(char* guess, int size)
{
    fgets(guess, size, stdin);
    guess[strcspn(guess, "\n")] = '\0'; // remove newline character

    // Check if the user entered the exit command
    if (strcmp(guess, "EXIT") == 0) {
        return true; // Return true to indicate an exit command
    }
    return false; // No exit command
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

// Updates high scores with the player's score if it's high enough
void updateHighscores(HIGHSCORE* highscore, GAME_STATE* gameState) {
    addScore(highscore, gameState->player.name, gameState->player.score);
}

// Handles the end of the game, updating and saving high scores
void endGameHighScore(GAME_STATE* gameState, HIGHSCORE* highscore) {
    if (areAllConnectionsGuessed(gameState->head)) {
        gameState->player.score++; // Increment score by 1 for each win
        printf("Current streak: %d\n", gameState->player.score);
    }
    else if (gameState->lives <= 0 || gameState->isGameOver) {
        gameState->player.score = 0; // Reset streak on game over
        printf("Streak reset.\n");
    }
    updateHighscores(highscore, gameState); // Update high scores with streak
    printHighscores(*highscore);            // Display high scores
    saveHighscores(*highscore, "highscores.txt"); // Save high scores
}

bool areAllConnectionsGuessed(NODE* head) {
    NODE* currentNode = head;
    int guessedCount = 0;

    while (currentNode != NULL) {
        if (currentNode->c.wasGuessed) {
            guessedCount++;
            if (guessedCount == TOTALCONNECTIONS) {
                printf("All connections have been guessed!\n"); // Debug output
                return true; // All connections (4) are guessed
            }
        }
        currentNode = currentNode->next;
    }

    printf("Not all connections guessed yet.\n"); // Debug output
    return false; // Less than 4 connections guessed
}




void storeShuffledWords(GAME_STATE* gameState) {
    NODE* ptr = gameState->head;
    int count = 0;

    while (ptr != NULL && count < GRID_WIDTH * GRID_HEIGHT) {
        gameState->shuffledWords[count] = ptr->c.words[count % MAXCONNECTIONS];
        count++;
        if (count % GRID_WIDTH == 0) {
            ptr = ptr->next; // Move to the next node after filling a row
        }
    }

    shuffleArray(gameState->shuffledWords, GRID_WIDTH * GRID_HEIGHT);
}