#include <stdio.h>

// mutate matrix from .txt file to .dot type code
// return -1 if adjacent matrix isn't square
// return -2 if no file with this name
// return 0 if all is ok
int getMatrixToDotFile(char *fileName) {
    FILE *graphFile = fopen("../graph.dot", "w");
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
            fclose(graphFile);
            fclose(matrixFile);
            fprintf(graphFile, "}");

            return currentRow == maxRow ? 0 : -1;

        }

        if (way != 0) {
            fprintf(graphFile, "\t%u -> %u;\n", currentRow, currentColumn);
            maxRow = maxRow > currentColumn ? maxRow : currentColumn;
        }

        ++currentColumn;

        if (fgetc(matrixFile) == '\n') {
            ++currentRow;
            currentColumn = 1;
        }
    }

    fprintf(graphFile, "}");

    fclose(graphFile);
    fclose(matrixFile);

    return currentRow == maxRow ? 0 : -1;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        return 1;
    }

    int errorCode = getMatrixToDotFile(argv[1]);
    if (errorCode == -1) {
        printf("Adjacent matrix isn't square");
        return 1;
    }
    if (errorCode == -2) {
        printf("No file with this name");
        return -1;
    }

    return 0;
}
