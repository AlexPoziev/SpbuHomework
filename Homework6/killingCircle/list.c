#include "list.h"
#include <stdio.h>

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
    return list->lastElement->position >= position && position > 0;
}

List* createList(void) {
    List *temp = malloc(sizeof(List));
    temp->lastElement = NULL;
    temp->head = NULL;
    return temp;
}

int listSize(List *list) {
    return list->head == NULL ? 0 : (list->lastElement->position + 1);
}

bool isNodeEmpty(Node *head) {
    return head == NULL;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

Node* findPosition(List *list, int position) {
    if (isEmpty(list) || checkCorrectivePosition(list, position)) {
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

void plusOnePosition(Node *next, List *list) {
    Node *temp = next;
    while(temp != list->lastElement) {
        ++(temp->position);
        temp = temp->next;
    }
    ++(list->lastElement->position);
}

void minusOnePosition(Node *next, List *list) {
    Node *temp = next;
    while(temp != list->lastElement) {
        --(temp->position);
        temp = temp->next;
    }
    --(list->lastElement->position);
}

int insert(List *list, int value, int position) {
    if ((list->lastElement == NULL && position != 0) || position < 0) {
        return -1;
    }
    Node *temp = NULL;
    if (list->lastElement == NULL && position == 0) {
        temp = malloc(sizeof(Node));
        temp->value = value;
        temp->position = position;
        list->lastElement = temp;
        list->head = temp;

        return 0;
    }

    if (position == 0) {
        temp = malloc(sizeof(Node));
        plusOnePosition(list->head, list);

        temp->value = value;
        temp->position = position;
        temp->next = list->head;
        list->lastElement->next = temp;
        list->head = temp;

        return 0;
    }

    if (position == list->lastElement->position + 1) {
        temp = malloc(sizeof(Node));
        temp->value = value;
        temp->position = position;
        temp->next = list->head;
        list->lastElement->next = temp;
        list->lastElement = temp;

        return 0;
    }

    if (!checkCorrectivePosition(list, position)) {
        return -1;
    }

    Node *currentNode = list->head->next;
    Node *lastNode = list->head;
    while (currentNode->position != position) {
        if (currentNode->next == NULL) {
            return -1;
        }
        lastNode = currentNode;
        currentNode = currentNode->next;
    }
    temp = malloc(sizeof(Node));
    lastNode->next = temp;
    temp->value = value;
    temp->position = position;
    temp->next = currentNode;

    plusOnePosition(currentNode, list);

    return 0;
}

int delete(List *list, int position, int *errorCode) {
    if (isEmpty(list) || position < 0 || list->lastElement->position < position ) {
        *errorCode = -1;
        return 0;
    }
    int temp = 0;

    if (list->head == list->lastElement) {
        temp = list->head->value;
        free(list->head);
        list->head = NULL;
        list->lastElement = NULL;

        return temp;
    }

    if (position == 0) {
        minusOnePosition(list->head, list);
        list->lastElement->next = list->head->next;
        temp = list->head->value;
        free(list->head);
        list->head = list->lastElement->next;

        return temp;
    }

    if (!checkCorrectivePosition(list, position)) {
        return -1;
    }

    Node *currentNode = list->head->next;
    Node *lastNode = list->head;
    while (currentNode->position != position) {
        if (currentNode->next == NULL) {
            *errorCode = -1;
            return 0;
        }
        lastNode = currentNode;
        currentNode = currentNode->next;
    }
    temp = currentNode->value;
    if (currentNode->position == (list->lastElement->position)) {
        list->lastElement = lastNode;
        lastNode->next = currentNode->next;
        free(currentNode);
    } else {
        lastNode->next = currentNode->next;
        minusOnePosition(currentNode, list);
        free(currentNode);
    }

    return temp;
}

int cycleListDelete(List *list, int position, int *errorCode) {
    if (isEmpty(list)) {
        return -1;
    }
    printf(" %d ", list->lastElement->position);
    int temp = delete(list, position % (listSize(list)), errorCode);
    if (*errorCode == -1) {
        return 0;
    }

    return temp;
}

int cycleListInsert(List *list, int value, int position){
    if (isEmpty(list)) {
        return -1;
    }
    int errorCode = insert(list, value, position % (listSize(list) + 1));
    if (errorCode == -1) {
        return -1;
    }

    return 0;
}

void clear(List** list) {
    int errorCode = 0;
    while (!isEmpty(*list)){
        delete(*list, 0, &errorCode);
    }
    free(*list);
    *list = NULL;
}

int print(List *list) {
    if (list == NULL || list->head == NULL) {
        return -1;
    }
    Node *temp = list->head;
    printf("The list is: ");
    while(temp->position != list->lastElement->position) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("%d ", temp->value);
    printf("\n");
}