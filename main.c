#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utilsFun.h"
#include "structs.h"
#include "session.h"
#include "eines.h"
#include "tasques.h"
#include "piece.h"

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
}

void printMenuMinion(UserType type){
    switch (type){
        case GRU:
            printf("\n=== GRU MENU ===\n");
            printComu();
            printf("\t3. Creacio de tasques\n");
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
            printf("\t3. Consultar llistat d'eines creades\n");
            printf("\t4. Creacio d'una nova eina\n");
            printf("\t5. Creacio d'una nova peca\n");
            printf("\t6. Assignar peca a una eina\n");
            printf("\t7. Consultar temps treballat\n");
            printf("\t8. Consultar eines i peces dissenyades\n");
            printf("\t0. Tancar Sessio");    
            break;
        default:
            printf("ERROR");
            break;
    }
    
}

int main() {
    UserType loggedUser = NONE;
    int userPosition = -1;
    user *users = NULL;
    eina *eines = NULL;
    task *tasques = NULL;
    piece *pieces = NULL;

    int numUsers = 0, numEines = 0, numTasques = 0, numPieces = 0;
    int opcio = 0, opcioLogged = -1;
    users = malloc(MAX_USERS * sizeof(user));
    eines = malloc(MAX_EINES * sizeof(eina));
    tasques = malloc(MAX_TASKS * sizeof(task));
    pieces = malloc(MAX_PIECE * sizeof(piece));

    loadUsers(users, &numUsers);

    /*inicio un MIN_ENGINYER ja que no hi ha cap forma de crear-lo sino perque els MINIONS no 
    evolucionen en les funcionalitats comunes i, per tant, no podria provar les meves funcionalitats
    Users hardcodejats

    GRU: nom(gru) contrasenya(gru123) pin(1111)
    MINION: nom(min) contrasenya(min123) pin(2222)
    SUPERMINION: nom(sMin) contrasenya(sMin123) pin(3333)
    MINION_ENG: nom(minE) contrasenya(minE123) pin(4444)

    */
    
    if(numUsers < 4){
        initUsers(users, &numUsers); 
        saveUsers(users, numUsers);
    }
             
    
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
                    userPosition = login(users, numUsers);
                    if(userPosition == -1 ){
                        loggedUser = NONE;
                    } else {
                        loggedUser = users[userPosition].type;
                    }
                    break;
                case 2:
                    userPosition = registerUser(users, &numUsers);
                    if(userPosition == -1 ){
                        loggedUser = NONE;
                    } else {
                        loggedUser = users[userPosition].type;
                        saveUsers(users, numUsers);
                    }
                    break;
                case 3:
                    free(users);
                    printf("GoodBye!\n");
                    break;
                default:
                    printf("Wrong Option. Please choose 1, 2, or 3.\n");
                    break;
            }
        } else {
            opcioLogged = -1;
            loadEines(eines, &numEines);
            loadTasques(tasques, &numTasques);
            loadPieces(pieces, &numPieces);

            if(numPieces < 2){
                initPieces(pieces, &numPieces);
                savePieces(pieces, numPieces);
            }  

            if(numEines < 2){
                initEines(eines, &numEines, pieces, numPieces);
                saveEines(eines, numEines);
            }

            while(opcioLogged != 0){
                printMenuMinion(loggedUser);
                printf("\n\nOption to choose: ");
                opcioLogged = leerInt(); 

                switch(loggedUser) {                        
                    case MINION:
                        switch(opcioLogged) {
                            case 0:
                                free(eines);
                                free(pieces);
                                free(tasques);
                                loggedUser = NONE;
                                break;
                            case 1:
                                mostrarEinesACrear(eines, numEines);
                                break;
                            case 2:
                                mostrarTasquesPendents(tasques, numTasques);
                                break;
                            default:
                                printf("Wrong Option (0-2)\n");
                                break;
                        }
                        break;

                    case SUPERMINION:
                        switch(opcioLogged) {
                            case 0:
                                free(eines);
                                free(pieces);
                                free(tasques);
                                loggedUser = NONE;
                                break;
                            case 1:
                                mostrarEinesACrear(eines, numEines);
                                break;
                            case 2:
                                mostrarTasquesPendents(tasques, numTasques);
                                break;
                            default:
                                printf("Wrong Option (0-2)\n");
                                break;
                        }
                        break;
                    
                    case GRU:  
                        switch (opcioLogged) {
                            case CAS_IMPOSSIBLE:
                                break;
                            case 0:
                                free(eines);
                                free(pieces);
                                free(tasques);
                                loggedUser = NONE;
                                break;
                            case 1:
                                mostrarEinesACrear(eines, numEines);
                                break;
                            case 2:
                                mostrarTasquesPendents(tasques, numTasques);
                                break;
                            case 3:
                                crearNovaTasca(tasques, &numTasques, users, numUsers);
                                saveTasques(tasques, numTasques);
                                break;
                            default:
                                printf("Wrong Option (0-3)\n");
                                break;
                        }
                        break;
                    case MINION_ENG:
                        switch (opcioLogged) {
                            case 0:
                                free(eines);
                                free(pieces);
                                free(tasques);
                                loggedUser = NONE;
                                break;
                            case 1:
                                mostrarEinesACrear(eines, numEines);
                                break;
                            case 2:
                                mostrarTasquesPendents(tasques, numTasques);
                                break;
                            case 3:
                                mostrarEinesCreades(eines, numEines);
                                break;
                            case 4:
                                if(numPieces > 0){
                                    crearNovaEina(eines, &numEines, users, userPosition, pieces, numPieces);
                                    saveEines(eines, numEines);
                                } else {
                                    printf("There are no pieces to build a new tool.");
                                }
                                break;
                            case 5:
                                createNewPiece(pieces, &numPieces, users[userPosition].user);
                                savePieces(pieces, numPieces);
                                break;
                            case 6:
                                afegirPiece(pieces, numPieces, eines, numEines);
                                break;
                            case 7:
                                mostrarTempsTreballat(pieces, numPieces, eines, numEines, users[userPosition].user);
                                break;
                            case 8:
                                consultarPieceEinesDissenyades(pieces, numPieces, eines, numEines, users[userPosition].user, users, numUsers);
                                saveUsers(users, numUsers);
                                break;
                            default:
                                printf("Wrong Option (0-8)");
                                break;
                        }
                        break;
                    case NONE:
                        printf("Loggin Out...\n");
                        break;

                }
            }
        }
    }
    return 0;
}
