#pragma once
#include <assert.h>      
#include <string.h>       
#include <stdio.h>        
#include "game.h"        

// Mock data for testing
NODE sampleNode1 = { .c = {.words = {"red", "blue", "green", "yellow"}, .wasGuessed = false }, .next = NULL };
NODE sampleNode2 = { .c = {.words = {"apple", "banana", "cherry", "date"}, .wasGuessed = false }, .next = NULL };

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

