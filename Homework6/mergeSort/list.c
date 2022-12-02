#include "list.h"
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct ListElement {
    char* name;
    char* phoneNumber;
    struct ListElement *next;
} ListElement;

typedef struct List {
    ListElement *head;
} List;

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->head = NULL;

    return temp;
}

List* createListByElement(ListElement *element) {
    List *temp = malloc(sizeof(List));
    temp->head = element;

    return temp;
}

ListElement* getElementFromFile(FILE *file, int *errorCode) {
    ListElement *temp = malloc(sizeof(ListElement));
    if (temp == NULL) {
        *errorCode = 1;
        return NULL;
    }

    temp->name = calloc(MAX_SIZE, sizeof(char));
    if (temp->name == NULL) {
        free(temp);
        *errorCode = 1;

        return NULL;
    }

    int eofCheck = fscanf(file, "%s",  temp->name);
    if (eofCheck == EOF) {
        free(temp->name);
        free(temp);
        *errorCode = -1;

        return NULL;
    }

    eofCheck = fgetc(file);
    if (eofCheck == EOF) {
        free(temp->name);
        free(temp);
        *errorCode = -1;

        return NULL;
    }

    temp->phoneNumber = calloc(MAX_SIZE, sizeof(char));
    if (temp->phoneNumber == NULL) {
        free(temp->name);
        free(temp);
        *errorCode = 1;

        return NULL;
    }

    eofCheck = fscanf(file, "%[^\n]",  temp->phoneNumber);
    if (eofCheck == EOF) {
        free(temp->phoneNumber);
        free(temp->name);
        free(temp);
        *errorCode = -1;

        return NULL;
    }

    return temp;
}

int getFromFile(char* fileName, List* list) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return -2;
    }

    int errorCode = 0;

    ListElement* temp = getElementFromFile(file, &errorCode);
    if (errorCode) {
        fclose(file);
        return errorCode;
    }

    list->head = temp;
    list->head->next = NULL;
    ListElement *previousNode = list->head;

    while (!feof(file)) {
        temp->next = getElementFromFile(file, &errorCode);
        if (errorCode) {
            fclose(file);
            return errorCode;
        }

        temp = temp->next;
        temp->next = NULL;
        previousNode->next = temp;
        previousNode = temp;
    }

    fclose(file);

    return 0;
}

void cutList(ListElement* element) {
    element->next = NULL;
}

ListElement* getFirstListElement(List *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

ListElement* lastPosition(List *list) {
    ListElement *temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

int insert(List *list, ListElement *element) {
    if (list == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        list->head = element;
        list->head->next = NULL;

        return 0;
    }

    ListElement *lastElement = lastPosition(list);
    lastElement->next = element;
    element->next = NULL;

    return 0;
}

void putHead(List *list, char *name, char *phoneNumber) {
    ListElement *temp = malloc(sizeof(ListElement));
    if (temp == NULL) {
        return;
    }

    temp->name = name;
    temp->phoneNumber = phoneNumber;

    temp->next = list->head;
    list->head = temp;
}

ListElement* getNextListElement(ListElement *element) {
    if (element == NULL) {
        return NULL;
    }

    return element->next;
}

char* getListElementValue(ListElement *element, Priority priority) {
    if (element == NULL) {
        return NULL;
    }

    return priority == phoneNumber
            ? element->phoneNumber
            : element->name;
}

ListElement* getMiddleListElement(List *list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }

    ListElement *smallStep = list->head;
    ListElement *largeStep = list->head;
    while (largeStep != NULL && largeStep->next != NULL) {
        largeStep = largeStep->next->next;
        smallStep = smallStep->next;
    }

    return smallStep;
}

bool isEnd(ListElement *element) {
    if (element == NULL) {
        return true;
    }

    return element->next == NULL;
}

void printList(List *list) {
    if (list == NULL) {
        return;
    }

    ListElement *temp = list->head;
    while (temp != NULL) {
        printf("%s %s \n", temp->name, temp->phoneNumber);
        temp = temp->next;
    }
}

void deleteList(List **list, bool isAllocated) {
    if (*list == NULL) {
        free(*list);
        return;
    }

    ListElement *temp = (*list)->head;
    while (temp != NULL) {
        (*list)->head = (*list)->head->next;
        if (isAllocated) {
            free(temp->phoneNumber);
            free(temp->name);
        }

        temp = (*list)->head;
    }

    free(*list);
    *list = NULL;
}

void deleteListMemory(List **list) {
    free(*list);
    *list = NULL;
}

bool isListElementNull(ListElement* element) {
    return element == NULL;
}