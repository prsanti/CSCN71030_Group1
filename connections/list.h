#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// linked list signatures

#include "connection.h"

typedef struct node {
	CONNECTION c;
	struct node* next;
} NODE;

void addToList(NODE*, CONNECTION connectArr[MAXCONNECTIONS]);

// print and traverse connection of each node
void traverse(NODE*);