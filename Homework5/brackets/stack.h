#pragma once

#include <stdbool.h>

typedef struct Stack {
    int value;
    struct Stack *next;
}Stack;

int push(Stack **head, int value);

int pop(Stack **head, int *errorCode);

void clearStack(Stack **head);

bool isEmpty(Stack *head);