#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// mutate matrix from .txt file to .dot type code
// return -1 if adjacent matrix isn't square
// return -2 if no file with this name
// return 0 if all is ok
// return 1 if not enough memory
// return 2 if way distance less than zero
int getMatrixToDotFile(char *fileName) {
    FILE *graphFile = fopen("../graph.dot", "w");
    if (graphFile == NULL) {
        return 1;
    }

    FILE *matrixFile = fopen(fileName, "r");
    if (matrixFile == NULL) {
        fclose(graphFile);
        return -2;
    }

    fprintf(graphFile, "digraph Matrix {\n");

    unsigned int maxRow = 0;
    unsigned int currentRow = 1;
    unsigned int currentColumn = 1;

    while (!feof(matrixFile)) {
        unsigned int way = 0;
        int eofCheck = fscanf(matrixFile, "%u", &way);
        if (eofCheck == EOF) {
            fprintf(graphFile, "}");
            fclose(graphFile);
            fclose(matrixFile);

            return (currentRow == maxRow && currentColumn == maxRow + 1) ? 0 : -1;
        }
        if (eofCheck == 0) {
            fclose(graphFile);
            fclose(matrixFile);

            return 2;
        }

        if (way != 0) {
            fprintf(graphFile, "\t%u -> %u [label=%u];\n", currentRow, currentColumn, way);
            maxRow = maxRow > currentColumn ? maxRow : currentColumn;
        }

        eofCheck = fgetc(matrixFile);

        if (eofCheck == '\n') {
            ++currentRow;
            currentColumn = 0;
        } else if (eofCheck == EOF) {
            fprintf(graphFile, "}");
            fclose(graphFile);
            fclose(matrixFile);

            return (currentRow == maxRow && currentColumn == maxRow) ? 0 : -1;
        }

        ++currentColumn;
    }

    fprintf(graphFile, "}");

    fclose(graphFile);
    fclose(matrixFile);

    return currentRow == maxRow ? 0 : -1;
}

bool getMatrixToDotFileTest(void) {
    FILE *file = fopen("test.txt", "w");
    if (file == NULL) {
        return false;
    }

    fprintf(file, "0 1 1"
                  "\n1 0 0"
                  "\n0 1 0");
    fclose(file);

    getMatrixToDotFile("test.txt");

    file = fopen("../graph.dot", "r");
    char test[20] = {0};
    fscanf(file, "%[^\n]", test);
    fgetc(file);
    bool firstTest = !strcmp(test, "digraph Matrix {");
    fscanf(file, "%[^\n]", test);
    fgetc(file);
    bool secondTest = !strcmp(test, "\t1 -> 2 [label=1];");
    fscanf(file, "%[^\n]", test);
    fgetc(file);
    bool thirdTest = !strcmp(test, "\t1 -> 3 [label=1];");
    fscanf(file, "%[^\n]", test);
    fgetc(file);
    bool fourthTest = !strcmp(test, "\t2 -> 1 [label=1];");
    fscanf(file, "%[^\n]", test);
    fgetc(file);
    bool fifthTest = !strcmp(test, "\t3 -> 2 [label=1];");
    fscanf(file, "%[^\n]", test);
    bool sixthTest = !strcmp(test, "}");

    remove("test.txt");
    remove("../graph.dot");

    return firstTest && secondTest && thirdTest
            && fourthTest && fifthTest && sixthTest;
}

int main(int argc, char** argv) {
    if (argc == 3 && !strcmp(argv[2], "--test")) {
        if (!getMatrixToDotFileTest()) {
            printf("Tests Failed");
            return 1;
        }

        return 0;
    }

    if (argc == 1) {
        printf("No file input");
        return 1;
    }

    int errorCode = getMatrixToDotFile(argv[1]);
    switch (errorCode) {
        case 1: {
            printf("Not enough memory");
            return 1;
        }
        case -1: {
            printf("Adjacent matrix isn't square");
            return 0;
        }
        case -2: {
            printf("No file with this name");
            return 0;
        }
        case 2: {
            printf("Way distance less than zero");
            return 0;
        }
        default: {
            return 0;
        }
    }
}
