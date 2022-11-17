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
} List;

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
    tempList->head->next = NULL;
    (*list)->head = (*list)->head->next;
    if ((*list)->head == NULL) {
        deleteList(list);
    }

    return tempList;
}

void putList(List *destinationList, List **sourceList) {
    if (sourceList == NULL) {
        return;
    }

    if ((*sourceList)->head == NULL) {
        deleteList(sourceList);
        return;
    }

    if (destinationList == NULL) {
        destinationList = (*sourceList);
        return;
    }

    if (destinationList->head == NULL) {
        destinationList->head = (*sourceList)->head;
        free(*sourceList);
        *sourceList = NULL;

        return;
    }

    Node *currentNode = (*sourceList)->head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    currentNode->next = destinationList->head;
    destinationList->head = (*sourceList)->head;

    free(*sourceList);
}

char* getFirstWord(List* list) {
    return list == NULL || list->head == NULL ? NULL : list->head->word;
}

int printList(List *list) {
    if (list == NULL) {
        return 0;
    }

    Node *currentNode = list->head;
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

    Node *nextNode = (*list)->head;
    Node *currentNode = NULL;

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

    Node *currentNode = list->head;
    unsigned int length = 0;

    while (currentNode != NULL) {
        ++length;
        currentNode = currentNode->next;
    }

    return length;
}

// tests

bool createListTest(void) {
    List *list = createList();

    bool test = list != NULL;

    deleteList(&list);

    return test;
}

bool addWordTest(void) {
    List *list = createList();

    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "CommonWealth");

    bool firstTest = !strcmp("check", list->head->word) && list->head->frequency == 2;
    bool secondTest = !strcmp("test", list->head->next->word) && list->head->next->frequency == 3;
    bool thirdTest = !strcmp("CommonWealth", list->head->next->next->word) && list->head->next->next->frequency == 1;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}

bool getListLengthTest(void) {
    List *list = createList();

    bool firstTest = getListLength(list) == 0;
    addWord(list, "check");
    addWord(list, "check");
    addWord(list, "test");
    addWord(list, "test");
    addWord(list, "test");

    bool secondTest = getListLength(list) == 2;

    addWord(list, "CommonWealth");
    addWord(list, "Burgundy");

    bool thirdTest = getListLength(list) == 4;

    deleteList(&list);

    return firstTest && secondTest && thirdTest;
}

bool deleteListTest(void) {
    List *list = createList();

    addWord(list, "test");

    deleteList(&list);

    return list == NULL;
}

bool listTest(void) {
    return createListTest() && addWordTest() && deleteListTest() && getListLengthTest();
}