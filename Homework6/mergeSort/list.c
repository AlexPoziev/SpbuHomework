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

ListElement* getFirstPosition(List *list) {
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

int insert(List *list, Position *position) {
    if (list == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        ListElement *temp = malloc(sizeof(ListElement));
        if (temp == NULL) {
            return 1;
        }
        temp->contact = position->position->contact;
        temp->next = NULL;
        list->head = temp;

        return 0;
    }

    ListElement *temp = malloc(sizeof(ListElement));
    temp->contact = position->position->contact;
    temp->next = NULL;
    ListElement *lastElement = lastPosition(list);
    lastElement->next = temp;

    return 0;
}

void putHead(List *list, char *name, char *phoneNumber) {
    ListElement *temp = malloc(sizeof(ListElement));
    if (temp == NULL) {
        return;
    }
    temp->contact = malloc(sizeof(Contact));

    if (temp->contact == NULL) {
        return;
    }
    temp->contact->name = name;
    temp->contact->phoneNumber = phoneNumber;
    if (list->head == NULL) {
        temp->next = NULL;
        list->head = temp;

        return;
    }

    temp->next = list->head;
    list->head = temp;
}

void getNextPosition(Position *position) {
    if (position->position == NULL) {
        return;
    }

    position->position = position->position->next;
}

char* getPositionValue(Position *position, Priority priority, int *errorCode) {
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
        ListElement *smallStep = list->head;
        ListElement *largeStep = list->head;
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

    ListElement *temp = list->head;
    while (temp != NULL) {
        printf("%s %s \n", temp->contact->name, temp->contact->phoneNumber);
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
        if (temp->contact != NULL) {
            if (isAllocated) {
                free(temp->contact->phoneNumber);
                free(temp->contact->name);
            }
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

void deleteListMemory(List **list) {
    free(*list);
    *list = NULL;
}

bool isPositionNull(Position *position) {
    return position->position == NULL;
}