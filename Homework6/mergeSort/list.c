#include "list.h"
#include <stdlib.h>

typedef struct Contact {
    char* name;
    char* phoneNumber;
} Contact;

typedef struct Node {
    Contact *contact;
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

void getFromFile(FILE* file, char* fileName, List* list) {
    file = fopen(fileName, "r");
    while (!feof(file)) {
        Contact *contact = malloc(sizeof(Contact));


    }
}

void getFirstPosition(List *list, Position *position) {
    position->position = list->head;
}

Node* lastPosition(List *list) {
    Node *temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

int insert(List *list, Position *position) {
    if (list == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        list->head = position->position;
        list->head->next = NULL;

        return 0;
    }

    Node *lastElement = lastPosition(list);
    lastElement->next = position->position;
    lastElement->next->next = NULL;

    return 0;
}

void getNextPosition(Position *position) {
    if (position->position == NULL) {
        return;
    }

    position->position = position->position->next;
}

char* getPositionValue(List *list, Position *position, Priority priority, int *errorCode) {
    if (position == NULL) {
        *errorCode = -1;
        return NULL;
    }

    return priority == phoneNumber
    ? position->position->contact->phoneNumber
    : position->position->contact->name;
}

void getMiddlePosition(List *list, Position *position) {
    if (list->head != NULL) {
        Node *smallStep = list->head;
        Node *largeStep = list->head;
        while (largeStep != NULL && largeStep->next != NULL) {
            largeStep = largeStep->next->next;
            smallStep = smallStep->next;
        }
        position->position = smallStep;
    }
}

bool isEnd(Position *position) {
    if (position == NULL) {
        return true;
    }

    return position->position->next == NULL;
}

void printList (List *list) {
    if (list == NULL) {
        return;
    }

    Node *temp = list->head;
    while (temp != NULL) {
        printf("%s %s \n", temp->contact->name, temp->contact->phoneNumber);
        temp = temp->next;
    }
}

void addNext(Position *currentPosition, Position *newPosition) {
    currentPosition->position->next = newPosition->position;
}

void deleteList(List **list) {
    if (*list == NULL) {
        free(*list);
        return;
    }
    Node *temp = (*list)->head;
    while (temp != NULL) {
        (*list)->head = (*list)->head->next;
        if (temp->contact != NULL) {
            free(temp->contact->phoneNumber);
            free(temp->contact->name);
            free(temp->contact);
        }
        temp = (*list)->head;
    }
    free(*list);
    *list = NULL;
}

void deletePosition(Position **position) {
    free(*position);
    *position = NULL;
}