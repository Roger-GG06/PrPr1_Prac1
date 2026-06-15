#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 10

void printMenuPrincipal() {
    printf("Welcome to LS Minions Club :) What would you like to do today?\n");
    printf("\t1. Log in\n");
    printf("\t2. Register New Minion\n");
    printf("\t3. Shut down!\n");
    printf("Choose an option: ");
}

int leerInt() {
    char input[MAX_LENGTH];
    int i;

    if (fgets(input, MAX_LENGTH, stdin) == NULL) {
        return -1;
    }

    input[strcspn(input, "\n")] = '\0';

    for (i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return -1;
        }
    }

    return atoi(input);
}

int main() {
    int opcio = 0;

    while (opcio != 3) {
        printMenuPrincipal();

        opcio = leerInt();

        if (opcio == -1) {
            printf("Invalid input. Please enter a number (1-3).\n");
            continue;
        }

        switch (opcio) {
            case 1:
                printf("Login functionality coming soon...\n");
                break;
            case 2:
                printf("Register functionality coming soon...\n");
                break;
            case 3:
                printf("GoodBye!\n");
                break;
            default:
                printf("Wrong Option. Please choose 1, 2, or 3.\n");
                break;
        }
    }

    return 0;
}