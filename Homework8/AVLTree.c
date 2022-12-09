#include "AVLTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *value;
    char *token;
    int8_t balance;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

typedef struct Dictionary {
    Node *dictionary;
} Dictionary;

typedef enum Direction{
    left = -1,
    right = 1
} Direction;

Dictionary* createDictionary(void) {
    Dictionary *newDictionary = calloc(1, sizeof(Dictionary));

    return newDictionary;
}

Node* createNode(char *token, char *value) {
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }

    char *newToken = calloc(strlen(token) + 1, sizeof(char));
    if (newToken == NULL) {
        free(newNode);
        return NULL;
    }

    strcpy(newToken, token);
    newNode->token = newToken;

    char *newValue = calloc(strlen(value) + 1, sizeof(char));
    if (newValue == NULL) {
        free(newNode);
        free(newToken);

        return NULL;
    }

    stpcpy(newValue, value);
    newNode->value = newValue;

    return newNode;
}

Node* rotateLeft(Node *currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;

    rightChild->leftChild = currentNode;
    currentNode->rightChild = leftGrandson;

    // two ways
    if (rightChild->balance) {
        currentNode->balance = 0;
        rightChild->balance = 0;
    } else {
        currentNode->balance = 1;
        rightChild->balance = -1;
    }

    return rightChild;
}

Node* bigRotateLeft(Node* currentNode) {
    Node *rightChild = currentNode->rightChild;
    Node *leftGrandson = rightChild->leftChild;
    Node *leftGrandGrandson = leftGrandson->leftChild;
    Node *rightGrandGrandson = leftGrandson->rightChild;

    leftGrandson->leftChild = currentNode;
    leftGrandson->rightChild = rightChild;
    currentNode->rightChild = leftGrandGrandson;
    rightChild->leftChild = rightGrandGrandson;

    switch (leftGrandson->balance) {
        case -1: {
            currentNode->balance = 0;
            rightChild->balance = 1;
            break;
        }
        case 0: {
            currentNode->balance = 0;
            rightChild->balance = 0;
            break;
        }
        case 1: {
            currentNode->balance =-1;
            rightChild->balance = 0;
            break;
        }
    }
    leftGrandson->balance = 0;

    return leftGrandson;
}

Node* rotateRight(Node *currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;

    leftChild->rightChild = currentNode;
    currentNode->leftChild = rightGrandson;

    // two ways
    if (leftChild->balance) {
        currentNode->balance = 0;
        leftChild->balance = 0;
    } else {
        currentNode->balance = -1;
        leftChild->balance = 1;
    }

    return leftChild;
}

Node* bigRotateRight(Node* currentNode) {
    Node *leftChild = currentNode->leftChild;
    Node *rightGrandson = leftChild->rightChild;
    Node *rightGrandGrandson = rightGrandson->rightChild;
    Node *leftGrandGrandson = rightGrandson->leftChild;

    rightGrandson->rightChild = currentNode;
    rightGrandson->leftChild = leftChild;
    currentNode->leftChild = rightGrandGrandson;
    leftChild->rightChild = leftGrandGrandson;

    // really hope that a had correctly inverse big rotate left case
    switch (rightGrandson->balance) {
        case -1: {
            currentNode->balance = -1;
            leftChild->balance = 0;
            break;
        }
        case 0: {
            currentNode->balance = 0;
            leftChild->balance = 0;
            break;
        }
        case 1: {
            currentNode->balance =0;
            leftChild->balance = 1;
            break;
        }
    }

    rightGrandson->balance = 0;

    return rightGrandson;
}

Node* balance(Node *node) {
    if (node->balance == 2) {
        if (node->rightChild->balance >= 0) {
            return rotateLeft(node);
        }

        return bigRotateLeft(node);
    }

    if (node->balance == -2) {
        if (node->leftChild->balance <= 0){
            return rotateRight(node);
        }

        return bigRotateRight(node);
    }

    return node;
}

