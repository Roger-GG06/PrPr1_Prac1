#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"
#include "session.h"
#include "utils.h"

void printMenuPrincipal() {
    printf("Welcome to LS Minions Club :) What would you like to do today?\n");
    printf("\t1. Log in\n");
    printf("\t2. Register New Minion\n");
    printf("\t3. Shut down!\n");
    printf("Choose an option: ");
}

void printComu(){
    printf("\t1. Llistar eines\n");
    printf("\t2. Llistar tasques\n");
    printf("\t3. Creacio de tasques\n");
}

void printMenuMinion(UserType type){
    switch (type){
        case GRU:
            printf("\n=== GRU MENU ===\n");
            printComu();
            printf("\t0. Tancar Sessio"); 
            break;
        case MINION:
            printf("\n=== MINION MENU ===\n");
            printComu();
            printf("\t0. Tancar Sessio"); 
            break;
        case SUPERMINION:
            printf("\n=== SUPERMINION MENU ===\n");
            printComu();
            printf("\t0. Tancar Sessio"); 
            break;
        case MINION_ENG:
            printf("\n=== MINION ENGINYER MENU ===\n");
            printComu();
            printf("\t4. Consultar llistat d'eines creades\n");
            printf("\t5. Creacio d'una nova eina\n");
            printf("\t6. Creacio d'una nova peca\n");
            printf("\t7. Assignar peca a una eina\n");
            printf("\t8. Consultar temps treballat\n");
            printf("\t9. Consultar eines i peces dissenyades\n");
            printf("\t0. Tancar Sessio");    
            break;
        default:
            printf("ERROR");
            break;
    }
    
}

int main() {
    UserType loggedUser = NONE;
    user *users = NULL;
    int numUsers;
    int opcio = 0, opcioLogged = -1;
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
            opcioLogged = -1;
            while(opcioLogged != 0){
                printMenuMinion(loggedUser);
                printf("\n\nOption to choose: ");
                opcioLogged = leerInt(); 

                if(loggedUser != MINION_ENG){
                    if(opcioLogged < 0 || opcioLogged > 3){
                        opcioLogged = -1;
                        printf("Wrong Option (0-3)");
                    }
                }

                switch (opcioLogged) {
                    case 0:
                        printf("Tancant sessio...\n");
                        loggedUser = NONE;
                        break;
                    case 1:
                        printf("Llistar eines (not implemented yet)\n");
                        break;
                    case 2:
                        printf("Llistar tasques (not implemented yet)\n");
                        break;
                    case 3:
                        printf("Creacio de tasques (not implemented yet)\n");
                        break;
                    case 4:
                        printf("Opcio 4 (not implemented yet)\n");
                        break;
                    case 5:
                        printf("Opcio 5 (not implemented yet)\n");
                        break;
                    case 6:
                        printf("Opcio 6 (not implemented yet)\n");
                        break;
                    case 7:
                        printf("Opcio 7 (not implemented yet)\n");
                        break;
                    case 8:
                        printf("Opcio 8 (not implemented yet)\n");
                        break;
                    case 9:
                        printf("Opcio 9 (not implemented yet)\n");
                        break;
                    default:
                        printf("Wrong Option (0-9)");
                        break;
                }
            }
        }
    }

    return 0;
}