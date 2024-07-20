// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

// linked list functions
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "connection.h"

void createList(NODE* ptr, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
    // Loop through total connections
    for (int i = 0; i < TOTALCONNECTIONS; i++) {
        // Set pointer to connection of array
        ptr->c = *connectionArr[i];

        // Allocate memory for next node if not the last node
        if (i < TOTALCONNECTIONS - 1) {
            ptr->next = (NODE*)malloc(sizeof(NODE));
            if (ptr->next == NULL) {
                fprintf(stderr, "Error allocating memory\n");
                break;
            }
            ptr = ptr->next; // Move to the next node
        }
        else {
            ptr->next = NULL; // Last node should point to NULL
        }
    }
}


/*void createList(NODE* ptr, CONNECTION* connectionArr[TOTALCONNECTIONS]) {
    for (int i = 0; i < TOTALCONNECTIONS; i++) {
        ptr->c = *connectionArr[i];

        // Allocate memory for the next node
        ptr->next = (NODE*)malloc(sizeof(NODE));

        if (ptr->next == NULL) {
            printf("Error allocating memory\n");
            break;
        }

        ptr = ptr->next;
    }

    // Set the last pointer's next to NULL
    ptr->next = NULL;
}*/

void traverse(NODE* ptr) {
    while (ptr != NULL) {
        printConnection(ptr->c);
        ptr = ptr->next;
    }
}

void deleteNode(NODE* ptr) {
    while (ptr != NULL) {
        NODE* temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}
