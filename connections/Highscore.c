// highscore.c

#include "highscore.h"
#include <stdio.h>
#include <string.h>

// Initializes the high scores list by setting the number of scores to 0
void initializeHighscores(HIGHSCORE* s) {
    s->numscores = 0;
    for (int i = 0; i < MAX_SCORES; i++) {
        strcpy(s->scores[i].name, "");
        s->scores[i].score = 0;
    }
}

// Sort the high scores
void sortHighscores(HIGHSCORE* highscore) {
    for (int i = 0; i < highscore->numscores - 1; i++) {
        for (int j = 0; j < highscore->numscores - i - 1; j++) {
            if (highscore->scores[j].score < highscore->scores[j + 1].score) {
                // Swap the scores
                PLAYER temp = highscore->scores[j];
                highscore->scores[j] = highscore->scores[j + 1];
                highscore->scores[j + 1] = temp;
            }
        }
    }
}

// Adds a new score to the high scores list
void addScore(HIGHSCORE* highscore, const char* playerName, int score) {
    // Check if the player already has a score recorded
    for (int i = 0; i < highscore->numscores; i++) {
        if (strcmp(highscore->scores[i].name, playerName) == 0) {
            // If the player already exists, update their score if the new score is higher
            if (score > highscore->scores[i].score) {
                highscore->scores[i].score = score;
                sortHighscores(highscore); // Sort after updating score
            }
            return;
        }
    }

    // If the player does not exist in the high scores
    if (highscore->numscores < MAX_SCORES) {
        // There's space in the high score list, add the new score
        strncpy(highscore->scores[highscore->numscores].name, playerName, MAX_NAME_LENGTH);
        highscore->scores[highscore->numscores].score = score;
        highscore->numscores++;
        sortHighscores(highscore); // Sort after adding a new score
    }
    else {
        // Find the lowest score in the list
        int minIndex = 0;
        for (int i = 1; i < highscore->numscores; i++) {
            if (highscore->scores[i].score < highscore->scores[minIndex].score) {
                minIndex = i;
            }
        }

        // Replace the lowest score if the new score is higher
        if (score > highscore->scores[minIndex].score) {
            strncpy(highscore->scores[minIndex].name, playerName, MAX_NAME_LENGTH);
            highscore->scores[minIndex].score = score;
            sortHighscores(highscore); // Sort after replacing the score
        }
    }
}


// Prints the high scores list
void printHighscores(HIGHSCORE s) {
    printf("Highscores:\n");
    for (int i = 0; i < s.numscores; i++) {
        printf("%d. %s - %d\n", i + 1, s.scores[i].name, s.scores[i].score);
    }
}

// Saves the high scores to a text file
void saveHighscores(HIGHSCORE s, const char* filename) {
    FILE* file = fopen(filename, "w");  // Open in text write mode
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < s.numscores; i++) {
        fprintf(file, "%s %d\n", s.scores[i].name, s.scores[i].score);
    }
    fclose(file);
}

// Loads the high scores from a text file
void loadHighscores(HIGHSCORE* s, const char* filename) {
    FILE* file = fopen(filename, "r");  // Open in text read mode
    if (file == NULL) {
        printf("Error opening file for reading. Starting with empty high scores.\n");
        initializeHighscores(s); // Initialize with empty scores if file cannot be read
        return;
    }
    s->numscores = 0;
    while (fscanf(file, "%s %d", s->scores[s->numscores].name, &s->scores[s->numscores].score) == 2) {
        s->numscores++;
        if (s->numscores >= MAX_SCORES) {
            break;
        }
    }
    fclose(file);
}