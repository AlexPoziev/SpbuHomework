#pragma once

#include <stdbool.h>

typedef struct Stack {
    double value;
    struct Stack *next;
}Stack;

//add value to stack
int push(Stack **head, double value);

//delete value from stack
double pop(Stack **head, int *errorCode);

//clear memory
void clearStack(Stack **head);

//check for empty head
bool isEmpty(Stack *head);