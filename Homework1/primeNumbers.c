#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void primeNumbersPrinter(int limit) { // решето Эратосфена
    bool *isPrime = (bool*)malloc((limit + 1) * sizeof(bool));
    if (isPrime == NULL){
        printf("Проводятся технические работы, воспользуйтесь программой позже");
        return;
    }

    for (int initializer = 0; initializer <= limit; ++initializer) {
        isPrime[initializer] = true;
    }

    for (int i = 2; i * i < limit; ++i) {
        if (isPrime[i] == 1) {
            for (int falser = i * i; falser <= limit; falser += i) {
                isPrime[falser] = false;
            }
        }
    }
    for (int answer = 2; answer <= limit; ++answer) {
        if (isPrime[answer] == 1) {
            printf("%d ", answer);
        }
    }

    free(isPrime);
}

int main() {
    int limit = 0;

    printf("Ввведите границу: ");
    scanf("%d", &limit);
    printf("Все простые числа до границы: ");
    primeNumbersPrinter(limit);

    return 0;
}