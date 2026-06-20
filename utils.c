#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

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

    input[strlen(input) - 1] = '\0';

    for (i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return -1;
        }
    }

    return atoi(input);
}

float leerFloat() {
    char input[MAX_STR];
    int i;
    int puntoDecimal = 0;
    
    if (fgets(input, MAX_STR, stdin) == NULL) {
        return -1.0f;
    }
    
    input[strlen(input) - 1] = '\0';
    
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '.') {
            if (puntoDecimal) {
                return -1.0f;
            }
            puntoDecimal = 1;
        } else if (!isdigit(input[i])) {
            return -1.0f;
        }
    }
    
    return atof(input);
}

int mostrarTypeDisponible(user *users, int numUsers, UserType type){
    int numMinion = 0;

    printf("\nMinions Disponibles:\n");
    for(int i = 0; i < numUsers; i++){
        if(users[i].type == type){
            numMinion++;
            printf("%d) %s\n", numMinion, users[i].user);
        }
    }
    return numMinion;
}

user retornarTypeDisponible(user *users, int numUsers, UserType type, int opcioEscollida){
    int numMinion = 0;
    user usuariNull = {0};

    for(int i = 0; i < numUsers; i++){
        if(users[i].type == type){
            numMinion++;
            if(numMinion == opcioEscollida){
                return users[i];
            }
        }
    }
    return usuariNull;
}

int comprovarHorari(char hora[MAX_STR]) {
    int hores, minuts;
    char separador;
    
    if (sscanf(hora, "%d%c%d", &hores, &separador, &minuts) == 3) {
        if (separador == ':') {
            if (hores >= 0 && hores <= 23 && minuts >= 0 && minuts <= 59) {
                return 1;
            }
        }
    }
    return 0;
}