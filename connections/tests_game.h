#pragma once
#include <assert.h>      
#include <string.h>       
#include <stdio.h>        
#include "game.h"        

// Test case: REQ_GM_001
void test_initializeGame();

// Test case: REQ_GM_002
void test_processCorrectGuess();

// Test case: REQ_GM_003
void test_processIncorrectGuess();

// Test case: REQ_GM_004
void test_splitGuessIntoWords();

// Test case: REQ_GM_005
void test_capitalizeString();

// Test case: REQ_GM_006
void test_isGuessAConnection();

//  function to run all tests
int runAllGameTests();

