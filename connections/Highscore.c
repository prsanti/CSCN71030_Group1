// highscore.c

#include "highscore.h"
#include <stdio.h>
#include <string.h>

void initializeHighscores(HIGHSCORE* s) {
    s->numscores = 0;
    for (int i = 0; i < MAX_SCORES; i++) {
        strcpy(s->scores[i].name, "");
        s->scores[i].score = 0;
    }
}

void addScore(HIGHSCORE* s, char* playerName, int score) {
    if (s->numscores < MAX_SCORES) {
        strcpy(s->scores[s->numscores].name, playerName);
        s->scores[s->numscores].score = score;
        s->numscores++;
    }
    else {
        // Replace the lowest score if the list is full and this score is higher
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

void printHighscores(HIGHSCORE s) {
    printf("Highscores:\n");
    for (int i = 0; i < s.numscores; i++) {
        printf("%d. %s - %d\n", i + 1, s.scores[i].name, s.scores[i].score);
    }
}
