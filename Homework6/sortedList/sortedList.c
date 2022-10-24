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
    temp->head = NULL;

    return temp;
}

int insert(List *list, int value) {
    if (list == NULL) {
        return -1;
    }

    Node* temp = malloc(sizeof(Node));
    if (temp == NULL) {
        return 1;
    }

    if (list->head == NULL) {
        temp->value = value;
        temp->previous = NULL;
        temp->next = NULL;
        list->head = temp;

        return 0;
    }

    Node *currentNode = list->head;
    while (currentNode->next != NULL) {
        if (currentNode->value >= value) {
            break;
        }
        currentNode = currentNode->next;
    }
    bool isEnd = currentNode->value < value;

    if (isEnd) {
        temp->value = value;
        temp->previous = currentNode;
        temp->next = NULL;
        currentNode->next = temp;

        return 0;
    }

    if (currentNode->previous != NULL) {
        currentNode->previous->next = temp;
    }
    temp->previous = currentNode->previous;
    currentNode->previous = temp;
    temp->next = currentNode;

    return 0;
}

/*int delete(List *list, int value) {
    if (list == NULL) {
        return -1;
    }

    bool isEnd = 0;
    Node *currentNode = getNode(list, value, &isEnd);
    if (isEnd == 0 && currentNode == NULL) {
        return -1;
    }
    if (currentNode->previous != NULL) {
        currentNode->previous->next = currentNode->next;
    }
    if (currentNode->next != NULL) {
        currentNode->next->previous = currentNode->previous;
    }

    free(currentNode);

    return 0;
}*/

int printList(List *list) {
    if (list == NULL) {
        return -1;
    }
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    return 0;
}

