#include "stackTest.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool pushTest(void) {
    IntStack *intHead = NULL;
    DoubleStack *doubleHead = NULL;
    const double delta = 0.0001;

    pushInt(&intHead, 10);
    pushInt(&intHead, 20);

    pushDouble(&doubleHead, 10.0);
    pushDouble(&doubleHead, 20.0);

    return intHead->value == 20 && intHead->next->value == 10 && (doubleHead->value - 20.0) < delta
    && (doubleHead->next->value - 20.0) < delta;
}

bool isEmptyTest(void) {
    IntStack *intHead = NULL;
    DoubleStack *doubleHead = NULL;

    pushInt(&intHead, 10);
    bool checkInt = isIntEmpty(intHead);
    clearIntStack(&intHead);

    pushDouble(&doubleHead, 10);
    bool checkDouble = isDoubleEmpty(doubleHead);
    clearDoubleStack(&doubleHead);

    return isIntEmpty(intHead) && (isDoubleEmpty(doubleHead)) && !checkDouble && !checkInt;
}

bool popTest(void) {
    IntStack *intHead = NULL;
    DoubleStack *doubleHead = NULL;
    const double delta = 0.0001;
    int errorCodeTrue = 0;
    int errorCodeInt = 0;
    int errorCodeDouble = 0;


    pushInt(&intHead, 10);
    int intCheckFirst = popInt(&intHead, &errorCodeTrue);
    popInt(&intHead, &errorCodeInt);

    pushDouble(&doubleHead, 10.0);
    double doubleCheckFirst = popDouble(&doubleHead, &errorCodeTrue);
    popInt(&intHead, &errorCodeDouble);

    return (intCheckFirst == 10 && !errorCodeTrue && errorCodeInt == -1 && errorCodeDouble == -1
    && (doubleCheckFirst - 10.0 < delta) && isDoubleEmpty(doubleHead) && isIntEmpty(intHead));
}

bool clearStackTest(void) {
    IntStack *intHead = NULL;
    DoubleStack *doubleHead = NULL;

    pushDouble(&doubleHead, 10.0);
    pushDouble(&doubleHead, 10.0);
    pushInt(&intHead, 10);
    pushInt(&intHead, 10);

    clearDoubleStack(&doubleHead);
    clearIntStack(&intHead);

    return isIntEmpty(intHead) && isDoubleEmpty(doubleHead);
}

bool stackTest(void) {
    return pushTest() && popTest() && clearStackTest() && isEmptyTest();
}