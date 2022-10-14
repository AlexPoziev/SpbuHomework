#pragma once

#include <stdbool.h>

typedef struct Stack {
    int value;
    struct Stack *next;
}Stack;

//add value to stack
int push(Stack **head, int value);

//delete value from stack
int pop(Stack **head, int *errorCode);

//clear memory
void clearStack(Stack **head);

//check for empty head
