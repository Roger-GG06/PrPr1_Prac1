#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"

void leerString(char *string){
    fgets(string, MAX_STR, stdin);
    string[strlen(string) - 1] = '\0';
}

int leerInt() {
    char input[MAX_STR];
    int i;

    if (fgets(input, MAX_STR, stdin) == NULL) {
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