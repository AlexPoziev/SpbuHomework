#include "stack.h"


#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

int push(Stack **head, double value) {
    Stack *temp = (Stack*)(malloc(sizeof(Stack)));
    if (temp == NULL) {
        return 1;
    }

    temp->value = value;
    temp->next = *head;
    *head = temp;

    return 0;
}

double pop(Stack **head, int *errorCode) {
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
    Stack *temp = (*head)->next;
    free(*head);
    *head = temp;

    return value;
}

bool isEmpty(Stack *head) {
    return (head == NULL) ? true : false;
}

void clearStack(Stack **head) {
    Stack *next= NULL;
    while (!isEmpty(*head)) {
        int errorCode = 0;
        pop(head, &errorCode);
    }
}