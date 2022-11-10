#include "list.h"
#include <stdlib.h>

#define MAX_SIZE 20

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
    Node *position;
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

List* createPositionList(Position *position) {
    List *temp = malloc(sizeof(List));
    temp->head = position->position;
    return temp;
}

int getFromFile(FILE* file, char* fileName, List* list) {
    file = fopen(fileName, "r");
    if (feof(file)) {
        fclose(file);
        return -2;
    }

    Node *temp = malloc(sizeof(Node));
    if (temp == NULL) {
        return 1;
    }

    temp->contact = malloc(sizeof(Contact));
    if (temp->contact == NULL) {
        free(temp);
        return 1;
    }
    temp->contact->name = calloc(MAX_SIZE, sizeof(char));
    if (temp->contact->name == NULL) {
        free(temp->contact);
        free(temp);

        return 1;
    }
    int eofCheck = fscanf(file, "%s",  temp->contact->name);
    if (eofCheck == EOF) {
        free(temp->contact->name);
        free(temp->contact);
        free(temp);

        return -1;
    }

    fgetc(file);
    temp->contact->phoneNumber = calloc(MAX_SIZE, sizeof(char));
    if (temp->contact->phoneNumber == NULL) {
        free(temp->contact->name);
        free(temp->contact);
        free(temp);

        return 1;
    }
    eofCheck = fscanf(file, "%[^\n]",  temp->contact->phoneNumber);
    if (eofCheck == EOF) {
        free(temp->contact->phoneNumber);
        free(temp->contact->name);
        free(temp->contact);
        free(temp);

        return -1;
    }

    list->head = temp;
    list->head->next = NULL;
    Node *previousNode = list->head;

    while (!feof(file)) {
        temp = temp->next;
        temp = malloc(sizeof(Node));
        if (temp == NULL) {
            return 1;
        }
        temp->contact = malloc(sizeof(Contact));
        if (temp->contact == NULL) {
            free(temp);

            return 1;
        }
        temp->contact->name = calloc(MAX_SIZE, sizeof(char));
        if (temp->contact->name == NULL) {
            free(temp->contact);
            free(temp);

            return 1;
        }
        eofCheck = fscanf(file, "%s", temp->contact->name);
        if (eofCheck == EOF) {
            free(temp->contact->name);
            free(temp->contact);
            free(temp);

            return -1;
        }
        fgetc(file);
        temp->contact->phoneNumber = calloc(MAX_SIZE, sizeof(char));
        if (temp->contact->phoneNumber == NULL) {
            free(temp->contact->name);
            free(temp->contact);
            free(temp);

            return 1;
        }
        eofCheck = fscanf(file, "%[^\n]", temp->contact->phoneNumber);
        if (eofCheck == EOF) {
            free(temp->contact->phoneNumber);
            free(temp->contact->name);
            free(temp->contact);
            free(temp);

            return -1;
        }

        temp->next = NULL;
        previousNode->next = temp;
        previousNode = temp;
    }

    fclose(file);

    return 0;
}

void cutList(Position *position) {
    position->position->next = NULL;
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
        Node *temp = malloc(sizeof(Node));
        if (temp == NULL) {
            return 1;
        }
        temp->contact = position->position->contact;
        temp->next = NULL;
        list->head = temp;

        return 0;
    }

    Node *temp = malloc(sizeof(Node));
    temp->contact = position->position->contact;
    temp->next = NULL;
    Node *lastElement = lastPosition(list);
    lastElement->next = temp;

    return 0;
}

void putHead(List *list, char *name, char *phoneNumber) {
    Node *temp = malloc(sizeof(Node));
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

void deleteList(List **list, bool isAllocated) {
    if (*list == NULL) {
        free(*list);
        return;
    }
    Node *temp = (*list)->head;
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