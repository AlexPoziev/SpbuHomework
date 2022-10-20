#include "list.h"

typedef struct Node {
    int value;
    int position;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

bool isNodeEmpty(Node *head) {
    return head == NULL;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

Node* lastElement(List *list) {
    Node *temp = list->head;
    while (!isNodeEmpty(temp)) {
        temp = temp->next;
    }

    return temp;
}

List* createList(void) {
    return malloc(sizeof(Node));
}

int insert(List *list, int value) {

}


