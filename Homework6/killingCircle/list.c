#include "list.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

List* createList(void) {
    return malloc(sizeof(Node));
}




