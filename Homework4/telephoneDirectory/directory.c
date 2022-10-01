#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("telephoneNumbers.txt", "r");
    if (file == NULL) {
        file = fopen("telephoneNumber.txt", "w");
    }
    fclose(file);

    

    return 0;
}
