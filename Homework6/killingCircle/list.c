#include "list.h"
#include <stdio.h>

// реализовать добавление после определенного номера элемента
// додумать как создавать место если нет там ничего возмонж гварды но не точно
// ну и в целом доделать

typedef struct Node {
    int value;
    int position;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *lastElement;
} List;

bool checkCorrectivePosition(List* list, int position) {
    return list->lastElementPosition >= position;
}

List* createList(void) {
    return malloc(sizeof(List));
}

bool isNodeEmpty(Node *head) {
    return head == NULL;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

Node* findPosition(List *list, int position) {
    if (isEmpty(list) || position < 0) {
        return NULL;
    }
    Node *temp = list->head;

    while (temp->position != position) {
        if (temp->next == NULL) {
            return NULL;
        }
        temp = temp->next;
    }

    printf("ewkere");
    return temp;
}

Node* lastElement(List *list) {
    Node *temp = list->head;
    while (!isNodeEmpty(temp)) {
        temp = temp->next;
    }

    return temp;
}

int insert(List *list, int value, int position) {
    if (list->lastElementPosition == -1 && position != 0) {
        return -1;
    }
    if (list->lastElementPosition == -1 && position == 0) {
        Node *temp = malloc(sizeof(Node));
        temp->value = value;
        temp->value = 0;
        list->lastElementPosition = 0;
        list->head = temp;

        return 0;
    }

    if (list->lastElementPosition)

    if (position)
}

void print(List *list) {
    Node *temp = list->head;
    printf("The list is: ");
    while(temp->next != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("%d ", temp->value);
    printf("\n");
}//