#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#define MAXWORD			50
#define MAXCONNECTIONS	4

typedef struct connection {
	char words[MAXCONNECTIONS][MAXWORD];
} CONNECTION;