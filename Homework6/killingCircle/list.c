#include "list.h"
#include <stdio.h>

typedef struct Node {
    int value;
    int position;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct Position {
    Node *position;
} Position;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head == NULL;
    return temp;
}

Position* createPosition() {
    return malloc(sizeof(Position));
}

int getNextPosition(Position *position) {
    if (position == NULL) {
        return -1;
    }
    position->position = position->position->next;
    return 0;
}

int insert(List *list, int value, int position) {
    if (list == NULL) {
        Node *newNode = malloc(sizeof(Node));
        newNode->next = newNode;
        newNode->previous = newNode;
        newNode->value = value;
        newNode->position = position;
        list->head = newNode;
    }
}