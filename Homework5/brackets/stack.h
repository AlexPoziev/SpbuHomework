#pragma once

#include <stdbool.h>

typedef struct Stack {
    char value;
    struct Stack *next;
}Stack;

//add value to stack
int push(Stack **head, char value);

//delete value from stack
char pop(Stack **head, int *errorCode);

//clear memory
void clearStack(Stack **head);

//check for empty head
bool isEmpty(Stack *head);