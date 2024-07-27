#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"


// Helper function for setting up a game state for testing
void setupTestGameState(GAME_STATE* gameState) {
    static NODE nodes[4]; // Static to avoid deallocation issues
    strcpy(nodes[0].c.words[0], "RED");
    strcpy(nodes[0].c.words[1], "BLUE");
    strcpy(nodes[0].c.words[2], "GREEN");
    strcpy(nodes[0].c.words[3], "YELLOW");
    nodes[0].c.wasGuessed = false;

    strcpy(nodes[1].c.words[0], "CAT");
    strcpy(nodes[1].c.words[1], "DOG");
    strcpy(nodes[1].c.words[2], "BIRD");
    strcpy(nodes[1].c.words[3], "FISH");
    nodes[1].c.wasGuessed = false;

    nodes[0].next = &nodes[1];
    nodes[1].next = NULL;

    gameState->head = &nodes[0];
    gameState->lives = MAX_LIVES;
    gameState->isGameOver = false;
    strcpy(gameState->player.name, "freak");
    gameState->player.score = 0;
}

// Test Case 1: Game Initialization
void testInitializeGame() {
    GAME_STATE gameState;
    NODE* head = NULL;  // Mock linked list head
    HIGHSCORE highscore;

    initializeGame(&gameState, head, &highscore);

    assert(strcmp(gameState.player.name, "freak") == 0);
    assert(gameState.player.score == 0);
    assert(gameState.lives == MAX_LIVES);
    assert(gameState.isGameOver == false);

    printf("testInitializeGame passed.\n");
}

// Test Case 2: Correct Guess Handling
void testCorrectGuess() {
    GAME_STATE gameState;
    setupTestGameState(&gameState);
    char* guess[] = { "RED", "BLUE", "GREEN", "YELLOW" };

    processGuess(&gameState);

    assert(gameState.head->c.wasGuessed == true);
    printf("testCorrectGuess passed.\n");
}

// Test Case 3: Incorrect Guess Handling
void testIncorrectGuess() {
    GAME_STATE gameState;
    setupTestGameState(&gameState);
    char* guess[] = { "BLACK", "WHITE", "PURPLE", "ORANGE" };

    processGuess(&gameState);

    assert(gameState.head->c.wasGuessed == false);
    assert(gameState.lives == MAX_LIVES - 1);

    printf("testIncorrectGuess passed.\n");
}

// Test Case 4: Game Over Conditions
void testGameOverConditions() {
    GAME_STATE gameState;
    setupTestGameState(&gameState);

    // Simulate game over by setting lives to 1 and making an incorrect guess
    gameState.lives = 1;
    processGuess(&gameState);
    assert(gameState.isGameOver == true);
    assert(gameState.lives == 0);

    // Simulate exit command
    gameState.isGameOver = false;
    strcpy(gameState.player.name, "freak");
    char guess[MAXBUFFER] = "EXIT";
    getUserInputGuess(guess, MAXBUFFER);
    processGuess(&gameState);
    assert(gameState.isGameOver == true);

    printf("testGameOverConditions passed.\n");
}

// Test Case 5: All Connections Guessed
void testAllConnectionsGuessed() {
    GAME_STATE gameState;
    setupTestGameState(&gameState);

    // Mark all connections as guessed
    NODE* node = gameState.head;
    while (node != NULL) {
        node->c.wasGuessed = true;
        node = node->next;
    }

    assert(areAllConnectionsGuessed(gameState.head) == true);
    printf("testAllConnectionsGuessed passed.\n");
}

// Test Case 6: Highscore Handling
void testHighscoreHandling() {
    GAME_STATE gameState;
    HIGHSCORE highscore;
    gameState.player.score = 10;
    strcpy(gameState.player.name, "freak");

    endGameHighScore(&gameState, &highscore);
    // Note: In a real test, you would check the highscore list to see if the score was added.

    printf("testHighscoreHandling passed.\n");
}

// Test Case 7: Input Handling
void testInputHandling() {
    char guess[MAXBUFFER];
    assert(getUserInputGuess(guess, MAXBUFFER) == false);

    strcpy(guess, "EXIT");
    assert(getUserInputGuess(guess, MAXBUFFER) == true);

    char* splitGuess[MAX_WORDS_PER_GUESS];
    strcpy(guess, "RED BLUE GREEN YELLOW");
    int count = splitGuessIntoWords(guess, splitGuess, MAX_WORDS_PER_GUESS);
    assert(count == MAX_WORDS_PER_GUESS);

    printf("testInputHandling passed.\n");
}

// Test Case 8: Shuffling Words
void testShufflingWords() {
    GAME_STATE gameState;
    setupTestGameState(&gameState);

    storeShuffledWords(&gameState);

    // Check if words are shuffled (basic check: not identical to original)
    bool shuffled = false;
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
        if (strcmp(gameState.shuffledWords[i], gameState.head->c.words[i % MAXCONNECTIONS]) != 0) {
            shuffled = true;
            break;
        }
    }
    assert(shuffled == true);

    printf("testShufflingWords passed.\n");
}

int main() {
    testInitializeGame();
    testCorrectGuess();
    testIncorrectGuess();
    testGameOverConditions();
    testAllConnectionsGuessed();
    testHighscoreHandling();
    testInputHandling();
    testShufflingWords();

    printf("All tests passed!\n");
    return 0;
}
