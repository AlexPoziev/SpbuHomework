#include <stdio.h>
#include <stdlib.h>

void test(FILE *file) {
    char c = getc(file);
    c = getc(file);
    if (c == 'c') {
        ungetc('c', file);
    }
}

int main() {
    FILE *file = fopen("test.txt", "r");
    char check[20] = {0};
    scanf("%[^d]", check);
    printf("%s", check);

    return 0;
}
