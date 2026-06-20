#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "eines.h"

void loadEines(eina *eines, int *numEines) {
    FILE *fp = fopen(EINES_FILE, "r");
    char line[MAX_LENGTH * 2];
    
    *numEines = 0;
    
    if (fp == NULL) {
        printf("\nERROR: cannot read eina file\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        char *token = strtok(line, ";");
        int camp = 0;
        
        eina *e = &eines[*numEines];
        e->numPieces = 0;
        for (int p = 0; p < MAX_PIECE_PER_EINA; p++) {
            e->pieces[p][0] = '\0';
        }
        
        while (token != NULL) {
            switch (camp) {
                case 0:
                    strcpy(e->nom, token);
                    break;
                case 1:
                    strcpy(e->type, token);
                    break;
                case 2: 
                    strcpy(e->descripcio, token);
                    break;
                case 3:
                    e->quantity = atoi(token);
                    break;
                case 4: 
                    if (strcmp(token, "PENDENT") == 0) e->creacio = PENDENT;
                    else if (strcmp(token, "EN_CURS") == 0) e->creacio = EN_CURS;
                    else if (strcmp(token, "ACABAT") == 0) e->creacio = ACABAT;
                    else e->creacio = PENDENT;
                    break;
                case 5:
                    e->numPieces = atoi(token);
                    break;
                default: 
                    if (camp - 6 < MAX_PIECE_PER_EINA) {
                        strcpy(e->pieces[camp - 6], token);
                    }
                    break;
            }
            camp++;
            token = strtok(NULL, ";");
        }
        
        (*numEines)++;
    }
    
    fclose(fp);
}  

void mostrarEinesACrear(eina *eines, int numEines) {
    int einesMostrades = 0;
    if (numEines == 0) {
        printf("\nNo hi ha eines disponibles.\n");
        return;
    }
    
    printf("\n\t\t=== TOOLS IN PROCESS ===\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(" Name\t\t\t| Type\t\t\t| Quantity  | State    | Pieces \n");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < numEines; i++) {
        char estatStr[MAX_STR];
        int mostrar = 1;
        switch (eines[i].creacio) {
            case PENDENT:   
                strcpy(estatStr, "PENDENT"); 
                break;
            case EN_CURS:  
                strcpy(estatStr, "EN CURS"); 
                break;
            case ACABAT:      
                mostrar = 0;
                break;
            default:
                strcpy(estatStr, "DESCONEGUT");           
                break;
        }
        if(mostrar){
            printf("%-23s | %-21s | %-9d | %-8s | ", eines[i].nom, eines[i].type, eines[i].quantity, estatStr);
            for(int j = 0; j < eines[i].numPieces; j++){
                printf("%s, ", eines[i].pieces[j]);
            }
            printf("\n");
            einesMostrades++;
        }  

    }
    if(einesMostrades == 0){
        printf("Totes les eines estan acabades.\n");
    }
    printf("--------------------------------------------------------------------------------\n");
}

void mostrarEinesCreades(eina *eines, int numEines) {
    int einesMostrades = 0;
    if (numEines == 0) {
        printf("\nNo hi ha eines disponibles.\n");
        return;
    }
    
    printf("\n\t\t=== FINISHED TOOLS ===\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(" Name\t\t\t| Type\t\t\t| Quantity  | State    | Pieces \n");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < numEines; i++) {
        char estatStr[MAX_STR];
        int mostrar = 1;
        switch (eines[i].creacio) {
            case PENDENT:   
                mostrar = 0; 
                break;
            case EN_CURS:
                mostrar = 0;  
                break;
            case ACABAT:      
                strcpy(estatStr, "FINISHED"); 
                break;
            default:
                strcpy(estatStr, "DESCONEGUT");           
                break;
        }
        if(mostrar){
            printf("%-23s | %-21s | %-9d | %-8s | ", eines[i].nom, eines[i].type, eines[i].quantity, estatStr);
            for(int j = 0; j < eines[i].numPieces; j++){
                printf("%s, ", eines[i].pieces[j]);
            }
            printf("\n");
            einesMostrades++;
        }  

    }
    if(einesMostrades == 0){
        printf("There are no tools finished yet\n");
    }
    printf("--------------------------------------------------------------------------------\n");
}

void crearNovaEina(eina *eines, int *numEines, user *usuari, piece *pieces, int numPieces){
    eina newEina;
    char name[MAX_STR], type[MAX_STR], description[MAX_LENGTH], namePiece[MAX_STR], creacio[MAX_STR];
    int pieceEscollida, durada;
    int posicioPiece = 0;
    int end = 0;

    printf("What is the name of the new tool? ");
    leerString(name);

    printf("What type of tool it is? ");
    leerString(type);

    printf("Make a brief description of the tool: ");
    leerString(description);

    while(!end){
        showPieces(pieces, numPieces);
        printf("0) No more pieces.\n");
        printf("Choose a piece: ");
        pieceEscollida = leerInt();
        if(numPieces + 1 < pieceEscollida || pieceEscollida < 0){
            printf("Ha de ser del 0 al %d\n", numPieces + 1);
        } else {
            if(pieceEscollida != 0){
                getPiece(pieces, pieceEscollida, namePiece);
                strcpy(newEina.pieces[posicioPiece], namePiece);
                posicioPiece++;
            } else {
                if(!posicioPiece){
                    printf("You must choose at least 1 piece.\n");
                } else {
                    end = 1;
                }
            }
        }
    }

    printf("How long did it take you (in minutes)? ");
    durada = leerInt();

    printf("When did u started? This format -> (xx:xx) : ");
    leerString(creacio);

    if(!comprovarHorari(creacio)){
        printf("Wrong format it has to be: (xx:xx) ");
        return;
    }

    strcpy(newEina.descripcio, description);
    strcpy(newEina.nom, name);
    newEina.numPieces = numPieces;
    strcpy(newEina.type, type);

}
