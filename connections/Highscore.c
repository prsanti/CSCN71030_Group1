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
    else {
        // If the list is full, it replaces the lowest score if the new score is higher
       
        int lowestScoreIndex = 0;
        for (int i = 1; i < MAX_SCORES; i++) {
            if (s->scores[i].score < s->scores[lowestScoreIndex].score) {
                lowestScoreIndex = i;
            }
        }
        if (score > s->scores[lowestScoreIndex].score) {
            strcpy(s->scores[lowestScoreIndex].name, playerName);
            s->scores[lowestScoreIndex].score = score;
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

// Saving  the high scores to a file
void saveHighscores(HIGHSCORE s, const char filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&s, sizeof(HIGHSCORE), 1, file);
    fclose(file);
}

// Loading high score
void loadHighscores(HIGHSCORE* s, const char filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fread(s, sizeof(HIGHSCORE), 1, file);
    fclose(file);
}