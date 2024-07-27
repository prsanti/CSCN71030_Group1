#include "tests_highscore.h"

#pragma once

#include "Highscore.h"

#define MAX_SCORES 5    // Define the maximum number of high scores

// Test function for saving and loading high scores (REQ_HSM_001)
void test_save_and_load_highscore() {
    HIGHSCORE scores;           // Declare a high score structure
    initializeHighscores(&scores);  // Initialize the high score list

    // Add test scores to the high score list
    addScore(&scores, "Alice", 150);
    addScore(&scores, "Bob", 200);
    addScore(&scores, "Charlie", 100);

    // Save the high scores to a file
    saveHighscores(scores, "test_scores.txt");

    // Load the high scores from the file into a new high score structure
    HIGHSCORE loadedScores;
    initializeHighscores(&loadedScores);  // Initialize the new high score list
    loadHighscores(&loadedScores, "test_scores.txt");  // Load scores from the file

    // Assert that the number of loaded scores is correct
    assert(loadedScores.numscores == 3);
    // Assert that the loaded scores and names match the expected values
    assert(strcmp(loadedScores.scores[0].name, "Bob") == 0 && loadedScores.scores[0].score == 200);
    assert(strcmp(loadedScores.scores[1].name, "Alice") == 0 && loadedScores.scores[1].score == 150);
    assert(strcmp(loadedScores.scores[2].name, "Charlie") == 0 && loadedScores.scores[2].score == 100);

    // Print success message for this test case
    printf("Test REQ_HSM_001 passed.\n");
}

// Test function for verifying the display of high scores (REQ_HSM_002)
void test_verify_highscore_display() {
    HIGHSCORE scores;           // Declare a high score structure
    initializeHighscores(&scores);  // Initialize the high score list

    // Add test scores to the high score list
    addScore(&scores, "Alice", 150);
    addScore(&scores, "Bob", 200);
    addScore(&scores, "Charlie", 100);

    // Define the expected output as a hardcoded string
    char expectedOutput[] = "Highscores:\n1. Bob - 200\n2. Alice - 150\n3. Charlie - 100\n";

    // Redirect stdout to a file to capture the output
    freopen("output.txt", "w", stdout);
    printHighscores(scores);  // Print the high scores
    freopen("/dev/tty", "a", stdout);  // Restore stdout to terminal

    // Open the output file to read the captured output
    FILE* file = fopen("output.txt", "r");
    char output[256];  // Buffer to store the read output
    fread(output, sizeof(char), 256, file);  // Read the file content into the buffer
    fclose(file);  // Close the file

    // Assert that the captured output matches the expected output
    assert(strcmp(output, expectedOutput) == 0);

    // Print success message for this test case
    printf("Test REQ_HSM_002 passed.\n");
}

// Test function for replacing a low score with a new high score (REQ_HSM_003)
void test_replace_highscore() {
    HIGHSCORE scores;           // Declare a high score structure
    initializeHighscores(&scores);  // Initialize the high score list

    // Fill the high score list with initial scores
    addScore(&scores, "Alice", 150);
    addScore(&scores, "Bob", 200);
    addScore(&scores, "Charlie", 100);
    addScore(&scores, "David", 180);
    addScore(&scores, "Eve", 120);

    // Add a new high score that should replace a lower score
    addScore(&scores, "Frank", 190);

    // Assert that the number of scores is at the maximum
    assert(scores.numscores == MAX_SCORES);
    // Assert that the lowest score was replaced (Charlie should not be in the list)
    assert(strcmp(scores.scores[MAX_SCORES - 1].name, "Charlie") != 0);
    // Assert that the new score by "Frank" is in the list
    assert(strcmp(scores.scores[MAX_SCORES - 1].name, "Frank") == 0);
    assert(scores.scores[MAX_SCORES - 1].score == 190);

    // Print success message for this test case
    printf("Test REQ_HSM_003 passed.\n");
}

// Main function to run all test cases
int main() {
    test_save_and_load_highscore();   // Run test for saving and loading high scores
    test_verify_highscore_display();  // Run test for verifying high score display
    test_replace_highscore();         // Run test for replacing low scores with high scores
    return 0;  // Return 0 to indicate successful execution
}
