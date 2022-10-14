#pragma once

#include <stdbool.h>

typedef struct Stack {
    char value;
    struct Stack *next;
}Stack;

int push(Stack **head, char value);

int pop(Stack **head, int *errorCode);

void clearStack(Stack **head);

bool isEmpty(Stack *head);