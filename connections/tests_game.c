#include "tests_game.h"

// Mock data for testing
NODE sampleNode1 = { .c = {.words = {"red", "blue", "green", "yellow"}, .wasGuessed = false }, .next = NULL };
NODE sampleNode2 = { .c = {.words = {"apple", "banana", "cherry", "date"}, .wasGuessed = false }, .next = NULL };

// Test case: REQ_GM_001
void test_initializeGame() {
    GAME_STATE gameState; 
    HIGHSCORE highscore; 
    sampleNode1.next = &sampleNode2;  // Link sampleNode1 to sampleNode2

    initializeGame(&gameState, &sampleNode1, &highscore, "karl");  // Initialize the game state with the sample nodes and highscore

    // Check if the game state is initialized correctly
    if (strcmp(gameState.player.name, "samplePlayer") == 0 &&
        gameState.player.score == 0 &&
        gameState.lives == MAX_LIVES &&
        gameState.isGameOver == false) {
        printf("REQ_GM_001: Game state initializes correctly - PASSED\n");  // Output PASSED if all conditions are met
    }
    else {
        printf("REQ_GM_001: Game state initializes correctly - FAILED\n");  // Output FAILED if any condition is not met
    }
}

// Test case: REQ_GM_002
void test_processCorrectGuess() {
    GAME_STATE gameState;       // Declare a GAME_STATE variable to store the game state
    gameState.head = &sampleNode1;  // Set the head of the linked list to sampleNode1
    gameState.lives = MAX_LIVES;  // Initialize the lives to the maximum allowed

    char* correctGuess[MAX_WORDS_PER_GUESS] = { "red", "blue", "green", "yellow" };  // Define a correct guess
    GUESS_RESULT result = isGuessAConnection(&gameState, correctGuess);  // Check if the guess is a correct connection

    if (result.isConnection == true && result.matchedConnection == &sampleNode1) {
        handleCorrectGuess(&gameState, result);  // Handle the correct guess
        if (gameState.lives == MAX_LIVES && sampleNode1.c.wasGuessed == true) {
            printf("REQ_GM_002: Game processes a correct guess correctly - PASSED\n");  // Output PASSED if conditions are met
        }
        else {
            printf("REQ_GM_002: Game processes a correct guess correctly - FAILED\n");  // Output FAILED if conditions are not met
        }
    }
    else {
        printf("REQ_GM_002: Game processes a correct guess correctly - FAILED\n");  // Output FAILED if the guess is not recognized as correct
    }
}

// Test case: REQ_GM_003
void test_processIncorrectGuess() {
    GAME_STATE gameState;       // Declare a GAME_STATE variable to store the game state
    gameState.head = &sampleNode1;  // Set the head of the linked list to sampleNode1
    gameState.lives = MAX_LIVES;  // Initialize the lives to the maximum allowed

    char* incorrectGuess[MAX_WORDS_PER_GUESS] = { "purple", "orange", "black", "white" };  // Define an incorrect guess
    GUESS_RESULT result = isGuessAConnection(&gameState, incorrectGuess);  // Check if the guess is an incorrect connection

    if (result.isConnection == false) {
        handleIncorrectGuess(&gameState);  // Handle the incorrect guess
        if (gameState.lives == MAX_LIVES - 1) {
            printf("REQ_GM_003: Game processes an incorrect guess correctly - PASSED\n");  // Output PASSED if lives decrement as expected
        }
        else {
            printf("REQ_GM_003: Game processes an incorrect guess correctly - FAILED\n");  // Output FAILED if lives do not decrement correctly
        }
    }
    else {
        printf("REQ_GM_003: Game processes an incorrect guess correctly - FAILED\n");  // Output FAILED if the guess is incorrectly recognized as correct
    }
}

// Test case: REQ_GM_004
void test_splitGuessIntoWords() {
    char guess[MAXBUFFER] = "red blue green yellow";  // Sample input string
    char* splitGuess[MAX_WORDS_PER_GUESS];  // Array to store the split words
    int wordCount = splitGuessIntoWords(guess, splitGuess, MAX_WORDS_PER_GUESS);  // Split the input string into words

    // Check if the words were split correctly
    if (wordCount == 4 &&
        strcmp(splitGuess[0], "red") == 0 &&
        strcmp(splitGuess[1], "blue") == 0 &&
        strcmp(splitGuess[2], "green") == 0 &&
        strcmp(splitGuess[3], "yellow") == 0) {
        printf("REQ_GM_004: User input handling and splitting into words - PASSED\n");  // Output PASSED if all words are correct
    }
    else {
        printf("REQ_GM_004: User input handling and splitting into words - FAILED\n");  // Output FAILED if any word is incorrect
    }
}

// Test case: REQ_GM_005
void test_capitalizeString() {
    char testString[MAXBUFFER] = "red blue green yellow";  // Sample input string
    capitalizeString(testString);  // Capitalize the string

    if (strcmp(testString, "RED BLUE GREEN YELLOW") == 0) {
        printf("REQ_GM_005: String capitalization function - PASSED\n");  // Output PASSED if capitalization is correct
    }
    else {
        printf("REQ_GM_005: String capitalization function - FAILED\n");  // Output FAILED if capitalization is incorrect
    }
}

// Test case: REQ_GM_006
void test_isGuessAConnection() {
    GAME_STATE gameState;       // Declare a GAME_STATE variable to store the game state
    gameState.head = &sampleNode1;  // Set the head of the linked list to sampleNode1

    char* correctGuess[MAX_WORDS_PER_GUESS] = { "red", "blue", "green", "yellow" };  // Define a correct guess
    GUESS_RESULT correctResult = isGuessAConnection(&gameState, correctGuess);  // Check if the guess is correct

    char* incorrectGuess[MAX_WORDS_PER_GUESS] = { "purple", "orange", "pink", "white" };  // Define an incorrect guess
    GUESS_RESULT incorrectResult = isGuessAConnection(&gameState, incorrectGuess);  // Check if the guess is incorrect

    if (correctResult.isConnection == true && incorrectResult.isConnection == false) {
        printf("REQ_GM_006: Guess validation against connections - PASSED\n");  // Output PASSED if correct guess recognized and incorrect guess not recognized
    }
    else {
        printf("REQ_GM_006: Guess validation against connections - FAILED\n");  // Output FAILED if any condition is not met
    }
}

// Main function to run all tests
int runAllGameTests() {
    test_initializeGame();
    test_processCorrectGuess();  
    test_processIncorrectGuess();  
    test_splitGuessIntoWords();  
    test_capitalizeString();     
    test_isGuessAConnection();
    return 0;  // Return success code
}
