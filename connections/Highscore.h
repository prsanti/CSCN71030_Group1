#pragma once
#include "connection.h"//for maxword

#define MAX_SCORES 5

// players struct has a category name and score
typedef struct players{
    char name[MAXWORD];
    int score;
} PLAYER;
// highscore struct has a category name and score
typedef struct highscore {
    PLAYER scores[MAX_SCORES];
    int numscores;
} HIGHSCORE;

void initializeHighscores(HIGHSCORE* s);
void addScore(HIGHSCORE* s, char* playerName, int score);
void printHighscores(HIGHSCORE s); 
void saveHighscores(HIGHSCORE s, const char* filename);
void loadHighscores(HIGHSCORE* s, const char* filename);
