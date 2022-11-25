#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

int pushInt(IntStack **head, int value) {
    IntStack *temp = (IntStack*)(malloc(sizeof(IntStack)));
    if (temp == NULL) {
        return 1;
    }

    temp->value = value;
    temp->next = *head;
    *head = temp;

    return 0;
}

int pushDouble(DoubleStack **head, double value) {
    DoubleStack *temp = (DoubleStack *)(malloc(sizeof(DoubleStack)));
    if (temp == NULL) {
        return 1;
    }

    temp->value = value;
    temp->next = *head;
    *head = temp;

    return 0;
}

int popInt(IntStack **head, int *errorCode) {
    if (*head == NULL) {
        if (errorCode != NULL) {
            *errorCode = -1;
        }

        return 0;
    }
    if (errorCode != NULL) {
        *errorCode = 0;
    }

    int value = (*head)->value;
    IntStack *temp = (*head)->next;
    free(*head);
    *head = temp;

    return value;
}

double popDouble(DoubleStack **head, int *errorCode) {
    if (*head == NULL) {
        if (errorCode != NULL) {
            *errorCode = -1;
        }

        return 0;
    }
    if (errorCode != NULL) {
        *errorCode = 0;
    }

    double value = (*head)->value;
    DoubleStack *temp = (*head)->next;
    free(*head);
    *head = temp;

    return value;
}

bool isIntEmpty(IntStack *head) {
    return (head == NULL) ? true : false;
}

bool isDoubleEmpty(DoubleStack *head) {
    return (head == NULL) ? true : false;
}

void clearIntStack(IntStack **head) {
    IntStack *next= NULL;
    while (!isIntEmpty(*head)) {
        int errorCode = 0;
        popInt(head, &errorCode);
    }
}

void clearDoubleStack(DoubleStack **head) {
    IntStack *next= NULL;
    while (!isDoubleEmpty(*head)) {
        int errorCode = 0;
        popDouble(head, &errorCode);
    }
}
