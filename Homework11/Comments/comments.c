#include "comments.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum Symbol {
    star,
    slash,
    other
} Symbol;

typedef enum State {
    notComment,
    comment,
    startComment,
    endComment,
} State;

unsigned int** createMatrix() {
    unsigned int **table = (unsigned**)calloc(4, sizeof(unsigned*));
    if (table == NULL) {
        return NULL;
    }

    for (int i = 0; i < 4; ++i) {
        table[i] = calloc(3, sizeof(unsigned));
        if (table[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(table[j]);
            }

            free(table);
            return NULL;
        }
    }

    return table;
}

void deleteMatrix(unsigned **table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        free(table[i]);
    }

    free(table);
}

// if user delete matrix.txt file it's his problem that it won't work
// errorCode gets value:
// -1 if no file
// 1 if not enough memory
unsigned int** getDFATable(char *fileName, int *errorCode) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        *errorCode = -1;
        return NULL;
    }

    unsigned int **table = createMatrix();
    if (table == NULL) {
        *errorCode = 1;
        fclose(file);

        return NULL;
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            fscanf(file, "%u", &table[i][j]);
            fgetc(file);
        }
    }

    fclose(file);

    return table;
}

Symbol getSymbolToken(char symbol) {
    switch (symbol) {
        case '/': {
            return slash;
        }
        case '*': {
            return star;
        }
        default: {
            return other;
        }
    }
}

State move(State currentState, Symbol currentSymbol, unsigned **table) {
    State newState = table[currentState][currentSymbol];
    if (currentState == startComment && newState == comment) {
        printf("/*");
    } else if (currentState == endComment && newState == notComment) {
        printf("/\n");
    }

    return newState;
}

// return -1 if file doesn't exist
// return 1 if not enough memory
// return 0 if all is ok
// return -2 if last comment doesn't have end */
int printCommentsFromFile(char *fileName) {
    int errorCode = 0;
    unsigned **table = getDFATable("test.txt", &errorCode);
    if (errorCode) {
        return errorCode;
    }

    // doesn't check for NULL because upper function do it
    FILE *file = fopen(fileName, "r");

    char currentSymbol = (char)fgetc(file);
    State currentState = notComment;

    while (currentSymbol != EOF) {
        currentState = move(currentState, getSymbolToken(currentSymbol), table);
        if (currentState != notComment && currentState != startComment) {
            putchar(currentSymbol);
        }

        currentSymbol = (char)fgetc(file);
    }

    if (currentState == comment || currentState == endComment) {
        fclose(file);
        deleteMatrix(table);

        return -2;
    }

    fclose(file);
    deleteMatrix(table);

    return 0;
}