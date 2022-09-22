#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int substringCount(const char* substring, const char* string) {
    int containCount = 0;
    const unsigned int substringSize = strlen(substring);
    const unsigned int stringSize = strlen(string);

    if (stringSize < substringSize || stringSize < 1) {
        return 0;
    }

    for (int i = 0; substringSize + i <= stringSize; ++i) {
        bool contains = true;
        if (substring[0] == string[i]) {
            for (int j = 1; j < substringSize; ++j) {
                if (substring[j] != string[i + j]) {
                    contains = 0;
                    break;
                }
            }
            if (contains == 1) {
                ++containCount;
            }
        }
    }
    
    return containCount;
}

int main() {
    char string[100] = " "; 
    char substring[100] = " ";

    printf("Введите строку длиной не более 100 символов: ");
    scanf("%s", string);
    printf("Введите подстроку длиной не более 100 символов: ");
    scanf("%s", substring);
    printf("Количество вхождений подстроки в строку: %d", substringCount(substring, string));

    return 0;
}