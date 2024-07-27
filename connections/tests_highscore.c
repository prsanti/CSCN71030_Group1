#include "tests_highscore.h"
#include "highscore.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define TEST_HIGHSCORE_FILENAME "highscore_test.txt"

// Test function for saving and loading high scores (REQ_HSM_001)
void test_save_and_load_highscore() {
    HIGHSCORE scores;
    initializeHighscores(&scores);

    addScore(&scores, "Alice", 1);
    addScore(&scores, "Bob", 2);
    addScore(&scores, "Charlie", 3);

    saveHighscores(scores, TEST_HIGHSCORE_FILENAME);

    HIGHSCORE loadedScores;
    initializeHighscores(&loadedScores);
    loadHighscores(&loadedScores, TEST_HIGHSCORE_FILENAME);

    if (loadedScores.numscores == 3 &&
        strcmp(loadedScores.scores[0].name, "Alice") == 0 && loadedScores.scores[0].score == 1 &&
        strcmp(loadedScores.scores[1].name, "Bob") == 0 && loadedScores.scores[1].score == 2 &&
        strcmp(loadedScores.scores[2].name, "Charlie") == 0 && loadedScores.scores[2].score == 3) {
        printf("Test REQ_HSM_001: Pass\n");
    }
    else {
        printf("Test REQ_HSM_001: Fail\n");
        printf("Expected: 3 scores, (Alice, 1), (Bob, 2), (Charlie, 3)\n");
        printf("Actual: %d scores, (%s, %d), (%s, %d), (%s, %d)\n",
            loadedScores.numscores,
            loadedScores.scores[0].name, loadedScores.scores[0].score,
            loadedScores.scores[1].name, loadedScores.scores[1].score,
            loadedScores.scores[2].name, loadedScores.scores[2].score);
    }
}

// Test function for verifying the display of high scores (REQ_HSM_002)
void test_verify_highscore_display() {
    HIGHSCORE scores;
    initializeHighscores(&scores);

    // Add some test scores
    addScore(&scores, "Alice", 1);
    addScore(&scores, "Bob", 2);
    addScore(&scores, "Charlie", 3);

    // Expected output format for manual verification
    printf("Expected Output:\n");
    printf("Alice - 1\n");
    printf("Bob - 2\n");
    printf("Charlie - 3\n");

    // Call the function to display high scores
    printf("Actual Output:\n");
    printHighscores(scores);
}


// Main function to run all test cases
void runAllHighscoreTests() {
    test_save_and_load_highscore();
    test_verify_highscore_display();
}

