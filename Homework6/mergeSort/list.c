#include "list.h"
#include <stdlib.h>

typedef struct Contact {
    char* name;
    char* phoneNumber;
} Contact;

typedef struct Node {
    Contact contact;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct Position {
    Node *position
} Position;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head = NULL;

    return temp;
}

Position* createPosition(void) {
    Position *temp = malloc(sizeof(Position));
    temp->position = NULL;

    return temp;
}

