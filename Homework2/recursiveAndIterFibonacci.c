#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned long int recursiveFibonacci(unsigned number) {
    return ((number <= 1) ? (number) : (recursiveFibonacci(number - 1) + recursiveFibonacci(number - 2)));
}

unsigned long int iterationFibonacci(unsigned number) {
    if (number == 0) {
        return 0;
    }
    unsigned long int back = 0;
    unsigned long int next = 1;
    
    for (int i = 1; i < number; ++i) {
        unsigned long int temp = next;
        next += back;
        back = temp;
    }
    
    return next;
}

bool correctTestIteration(void) {
    return iterationFibonacci(0) == 0 && iterationFibonacci(1) == 1 && iterationFibonacci(10) == 55 && iterationFibonacci(25) == 75025;
}

bool correctTestRecursion(void) {
    return recursiveFibonacci(0) == 0 && recursiveFibonacci(1) == 1 && recursiveFibonacci(10) == 55 && recursiveFibonacci(25) == 75025;
}

int main() {
    if (!correctTestIteration()) {
        printf("Iteration tests failed");
        return 1;
    }
    if (!correctTestRecursion()) {
        printf("Recursion tests failed");
        return 1;
    }
    
    /*printf("Enter non-negative number: ");
    int number = 0;
    scanf("%d", &number);
    while (number < 0) {
        printf("It's negative number, please, repeat enter: ");
        scanf("%d", &number);
    }
    printf("Recursion method out: %lu \n", recursiveFibonacci((unsigned)(number)));
    printf("Iteration method out: %lu \n", iterationFibonacci((unsigned)(number)));*/
    
    unsigned timeDifferent = 1;
    int currentNumber = 0;
    
    while (timeDifferent < 5) {
        clock_t start_t = clock();
        recursiveFibonacci(currentNumber);
        clock_t end_t = clock();
        double recursionClock = (end_t - start_t) / CLOCKS_PER_SEC;
        
        start_t = clock();
        iterationFibonacci(currentNumber);
        end_t = clock();
        double iterationTime = (end_t - start_t) / CLOCKS_PER_SEC;
        
        if (recursionClock - iterationTime > (timeDifferent)) {
            printf("At number %d, recursion method speed in %g seconds slower than iterative \n", currentNumber, recursionClock - iterationTime);
            ++timeDifferent;
        }
        ++currentNumber;
    }
    
    return 0;
}
