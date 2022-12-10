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

State lengthMove(State currentState, Symbol currentSymbol, unsigned **table, unsigned *commentsCount) {
    State newState = table[currentState][currentSymbol];
    // get number of comments, because I want to add \n after each comment
    if (currentState == startComment && newState == comment) {
        ++(*commentsCount);
    }

    return newState;
}

// count comments length to allocate memory
// errorCode get value 1 if comment doesn't have end */
unsigned getCommentsLength(FILE *file, unsigned **table, int *errorCode) {
    unsigned int commentsLength = 0;
    char currentSymbol = (char)fgetc(file);
    State currentState = notComment;

    while (currentSymbol != EOF) {
        currentState = lengthMove(currentState, getSymbolToken(currentSymbol), table, &commentsLength);
        if (currentState == comment) {
            ++commentsLength;
        }

        currentSymbol = (char)fgetc(file);
    }

    if (currentState == comment || currentState == endComment) {
        *errorCode = 1;
    }

    // + 3 because don't count '/' and '/*'
    return commentsLength + 3;
}

State move(State currentState, char currentSymbol, unsigned **table, unsigned int *currentArrayPosition, char *comments) {
    State newState = table[currentState][getSymbolToken(currentSymbol)];

    if (currentState == startComment && newState == comment) {
        comments[*currentArrayPosition] = '/';
        comments[*currentArrayPosition + 1] = '*';
        *currentArrayPosition += 2;
    } else if (currentState == comment) {
        comments[*currentArrayPosition] = currentSymbol;
        ++(*currentArrayPosition);
    } else if (currentState == endComment && newState == notComment) {
        comments[*currentArrayPosition] = '/';
        comments[*currentArrayPosition + 1] = '\n';
        *currentArrayPosition += 2;
    }

    return newState;
}

// return -1 if file doesn't exist
// return 1 if not enough memory
// return 0 if all is ok
// return -2 if comment doesn't have end */
char* getCommentsFromFile(char *fileName, int *errorCode) {
    unsigned **table = getDFATable("matrix.txt", errorCode);
    if (*errorCode) {
        return NULL;
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        deleteMatrix(table);
        *errorCode = -1;
        return NULL;
    }

    unsigned int length = getCommentsLength(file, table, errorCode);
    if (*errorCode) {
        deleteMatrix(table);
        fclose(file);
        *errorCode = -2;

        return NULL;
    }

    char *commentsArray = calloc(length, sizeof(char));
    if (commentsArray == NULL) {
        deleteMatrix(table);
        fclose(file);
        *errorCode = 1;

        return NULL;
    }

    fseek(file, 0, SEEK_SET);

    unsigned int currentArrayPosition = 0;
    char currentSymbol = (char)fgetc(file);
    State currentState = notComment;

    while (currentSymbol != EOF) {
        currentState = move(currentState, currentSymbol, table, &currentArrayPosition, commentsArray);
        currentSymbol = (char)fgetc(file);
    }

    fclose(file);
    deleteMatrix(table);

    return commentsArray;
}