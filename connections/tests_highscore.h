#pragma once

#include "Highscore.h"

#define MAX_SCORES 5    // Define the maximum number of high scores

// Test case: REQ_HSM_001
void test_save_and_load_highscore();

// Test case: REQ_HSM_002
void test_verify_highscore_display();

// Test case: REQ_HSM_003
void test_replace_highscore();

// function to run all test cases
void runAllHighscoreTests();
