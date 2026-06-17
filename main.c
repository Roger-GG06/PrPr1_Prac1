#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"
#include "session.h"
#include "utils.h"

#define MAX_LENGTH 10

void printMenuPrincipal() {
    printf("Welcome to LS Minions Club :) What would you like to do today?\n");
    printf("\t1. Log in\n");
    printf("\t2. Register New Minion\n");
    printf("\t3. Shut down!\n");
    printf("Choose an option: ");
}


int main() {
    UserType loggedUser = NONE;
    user *users = NULL;
    int numUsers;
    int opcio = 0;
    users = malloc(MAX_USERS * sizeof(user));

    loadUsers(users, &numUsers);
    printf("%s", users[0].user);
    while (opcio != 3) {
        if(loggedUser == NONE){
            printMenuPrincipal();
            opcio = leerInt();

            if (opcio == -1) {
                printf("Invalid input. Please enter a number (1-3).\n");
                continue;
            }

            switch (opcio) {
                case 1:
                    loggedUser = login(users, numUsers);
                    break;
                case 2:
                    loggedUser = registerUser(users, &numUsers);
                    saveUsers(users, numUsers);
                    break;
                case 3:
                    printf("GoodBye!\n");
                    break;
                default:
                    printf("Wrong Option. Please choose 1, 2, or 3.\n");
                    break;
            }
        } else {
            switch (loggedUser){
                case GRU:
                    printf("GRU coming soon...\n");
                    loggedUser = NONE;
                    break;
                case MINION:
                    printf("MINION coming soon...\n");
                    loggedUser = NONE;
                    break;
                case SUPERMINION:
                    printf("SUPERMINION coming soon...\n");
                    loggedUser = NONE;
                    break;
                case MINION_ENG:
                    printf("MINION_ENG coming soon...\n");
                    loggedUser = NONE;
                    break;
                default:
                    printf("Wrong Log\n");
                    loggedUser = NONE;
                    break;
            }
        }
    }

    return 0;
}