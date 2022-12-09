#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListElement {
    int frequency;
    char *word;
    struct ListElement* next;
} ListElement;

typedef struct List {
    ListElement *head;
} List;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head = NULL;

    return temp;
}

ListElement *createNode(char *word) {
    ListElement *newNode = malloc(sizeof(ListElement));
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
        ListElement *newNode = createNode(word);
        if (newNode == NULL) {
            return 1;
        }

        list->head = newNode;

        return 0;
    }

    ListElement *currentNode = list->head;
    int strcmpResult = 1;

    while (strcmpResult != 0 && currentNode->next != NULL) {
        strcmpResult = strcmp(currentNode->word, word);
        currentNode = currentNode->next;
    }

    if (strcmpResult != 0) {
        strcmpResult = strcmp(currentNode->word, word);
    }

    if (strcmpResult != 0) {
        ListElement *newNode = createNode(word);
        if (newNode == NULL) {
            return 1;
        }

        currentNode->next = newNode;

        return 0;
    }

    ++(currentNode->frequency);

    return 0;
}

List* getFirst(List **list, int *errorCode) {
    if (list == NULL || (*list)->head == NULL) {
        return NULL;
    }

    List *tempList = createList();
    if (tempList == NULL) {
        *errorCode = 1;
        return NULL;
    }

    tempList->head = (*list)->head;
    (*list)->head = (*list)->head->next;
    tempList->head->next = NULL;
    if ((*list)->head == NULL) {
        deleteList(list);
    }

    return tempList;
}

void putList(List **destinationList, List **sourceList) {
    if (sourceList == NULL) {
        return;
    }

    if ((*sourceList)->head == NULL) {
        deleteList(sourceList);
        return;
    }

    if (destinationList == NULL) {
        *destinationList = *sourceList;
        return;
    }

    if ((*destinationList)->head == NULL) {
        (*destinationList)->head = (*sourceList)->head;
        free(*sourceList);
        *sourceList = NULL;

        return;
    }

    ListElement *currentNode = (*sourceList)->head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    currentNode->next = (*destinationList)->head;
    (*destinationList)->head = (*sourceList)->head;

    free(*sourceList);
}

char* getFirstWord(List* list) {
    return list == NULL || list->head == NULL ? NULL : list->head->word;
}

int printList(List *list) {
    if (list == NULL) {
        return 0;
    }

    ListElement *currentNode = list->head;
    int printedCount = 0;

    while (currentNode != NULL) {
        printf("'%s' %d times \n", currentNode->word, currentNode->frequency);
        currentNode = currentNode->next;
        ++printedCount;
    }

    return printedCount;
}

void deleteList(List **list) {
    if (*list == NULL) {
        return;
    }

    ListElement *nextNode = (*list)->head;
    ListElement *currentNode = NULL;

    while (nextNode != NULL) {
        currentNode = nextNode;
        nextNode = nextNode->next;

        free(currentNode->word);
        free(currentNode);
    }

    free(*list);

    *list = NULL;
}

unsigned int getListLength(List *list) {
    if (list == NULL) {
        return 0;
    }

    ListElement *currentNode = list->head;
    unsigned int length = 0;

    while (currentNode != NULL) {
        ++length;
        currentNode = currentNode->next;
    }

    return length;
}

ListElement* getFirstListElement(List* list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

ListElement* getNextListElement(ListElement *element) {
    if (element == NULL) {
        return NULL;
    }

    return element->next;
}

char* getElementWord(ListElement *element) {
    if (element == NULL) {
        return NULL;
    }

    return element->word;
}

unsigned int getElementFrequency(ListElement *element, int *errorCode) {
    if (element == NULL) {
        *errorCode = -1;
        return 0;
    }

    return element->frequency;
}