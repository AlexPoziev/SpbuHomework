#include "binaryTree.h"

#include <stdlib.h>

typedef struct Node {
    int token;
    char *word;
    struct Node* leftChild;
    struct Node* rightChild;
    struct Node* parent;
} Node;

typedef struct Dictionary {
    Node *root;
} Dictionary;

Dictionary* createDictionary(void) {
    Dictionary *temp = malloc(sizeof(Dictionary));
    temp->root = NULL;
    return temp;
}

Node* findPosition(Dictionary *dictionary, int token, bool *isEnd) {
    Node *currentNode = dictionary->root;
    Node *nextNode = currentNode->token < token ? currentNode->leftChild : currentNode->rightChild;
    while (nextNode != NULL && nextNode->token != token) {
        currentNode = nextNode;
        nextNode = currentNode->token < token ? currentNode->leftChild : currentNode->rightChild;
    }

}

int addWord(Dictionary *dictionary, int token, char* word) {
    if (dictionary == NULL || word == NULL) {
        return 1;
    }

    if (dictionary->root == NULL) {
        dictionary->root = malloc(sizeof(Node));
        if (dictionary->root == NULL) {
            return 1;
        }
        dictionary->root->leftChild = NULL;
        dictionary->root->rightChild = NULL;
        dictionary->root->parent = NULL;
        dictionary->root->token = token;
        dictionary->root->word = word;

        return 0;
    }


}