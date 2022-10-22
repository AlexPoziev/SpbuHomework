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

int isSingle(List* list) {
    return list->head == list->head->next;
}

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head == NULL;
    return temp;
}

Position* createPosition(List *list) {
    if (list == NULL) {
        return NULL;
    }
    Position *temp = malloc(sizeof(Position));
    temp->position = list->head;
    return temp;
}

int getNextPosition(Position *position) {
    if (position == NULL) {
        return -1;
    }
    position->position = position->position->next;
    return 0;
}

bool isEmptyNode(Node *node) {
    return node == NULL;
}

void plusOnePosition(Node *next, List *list) {
    Node *temp = next;
    while(temp != list->head->previous) {
        ++(temp->position);
        temp = temp->next;
    }
    ++(list->head->previous->position);
}

Node* findPosition(List *list, int position) {
    if (isEmpty(list) || isEmptyNode(list->head)) {
        return NULL;
    }
    Node *temp = list->head;

    while (temp->position != position) {
        if (temp->next == NULL) {
            return NULL;
        }
        temp = temp->next;
    }

    return temp;
}

int deletePosition(List *list, Position *position, int *errorCode) {
    position->position->previous->next = position->position->next;
    position->position->next->previous = position->position->previous;
    if (position->position == list->head) {
        list->head = position->position->next;
    }

    int temp = position->position->value;
    Node *nextElement = position->position->next;
    free(position->position);
    position->position = nextElement;

    return temp;
}

int insert(List *list, int value, int position) {

    if (list->head == NULL) {
        Node *newNode = malloc(sizeof(Node));
        if (newNode == NULL) {
            return 1;
        }
        newNode->next = newNode;
        newNode->previous = newNode;
        newNode->value = value;
        newNode->position = position;
        list->head = newNode;

        return 0;
    }

    if (position < 0 || position > list->head->previous->position + 1) {
        return -1;
    }

    if (position == list->head->previous->position + 1) {
        Node *newNode = malloc(sizeof(Node));
        if (newNode == NULL) {
            return 1;
        }
        newNode->next = list->head;
        newNode->previous = list->head->previous;
        list->head->previous->next = newNode;
        list->head->previous = newNode;
        newNode->value = value;
        newNode->position = position;

        return 0;
    }

    Node *currentNode = findPosition(list, position);
    if ((currentNode) == NULL) {
        return -1;
    }
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return 1;
    }
    newNode->value = value;
    newNode->position = position;
    currentNode->previous->next = newNode;
    currentNode->next->previous = newNode;
    newNode->previous = currentNode->previous;
    newNode->next = currentNode;
    if (position == 0) {
        list->head = newNode;
    }
    plusOnePosition(newNode->next, list);

    return 0;
}

bool isEmpty(List *list) {
    return list == NULL;
}

void clear(List **list, Position *position) {
    int errorCode = 0;
    position->position = (*list)->head;
    while(!isSingle(*list)) {
        deletePosition(*list, position, &errorCode);
    }
    free(position);
    free(*list);
}
