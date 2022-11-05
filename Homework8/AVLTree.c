#include "AVLTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *value;
    int token;
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
    Dictionary *newDictionary = malloc(sizeof(Dictionary));
    newDictionary->dictionary = NULL;
    return newDictionary;
}

Node* createNode(int token, char *value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->token = token;
    char *newValue = calloc(strlen(value), sizeof(char));
    stpcpy(newValue, value);
    newNode->value = newValue;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->balance = 0;

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

Node* insert(Node *node, int token, char *value, bool *isPart, int8_t *errorCode) {
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

    if (token < node->token) {
        node->leftChild = insert(node->leftChild, token, value, isPart, errorCode);
        direction = left;
    } else if (token > node->token) {
        node->rightChild = insert(node->rightChild, token, value, isPart, errorCode);
        direction = right;
    } else {
        // case finding existing token
        *isPart = true;
        char *newValue = calloc(strlen(value), sizeof(char));
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
int addValue(Dictionary *dictionary, int token, char* value) {
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

Node* delete(Node *node, int token, bool *isPart, int8_t *errorCode) {
    if (node == NULL) {
        // if not find node, then skip recursion
        *isPart = true;
        return node;
    }

    Direction direction = 0;

    if (token < node->token) {
        node->leftChild = delete(node->leftChild, token, isPart, errorCode);
        direction = left;
    } else if (token > node->token) {
        node->rightChild = delete(node->rightChild, token, isPart, errorCode);
        direction = right;
    } else {
        // check for delete case
        if (node->rightChild == NULL || node->leftChild == NULL) {
            Node *child = node->rightChild != NULL ? node->rightChild : node->leftChild;

            // no children
            if (child == NULL) {
                free(node->value);
                node->value = NULL;
                free(node);
                node = NULL;
            } else {
            // only child
                free(node->value);
                memcpy(node, child, sizeof(Node));
                free(child);
            }
        } else {
            // two children
            Node* approachChild = getMostRight(node);

            // copy values
            int temp = approachChild->token;
            char *tempValue = calloc(strlen(approachChild->value), sizeof(char));
            if (tempValue == NULL) {
                *errorCode = 1;
                *isPart = true;
                return node;
            }

            strcpy(tempValue, approachChild->value);

            // carry pointer to node for change its token after delete recursion
            node->value = tempValue;
            Node *tempNode = node;
            // recursion call to delete left most right element and balance it
            node = delete(node, approachChild->token, isPart, errorCode);

            tempNode->token = temp;
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
int deleteValue(Dictionary *dictionary, int token) {
    if (dictionary == NULL) {
        return -1;
    }

    bool isPart = false;
    int8_t errorCode = 0;
    dictionary->dictionary = delete(dictionary->dictionary, token, &isPart, &errorCode);

    return errorCode;
}

Node* findPosition(Dictionary *dictionary, int token, bool *isEnd) {
    Node *currentNode = dictionary->dictionary;
    if (currentNode->token == token) {
        *isEnd = false;
        return currentNode;
    }
    Node *nextNode = currentNode->token > token ? currentNode->leftChild : currentNode->rightChild;
    while (nextNode != NULL) {
        currentNode = nextNode;
        if (currentNode->token == token) {
            *isEnd = false;
            return currentNode;
        }
        nextNode = currentNode->token > token ? currentNode->leftChild : currentNode->rightChild;
    }

    *isEnd = true;
    return currentNode;
}

bool isContain(Dictionary *dictionary, int token) {
    if (dictionary == NULL) {
        return false;
    }
    bool isEnd = false;
    findPosition(dictionary, token, &isEnd);

    return !isEnd;
}

char* getValue(Dictionary *dictionary, int token) {
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
    child->value = NULL;
    free(child);
    child = NULL;
}

void deleteTree(Dictionary **dictionary) {
    deleteTreeRecursion((*dictionary)->dictionary);

    free(*dictionary);
    *dictionary = NULL;
}

int treeHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    // Find the height of left, right subtrees
    int leftHeight = treeHeight(node->leftChild);
    int rightHeight = treeHeight(node->rightChild);

    // Find max(subtree_height) + 1 to get the height of the tree
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
int8_t hardBalanceCalculate(Node *node) {

    return (int8_t)(treeHeight(node->rightChild) - treeHeight(node->leftChild));
}

bool balanceTest(Node *node) {
    if (node == NULL){
        return true;
    }

    bool check = balanceTest(node->leftChild);
    if (check == false) {
        return false;
    }
    check = balanceTest(node->rightChild);
    if (check == false) {
        return false;
    }

    int test = (int)hardBalanceCalculate(node);
    return test == node->balance && node->balance >= -2 && node->balance <= 2;
}

bool AVLTreeBalanceTest(void) {
    Dictionary *test = createDictionary();
    addValue(test, 5, "test");
    addValue(test, 0, "test");
    addValue(test, 10, "test");
    addValue(test, 15, "test");
    addValue(test, 20, "test");
    bool firstTest = balanceTest(test->dictionary);

    deleteValue(test, 5);
    bool secondTest = balanceTest(test->dictionary);

    addValue(test, 20, "test");
    addValue(test, 25, "test");
    addValue(test, 30, "test");
    addValue(test, 35, "test");
    addValue(test, 40, "test");
    bool thirdTest = balanceTest(test->dictionary);

    addValue(test, -10, "test");
    addValue(test, -15, "test");
    addValue(test, -20, "test");
    addValue(test, -30, "test");
    addValue(test, 50, "test");
    bool fourthTest = balanceTest(test->dictionary);

    deleteValue(test, 20);
    deleteValue(test, 50);
    deleteValue(test, -15);
    deleteValue(test, 25);
    deleteValue(test, 25);
    bool fifthTest = balanceTest(test->dictionary);

    deleteTree(&test);

    return firstTest && secondTest && thirdTest && fourthTest && fifthTest;
}
