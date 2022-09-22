#include <stdio.h>
#include <string.h>

const char* parenthesisCheck(unsigned long stringSize, const char* string) {//Xcode почему-то не ругается на const char* :(
    int parenthesisCount = 0;
    
    if (stringSize == 1 && string[0] == '\n') {
        return "Верное";
    }

    for (int i = 0; i < stringSize; ++i) {
        if (string[i] == '('){
            ++parenthesisCount;
        } else {
            --parenthesisCount;
            if (parenthesisCount < 0) return "Неверное";
        }
    }
    
    return parenthesisCount != 0 ? "Неверное" : "Верное";
}

int main() {
    char string[100];

    printf("Введите строку, состоящую из круглых скобок, длиною не более 100 символов, для проверки правильности их размещения: ");
    fgets(string, sizeof string, stdin);
    printf("Размещение строк: %s \n", parenthesisCheck(strlen(string) - 1, string));

    return 0;
}