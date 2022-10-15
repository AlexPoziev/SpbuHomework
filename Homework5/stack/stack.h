#pragma once

#include <stdbool.h>

// int stack struct
typedef struct IntStack {
    int value;
    struct IntStack *next;
}IntStack;

//double stack struct
typedef struct DoubleStack {
    double value;
    struct DoubleStack *next;
}DoubleStack;

// add value to stack
int pushInt(IntStack **head, int value);

// add value to stack
int pushDouble(DoubleStack **head, double value);

// delete value from stack
int popInt(IntStack **head, int *errorCode);

// delete value from stack
double popDouble(DoubleStack **head, int *errorCode);

// clear memory of int stack
void clearIntStack(IntStack **head);

// clear memory of double stack
void clearDoubleStack(DoubleStack **head);

// check for empty int stack head
bool isIntEmpty(IntStack *head);

// check for empty double stack head
bool isDoubleEmpty(DoubleStack *head);