Node* insert(Node *node, char *token, char *value, bool *isPart, int8_t *errorCode) {
    // create leaf
    if (node == NULL) {
        Node *newNode = createNode(token, value);
        if (newNode == NULL) {
            *errorCode = 1;
            *isPart = true;

            return NULL;
        }

        return newNode;
    }

    Direction direction = 0;

    if (strcmp(token, node->token) < 0) {
        node->leftChild = insert(node->leftChild, token, value, isPart, errorCode);
        direction = left;
    } else if (strcmp(token, node->token) > 0) {
        node->rightChild = insert(node->rightChild, token, value, isPart, errorCode);
        direction = right;
    } else {
        // case finding existing token
        *isPart = true;
        char *newValue = calloc(strlen(value) + 1, sizeof(char));
        if (newValue == NULL) {
            *errorCode = 1;
        } else {
            strcpy(newValue, value);
            free(node->value);
            node->value = newValue;
            return node;
        }
    }

    // firstly was way to get from recursion without changing balance for create leaf case
    // now just general way to skip recursion
    if (*isPart) {
        return node;
    }

    node->balance = (int8_t)(node->balance + direction);
    // if -2 or 2 no more changes in balance in recursive calls
    // if 0 that means token get position of second child and if before it was ok, its will be ok after that :)
    if (node->balance == 2 || node->balance == -2 || node->balance == 0) {
        *isPart = true;
    }

    return balance(node);
}

// just a shell, call insert() function, that really adds values
int addValue(Dictionary *dictionary, char *token, char* value) {
    if (dictionary == NULL) {
        return -1;
    }
    
    if (dictionary->dictionary == NULL) {
        Node *newValue = createNode(token, value);
        dictionary->dictionary = newValue;

        return 0;
    }

    bool isPart = false;
    int8_t errorCode = 0;
    dictionary->dictionary = insert(dictionary->dictionary, token, value, &isPart, &errorCode);

    return errorCode;
}

// get most right of left subtree
Node* getMostRight(Node* root) {
    Node *currentNode = root->leftChild;
    Node *next = currentNode->rightChild;
    while (next != NULL) {
        currentNode = next;
        next = currentNode->rightChild;
    }

    return currentNode;
}

Node* delete(Node *node, char *token, bool *isPart, int8_t *errorCode) {
    if (node == NULL) {
        // if not find node, then skip recursion
        *isPart = true;
        return node;
    }

    Direction direction = 0;

    if (strcmp(token, node->token) < 0) {
        node->leftChild = delete(node->leftChild, token, isPart, errorCode);
        direction = left;
    } else if (strcmp(token, node->token) > 0) {
        node->rightChild = delete(node->rightChild, token, isPart, errorCode);
        direction = right;
    } else {
        // check for delete case
        if (node->rightChild == NULL || node->leftChild == NULL) {
            Node *child = node->rightChild != NULL ? node->rightChild : node->leftChild;

            // no children
            if (child == NULL) {
                free(node->value);
                free(node->token);
                free(node);
                node = NULL;
            } else {
            // only child
                free(node->value);
                free(node->token);
                memcpy(node, child, sizeof(Node));
                free(child);
            }
        } else {
            // two children
            Node* approachChild = getMostRight(node);

            // copy values
            char *tempToken = calloc(strlen(approachChild->token) + 1, sizeof(char));
            if (tempToken == NULL) {
                *errorCode = 1;
                *isPart = true;

                return node;
            }

            char *tempValue = calloc(strlen(approachChild->value) + 1, sizeof(char));
            if (tempValue == NULL) {
                *errorCode = 1;
                *isPart = true;
                free(tempToken);

                return node;
            }

            strcpy(tempToken, approachChild->token);
            strcpy(tempValue, approachChild->value);

            // carry pointer to node for change its token after delete recursion
            node->value = tempValue;
            Node *tempNode = node;
            // recursion call to delete left most right element and balance it
            node = delete(node, approachChild->token, isPart, errorCode);

            tempNode->token = tempToken;
        }
    }

    if (*isPart || node == NULL) {
        return node;
    }

    // balance part
    node->balance = (int8_t)(node->balance - direction);
    if (node->balance == 1 || node->balance == -1) {
        *isPart = true;
    }

    return balance(node);
}

