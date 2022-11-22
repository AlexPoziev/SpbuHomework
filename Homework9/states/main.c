#include "states.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    Cities *cities = createCities();
    States *states = createStates();

    getDataFromFile("test.txt", cities, states);

    return 0;
}
