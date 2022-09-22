#include <stdio.h>

int main() {
    int const dimension = 10;
    int const maxTicketSum = 28;
    int luckyTickets = 0;
    int sumCount[maxTicketSum] = {0}; // если не ошибаюсь, то так работает только с нулем
    
    for (int firstNumber = 0; firstNumber < dimension; ++firstNumber) {
        for (int secondNumber = 0; secondNumber < dimension; ++secondNumber) {
            for (int thirdNumber = 0; thirdNumber < dimension; ++thirdNumber) {
                ++sumCount[firstNumber + secondNumber + thirdNumber];
            }
        }
    }
    for (int i = 0; i < maxTicketSum; ++i) {
        luckyTickets += sumCount[i] * sumCount[i];
    }
    
    printf("Количество счастливых билетов: %d \n", luckyTickets);

    return 0;
}
