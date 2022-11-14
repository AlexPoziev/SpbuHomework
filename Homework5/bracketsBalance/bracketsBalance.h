#pragma once

#include <stdbool.h>

// check bracket balance in string
bool bracketsBalance(char *string, unsigned long size, int *errorCode);

// correct test for bracketsBalance
bool correctTest(void);

// incorrect test for bracketsBalance
bool incorrectTest(void);

// just append two test for bracketsBalance
bool bracketsBalanceTest(void);