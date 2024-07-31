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

// Adds a new score to the high scores list

void addScore(HIGHSCORE* s, char* playerName, int score) {
    if (s->numscores < MAX_SCORES) {
        strcpy(s->scores[s->numscores].name, playerName);
        s->scores[s->numscores].score = score;
        s->numscores++;
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