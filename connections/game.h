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


// Initialization Functions
void initializeGame(GAME_STATE* gameState, NODE* head, HIGHSCORE* highscore);
void initializeConnections(NODE* head);

// Game Loop Management
void startGame(GAME_STATE* gameState, HIGHSCORE* highscore);
void processGuess(GAME_STATE* gameState);

// Input Handling
void getUserInputGuess(char* guess, int size);
int splitGuessIntoWords(char* guess, char* splitGuess[], int max_words_per_guess);
void resetGuessBuffers(char guess[], char* splitGuess[], int guessSize, int splitGuessSize);

// Game Logic
GUESS_RESULT isGuessAConnection(GAME_STATE* gameState, char* splitGuess[]);
void handleCorrectGuess(GAME_STATE* gameState, GUESS_RESULT guessResult);
void handleIncorrectGuess(GAME_STATE* gameState);

// Display and Feedback
void printGameState(const GAME_STATE* gameState);
void printGuessFeedback(const GUESS_RESULT guessResult, bool isAlreadyGuessed);

// Utility Functions
void capitalizeString(char* str);


void shuffleArray(char* array[], int size);


void updateHighscores(HIGHSCORE* highscore, GAME_STATE* gameState);
void endGame(GAME_STATE* gameState, HIGHSCORE* highscore);

bool areAllConnectionsGuessed(NODE* head);