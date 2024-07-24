#pragma once

#include "game.h"


void initializeGame(GAME_STATE* gameState, NODE* head)
{
    gameState->head = head; // set the connections
    strcpy(gameState->player.name, "samplePlayer");	// set the name
    gameState->player.score = 0;	// set the score
    gameState->lives = MAX_LIVES; // set the lives

    NODE* currentNode = head;
    while (currentNode != NULL) {
        currentNode->c.wasGuessed = false; // Ensure wasGuessed is set to false initially
        currentNode = currentNode->next;
    }
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


        // Loop for making sure at least 4 words are entered
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
            if (guessResult.matchedConnection->c.wasGuessed)
            {
                // Print in green if already guessed
                printf("\033[32mCorrect Guess!\n");
                printf("Connection already guessed: %s\033[0m\n", guessResult.matchedConnection->c.name);
            }
            else
            {
                // Normal color if not guessed before
                printf("Correct Guess!\n");
                printf("Connection made: %s\n", guessResult.matchedConnection->c.name);
                guessResult.matchedConnection->c.wasGuessed = true; // Mark as guessed
            }
        }
        else
        {
            printf("\033[31mIncorrect Guess!\n\033[0m");
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


//void printGameState(const GAME_STATE* gameState) {
//    printf("\nPlayer: %s\n", gameState->player.name);
//    printf("Score: %d\n", gameState->player.score);
//    printf("Lives: %d\n\n", gameState->lives);
//
//    // Create an array to store the words
//    char* words[4 * 4];
//    int count = 0;
//
//    NODE* ptr = gameState->head;
//    while (ptr != NULL && count < 4 * 4) {
//        words[count] = ptr->c.words[count % MAXCONNECTIONS];
//        count++;
//        if (count % 4 == 0) {
//            ptr = ptr->next; // Move to the next node after filling a row
//        }
//    }
//
//    // Shuffle the words
//    shuffleArray(words, 4 * 4);
//
//    // Print the grid
//    printf("+------------------+------------------+------------------+------------------+\n");
//    for (int i = 0; i < 4 * 4; i++) {
//        printf("| %-16s ", words[i] ? words[i] : ""); // Print word or empty space
//        if ((i + 1) % 4 == 0) {
//            printf("|\n");
//            printf("+------------------+------------------+------------------+------------------+\n");
//        }
//    }
//}

void shuffleArray(char* array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
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
            if (!currentNode->c.wasGuessed) {
                currentNode->c.wasGuessed = true; // Mark the connection as guessed only if it hasn't been guessed before
            }
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



// writing this so i dont forget later
// iterate through the linked list
// check the bool flag of each connection,
// if all are made, make a new game