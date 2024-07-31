// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#pragma once

#include "file.h"
#include "connection.h"
#include "list.h"
#include "game.h"
#include "Highscore.h"
#include "menu.h"

// Run all functions
void runTests(void);

void runAllConnectionTests();
void runAllFileTests();
void runAllGameTests();
void runAllHighscoreTests();
void runAllListTests();

// CONNECTION MODULE - PAUL
// manual test function for connection module
// Test case: REQ_CON_001
bool createConnectionTest(void);

// FILE MODULE - PAUL
// manual test functions for file module
bool countLinesTest(void); // Test case: REQ_IO_001
bool getRandomLineTest(void); // Test case: REQ_IO_002
bool loadDataTest(void); // Test case: REQ_IO_003

// LIST MODULE - PAUL
// manual test function for list module
bool createListTest(void); // Test case: REQ_LIST_001


// GAME MODULE - KARL
void test_initializeGame(); // Test case: REQ_GM_001
void test_processCorrectGuess(); // Test case: REQ_GM_002
void test_processIncorrectGuess(); // Test case: REQ_GM_003
void test_splitGuessIntoWords(); // Test case: REQ_GM_004
void test_capitalizeString(); // Test case: REQ_GM_005
void test_isGuessAConnection(); // Test case: REQ_GM_006

// HIGHSCORE MODULE - ALLI
void test_save_and_load_highscore(); // Test case: REQ_HSM_001
void test_verify_highscore_display(); // Test case: REQ_HSM_002
 



