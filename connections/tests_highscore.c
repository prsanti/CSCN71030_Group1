#include "tests_highscore.h"
#include "highscore.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_SCORES 5    // Define the maximum number of high scores

// Test function for saving and loading high scores (REQ_HSM_001)
void test_save_and_load_highscore() {
    HIGHSCORE scores;
    initializeHighscores(&scores);

    addScore(&scores, "Alice", 150);
    addScore(&scores, "Bob", 200);
    addScore(&scores, "Charlie", 100);

    saveHighscores(scores, "test_scores.txt");

    HIGHSCORE loadedScores;
    initializeHighscores(&loadedScores);
    loadHighscores(&loadedScores, "test_scores.txt");

    if (loadedScores.numscores == 3 &&
        strcmp(loadedScores.scores[0].name, "Bob") == 0 && loadedScores.scores[0].score == 200 &&
        strcmp(loadedScores.scores[1].name, "Alice") == 0 && loadedScores.scores[1].score == 150 &&
        strcmp(loadedScores.scores[2].name, "Charlie") == 0 && loadedScores.scores[2].score == 100) {
        printf("Test REQ_HSM_001: Pass\n");
    }
    else {
        printf("Test REQ_HSM_001: Fail\n");
    }
}

// Test function for verifying the display of high scores (REQ_HSM_002)
void test_verify_highscore_display() {
    HIGHSCORE scores;
    initializeHighscores(&scores);

    addScore(&scores, "Alice", 150);
    addScore(&scores, "Bob", 200);
    addScore(&scores, "Charlie", 100);

    char expectedOutput[] = "Highscores:\n1. Bob - 200\n2. Alice - 150\n3. Charlie - 100\n";

    freopen("output.txt", "w", stdout);
    printHighscores(scores);
    freopen("/dev/tty", "a", stdout);

    FILE* file = fopen("output.txt", "r");
    char output[256];
    fread(output, sizeof(char), 256, file);
    fclose(file);

    if (strcmp(output, expectedOutput) == 0) {
        printf("Test REQ_HSM_002: Pass\n");
    }
    else {
        printf("Test REQ_HSM_002: Fail\n");
    }
}

// Test function for replacing a low score with a new high score (REQ_HSM_003)
void test_replace_highscore() {
    HIGHSCORE scores;
    initializeHighscores(&scores);

    addScore(&scores, "Alice", 150);
    addScore(&scores, "Bob", 200);
    addScore(&scores, "Charlie", 100);
    addScore(&scores, "David", 180);
    addScore(&scores, "Eve", 120);

    addScore(&scores, "Frank", 190);

    if (scores.numscores == MAX_SCORES &&
        strcmp(scores.scores[MAX_SCORES - 1].name, "Charlie") != 0 &&
        strcmp(scores.scores[MAX_SCORES - 1].name, "Frank") == 0 &&
        scores.scores[MAX_SCORES - 1].score == 190) {
        printf("Test REQ_HSM_003: Pass\n");
    }
    else {
        printf("Test REQ_HSM_003: Fail\n");
    }
}

// Main function to run all test cases
void runAllHighscoreTests() {
    test_save_and_load_highscore();
    test_verify_highscore_display();
    test_replace_highscore();
}
