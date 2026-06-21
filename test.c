#include <stdio.h>
#include <string.h>

#include "session.h"
#include "structs.h"
#include "tasques.h"
#include "utils.h"

int main(){
    user *users = NULL;
    users = malloc(MAX_USERS * sizeof(user));
    DateTime *primer, *segon;
    primer = createDateTime(20, 20, 20, 12, 2022);
    segon = createDateTime(10, 10, 10, 10, 2002);
	char name[100] = "gru";
	char password[100] = "gru123";

    strcpy(users[0].user, "gru");
    strcpy(users[0].password, "gru123");
    users[0].pin = 1111;
    users[0].type = GRU;
    strcpy(users[0].fruit, "NONE");


    printf("TEST FIND USERNAME");
    if(!findUserByUsername(users, 1, name)){
        printf("\nUSER FOUND, TEST CORRECT\n");
    } else {
        printf("\nUSER NOT FOUND\n");
    }

    printf("TEST VALIDATE PASSWORD");
    if(validatePassword(users[0], password)){
        printf("\nCORRECT PASSWORD\n");
    } else {
        printf("\nINCORRECT PASSWORD\n");
    }

    printf("TEST VALIDATE PIN");
    if(validatePin(users[0], 1111)){
        printf("\nCORRECT PIN\n");
    } else {
        printf("\nINCORRECT PIN\n");
    }

    printf("TEST VALIDATE HORARI USUARI");
    if(comprovarHorariUsuari(*primer, 10, *segon)){
        printf("\nCORRECT NO MATCH\n");
    } else {
        printf("\nINCORRECT THEY MATCH\n");
    }

	free(users);
    free(primer);
    free(segon);
}
