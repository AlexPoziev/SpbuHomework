#include "sortedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct List {
    Node *head;
} List;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    if (temp == NULL) {
        return NULL;
    }

    temp->head = NULL;

    return temp;
}

Node* createNode(int value, Node* next, Node* previous) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->value = value;
    newNode->next = next;
    newNode->previous = previous;

    return newNode;
}

int insert(List *list, int value) {
    if (list == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        Node *temp = createNode(value, NULL, NULL);
        if (temp == NULL) {
            return 1;
        }

        list->head = temp;

        return 0;
    }

    // if find Node with greater value, stay before it. May be case with end no greater value in list.
    Node *currentNode = list->head;
    while (currentNode->next != NULL) {
        if (currentNode->value >= value) {
            break;
        }
        currentNode = currentNode->next;
    }
    bool isEnd = currentNode->value < value;

    if (isEnd) {
        Node *temp = createNode(value, NULL, currentNode);
        if (temp == NULL) {
            return 1;
        }

        currentNode->next = temp;

        return 0;
    }

    Node *temp = createNode(value, currentNode, currentNode->previous);
    if (temp == NULL) {
        return 1;
    }

    if (currentNode->previous != NULL) {
        currentNode->previous->next = temp;
    }

    currentNode->previous = temp;
    if (list->head == currentNode) {
        list->head = temp;
    }

    return 0;
}

int delete(List *list, int value) {
    if (list == NULL) {
        return -1;
    }

    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (currentNode->value == value) {
            break;
        }

        currentNode = currentNode->next;
    }

    if (currentNode == NULL) {
        return -1;
    }
    if (currentNode->previous != NULL) {
        currentNode->previous->next = currentNode->next;
    } else {
        list->head = currentNode->next;
    }
    if (currentNode->next != NULL) {
        currentNode->next->previous = currentNode->previous;
    }

    free(currentNode);

    return 0;
}

void deleteList(List **list) {
    if (*list == NULL) {
        free(*list);
        return;
    }

    Node *currentNode = (*list)->head;
    while (currentNode != NULL) {
        delete(*list, currentNode->value);
        currentNode = (*list)->head;
    }

    free(*list);
    *list = NULL;
}

int getValue(List *list, int *errorCode) {
    if (list == NULL || list->head == NULL) {
        *errorCode = -1;
        return 0;
    }

    return list->head->value;
}

int printList(List *list) {
    if (list == NULL) {
        return -1;
    }

    printf("Sorted list: ");
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    return 0;
}

