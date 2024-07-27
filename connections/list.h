#pragma once

// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// linked list signatures

#include "connection.h"
#include <stdio.h>
#include <stdlib.h>

// struct for linked list node
typedef struct node {
	CONNECTION c;
	struct node* next;
} NODE;

// create linked list
void createList(NODE*, CONNECTION* connectArr[TOTALCONNECTIONS]);

// print and traverse connection of each node
void traverse(NODE*);

// traverse and free each node
void deleteNode(NODE* ptr);

// manual test function for list module
bool createListTest(void);