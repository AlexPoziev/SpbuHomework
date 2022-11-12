#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    int frequency;
    char *word;
    struct Node* next;
} Node;

typedef struct List {
    Node *head;
} list;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head = NULL;

    return temp;
}

Node *createNode(char *word) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }

    char *newWord = calloc(strlen(word), sizeof(char));
    if (newWord == NULL) {
        free(newNode);
        return NULL;
    }

    strcpy(newWord, word);
    newNode->word = newWord;
    newNode->frequency = 1;
    newNode->next = NULL;

    return newNode;
}

int addWord(List *list, char *word) {
    if (list->head == NULL) {
        Node *newNode = createNode(word);
        if (newNode == NULL) {
            return 1;
        }

        list->head = newNode;

        return 0;
    }

    Node *currentNode = list->head;
    bool isSame = true;

    while (isSame && currentNode->next != NULL) {
        isSame = strcmp(currentNode->word, word);
        currentNode = currentNode->next;
    }

    if (isSame) {
        isSame = strcmp(currentNode->word, word);
    }

    if (isSame) {
        Node *newNode = createNode(word);
        if (newNode == NULL) {
            return 1;
        }

        currentNode->next = newNode;

        return 0;
    }

    ++(currentNode->frequency);

    return 0;
}