// just a shell, call delete() function, that really delete values
int deleteValue(Dictionary *dictionary, char *token) {
    if (dictionary == NULL) {
        return -1;
    }

    bool isPart = false;
    int8_t errorCode = 0;
    dictionary->dictionary = delete(dictionary->dictionary, token, &isPart, &errorCode);

    return errorCode;
}

Node* findPosition(Dictionary *dictionary, const char *token, bool *isEnd) {
    Node *currentNode = dictionary->dictionary;
    if (strcmp(currentNode->token, token) == 0) {
        *isEnd = false;
        return currentNode;
    }

    Node *nextNode = strcmp(currentNode->token, token) > 0 ? currentNode->leftChild : currentNode->rightChild;
    while (nextNode != NULL) {
        currentNode = nextNode;
        if (strcmp(currentNode->token, token) == 0) {
            *isEnd = false;
            return currentNode;
        }

        nextNode = strcmp(currentNode->token, token) > 0 ? currentNode->leftChild : currentNode->rightChild;
    }

    *isEnd = true;

    return currentNode;
}

bool isContain(Dictionary *dictionary, char *token) {
    if (dictionary == NULL) {
        return false;
    }

    bool isEnd = false;

    findPosition(dictionary, token, &isEnd);

    return !isEnd;
}

char* getValue(Dictionary *dictionary, char *token) {
    if (dictionary == NULL) {
        return NULL;
    }

    bool isEnd = false;
    Node *currentNode = findPosition(dictionary, token, &isEnd);

    return isEnd ? NULL : currentNode->value;
}

void deleteTreeRecursion(Node *child) {
    if (child == NULL) {
        return;
    }

    deleteTreeRecursion(child->leftChild);
    deleteTreeRecursion(child->rightChild);

    free(child->value);
    free(child->token);
    free(child);
}

void deleteTree(Dictionary **dictionary) {
    deleteTreeRecursion((*dictionary)->dictionary);

    free(*dictionary);
    *dictionary = NULL;
}

int balanceTree(Node* node, bool *isBalanced) {
    if (node == NULL || *isBalanced == false) {
        return 0;
    }

    int leftHeight = balanceTree(node->leftChild, isBalanced);
    int rightHeight = balanceTree(node->rightChild, isBalanced);

    if (node->balance != (rightHeight - leftHeight)) {
        *isBalanced = false;
    }
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

bool AVLTreeBalanceTest(void) {
    Dictionary *test = createDictionary();
    addValue(test, "b", "test");
    addValue(test, "a", "test");
    addValue(test, "ba", "test");
    addValue(test, "bc", "test");
    addValue(test, "dc", "test");
    bool firstTest = true;
    balanceTree(test->dictionary, &firstTest);

    deleteValue(test, "b");
    bool secondTest = true;
    balanceTree(test->dictionary, &secondTest);

    addValue(test, "bc", "test");
    addValue(test, "dc", "test");
    addValue(test, "lc", "test");
    addValue(test, "ks", "test");
    addValue(test, "dff", "test");
    bool thirdTest = true;
    balanceTree(test->dictionary, &thirdTest);

    addValue(test, "chchc", "test");
    addValue(test,  "a", "test");
    addValue(test, "b", "test");
    addValue(test, "a", "test");
    addValue(test, "125", "test");
    bool fourthTest = true;
    balanceTree(test->dictionary, &fourthTest);

    deleteValue(test, "a");
    deleteValue(test, "b");
    deleteValue(test, "dc");
    deleteValue(test, "ks");
    deleteValue(test, "125");
    bool fifthTest = true;
    balanceTree(test->dictionary, &fifthTest);

    deleteTree(&test);

    return firstTest && secondTest && thirdTest && fourthTest && fifthTest;
}
