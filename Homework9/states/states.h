#pragma once

#include <stdbool.h>


typedef struct Cities Cities;

// states
typedef struct States States;

// allocate memory for State
// need to check for NULL
States* createStates(void);

// allocate memory for Cities
// need to check for NULL
Cities* createCities(void);

// get data from file and create roads between cities and create states with only capitals
// return 2 if not enough data in the file
// return 1 if not enough memory
// return -1 if no file with this name
// return 0 if all is ok
int getDataFromFile(char *fileName, Cities *cities, States *states);

// i dont know what will return maybe nothing
// divide cities between states
int divideCities(Cities *cities, States *states);

// print number of state and numbers of cities in its own
void printStates(States *states);

// delete states and clear memory
void deleteStates(States **states);

// delete road and clear memory
void deleteRoads(Cities **roads);

// get from file info about cities and state and divide it between themselves
// print number of state and all cities in its own
// return 0 if all is ok
// return 1 if not enough memory
// return -1 idk at that moment
int states(char *fileName);