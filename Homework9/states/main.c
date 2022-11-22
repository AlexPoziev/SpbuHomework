#include "states.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    Cities *cities = createCities();
    if (cities == NULL) {
        printf("Not enough memory");
        return 1;
    }

    States *states = createStates();
    if (states == NULL) {
        printf("Not enough memory");
        deleteCities(&cities);

        return 1;
    }

    printf("Input file name with length less than 20 symbols: ");
    char fileName[20] = {0};
    scanf("%s", fileName);

    int errorCode = getDataFromFile(fileName, cities, states);
    if (errorCode == 2) {
        printf("Not enough data in the file");
        deleteCities(&cities);
        deleteStates(&states);

        return 0;
    }
    if (errorCode == 1) {
        printf("Not enough memory");
        deleteCities(&cities);
        deleteStates(&states);

        return 1;
    }
    if (errorCode == -1) {
        printf("File with this name doesn't exist");
        deleteCities(&cities);
        deleteStates(&states);

        return 0;
    }

    errorCode = divideCities(cities, states);
    if (errorCode == -1) {
        printf("Some city doesn't has any roads to it");
        deleteCities(&cities);
        deleteStates(&states);

        return 0;
    }

    printStates(states);

    deleteCities(&cities);
    deleteStates(&states);

    return 0;
}
