#include <stdio.h>
#include "binaryTree.h"
#include "binaryTreeTest.h"

#define MAX_STRING_SIZE 100

void choose(void) {
    printf("0 - exit\n");
    printf("1 - add value by token to dictionary. If token exists, change to new\n");
    printf("2 - get value by token\n");
    printf("3 - check for containing token in dictionary\n");
    printf("4 - delete token and corresponding value from dictionary\n");
}

int main() {
    if (!fullTest()) {
        printf("Tests Failed");
        return 1;
    }

    choose();
    Dictionary *dictionary = createDictionary();

    int option = 1;
    while (option != 0) {
        printf("Choose option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                printf("Input token: ");
                int token = 0;
                scanf("%d", &token);
                printf("Input value with length less than 100: ");
                char value[MAX_STRING_SIZE] = {0};
                scanf("%s", value);
                int errorCode = addWord(dictionary, token, value);
                if (errorCode) {
                    printf("Not enough memory");
                    return 1;
                }
                printf("Value successfully added \n");

                break;
            }
            case 2: {
                printf("Input token to get value of it: ");
                int token = 0;
                scanf("%d", &token);
                char *answer = getWord(dictionary, token);
                if (answer == NULL) {
                    printf("No value with this token in the dictionary \n");
                    break;
                }
                printf("Value of token %d is '%s' \n", token, answer);

                break;
            }
            case 3: {
                printf("Input token to check for its containing in the dictionary: ");
                int token = 0;
                scanf("%d", &token);
                printf("The token %d %s in the dictionary \n", token, isContain(dictionary, token)
                ? "is contained"
                : "isn't contained");

                break;
            }
            case 4: {
                printf("Input token to delete its and value from the dictionary: ");
                int token = 0;
                scanf("%d", &token);
                deleteWord(dictionary, token);
                printf("Deletion completed\n");

                break;
            }
            case 0: {
                break;
            }
            default: {
                printf("There is not option with this number, please, repeat input: \n");
                choose();

                break;
            }
        }
    }

    deleteTree(&dictionary);
        
    return 0;
}
