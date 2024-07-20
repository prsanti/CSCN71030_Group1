#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// game.h
// Group 1 - Paul, Iggy, Karl, Alli


#define _CRT_SECURE_NO_WARNINGS

#define MAX_LIVES 4
#define MIN_LIVES 0
#define MAX_WORDS_PER_GUESS 4
#define WORDS_IN_ONE_CONNECTION 4

#include <ctype.h>
#include "connection.h"
#include "list.h"
#include "Highscore.h"
#include "file.h"


typedef struct game_state {
    NODE* head;     // connection data
    PLAYER player;  // player data
    int lives;      // lives
} GAME_STATE;


typedef struct guess_result {
    bool isConnection;
    NODE* matchedConnection;
} GUESS_RESULT;


void initializeGame(GAME_STATE* gameState, NODE* head);

void startGame(GAME_STATE* gameState);

void printGameState(const GAME_STATE* gameState);


int validateGuess(GAME_STATE* gameState, const char* guess);
int splitGuessIntoWords(char* guess, char* words[], int max_words_per_guess);



GUESS_RESULT isGuessAConnection(GAME_STATE* gameState, char* splitGuess[]);







// helper functions
void getUserInputGuess(char* guess, int size);
void resetGuessBuffers(char guess[], char* splitGuess[], int guessSize, int splitGuessSize);

// Function to capitalize a string
void capitalizeString(char* str);





// help with testing functions;

// These functions are just for helping me test
void printWordsAfterSplit(char* splitGuess[], int word_count);
