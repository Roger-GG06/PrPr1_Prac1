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
        e->temps = 0;
        for (int p = 0; p < MAX_PIECE_PER_EINA; p++) {
            e->pieces[p][0] = '\0';
        }
        
        while (token != NULL) {
            switch (camp) {
                case 0:  
                    strcpy(e->nom, token);
                    break;
                case 1: 
                    strcpy(e->creador, token);
                    break;
                case 2:
                    strcpy(e->type, token);
                    break;
                case 3:
                    strcpy(e->descripcio, token);
                    break;
                case 4: 
                    e->quantity = atoi(token);
                    break;
                case 5:
                    if (strcmp(token, "PENDENT") == 0) e->creacio = PENDENT;
                    else if (strcmp(token, "EN_CURS") == 0) e->creacio = EN_CURS;
                    else if (strcmp(token, "ACABAT") == 0) e->creacio = ACABAT;
                    else e->creacio = PENDENT;
                    break;
                case 6:
                    e->temps = atoi(token);
                    break;
                case 7: 
                    e->numPieces = atoi(token);
                    break;
                default: 
                    if (camp - 8 < MAX_PIECE_PER_EINA) {
                        strcpy(e->pieces[camp - 8], token);
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


void saveEines(eina *eines, int numEines) {
    FILE *fp = fopen(EINES_FILE, "w");
    
    if (fp == NULL) {
        printf("\nERROR: cannot write eina file\n");
        return;
    }
    
    for (int i = 0; i < numEines; i++) {
        const char *estatStr;
        
        switch (eines[i].creacio) {
            case PENDENT:   estatStr = "PENDENT"; break;
            case EN_CURS:   estatStr = "EN_CURS"; break;
            case ACABAT:    estatStr = "ACABAT"; break;
            default:        estatStr = "PENDENT"; break;
        }
        
        fprintf(fp, "%s;%s;%s;%s;%d;%s;%d;%d", eines[i].nom, eines[i].creador, eines[i].type, eines[i].descripcio, eines[i].quantity, estatStr, eines[i].temps, eines[i].numPieces);
        
        for (int p = 0; p < eines[i].numPieces; p++) {
            fprintf(fp, ";%s", eines[i].pieces[p]);
        }
        
        fprintf(fp, "\n");
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

void crearNovaEina(eina *eines, int *numEines, user *usuaris, int posicioUsuari, piece *pieces, int numPieces){
    eina newEina;
    char name[MAX_STR], type[MAX_STR], description[MAX_LENGTH], namePiece[MAX_STR];
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
        printf("0) No more pieces.\n\n");
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


    newEina.creacio = ACABAT;
    strcpy(newEina.descripcio, description);
    strcpy(newEina.nom, name);

    newEina.numPieces = posicioPiece;
    strcpy(newEina.type, type);
    strcpy(newEina.creador, usuaris[posicioUsuari].user);
    newEina.quantity = 1;
    newEina.temps = durada;

    eines[(*numEines)] = newEina;
    (*numEines)++;

}

void showTools(eina *eines, int numEines){
    printf("\n=== TOOLS ===\n");
    for(int i = 0; i < numEines; i++){
        char estatStr[MAX_STR];
        
        switch (eines[i].creacio) {
            case PENDENT:   strcpy(estatStr, "PENDENT"); break;
            case EN_CURS:   strcpy(estatStr, "EN CURS"); break;
            case ACABAT:    strcpy(estatStr, "ACABAT"); break;
            default:        strcpy(estatStr, "DESCONEGUT"); break;
        }
        
        printf("%d) %s - %s (Creador: %s)\n", i + 1, eines[i].nom, estatStr, eines[i].creador);
    }
}


void afegirPiece(piece *pieces, int numPiece, eina *eines, int numEines){
    char pieceE[MAX_STR] = {0};
    int pieceEscollida = 0, einaEscollida = 0;
    int numPieceEina = 0;

    showPieces(pieces, numPiece);
    
    printf("Which piece do you want to add? ");
    pieceEscollida = leerInt();
    
    getPiece(pieces, pieceEscollida, pieceE);

    showTools(eines, numEines);
    
    printf("To which tool do you want to add it? ");
    einaEscollida = leerInt();

    if (einaEscollida < 1 || einaEscollida > numEines) {
        printf("The tools are between 1 - %d", numEines);
        return;
    }

    numPieceEina = eines[einaEscollida - 1].numPieces;

    printf("[DEBUG] einaEscollida = %s\n", eines[einaEscollida - 1].nom);
    printf("[DEBUG] numPieceEina (antes de añadir) = %d\n", numPieceEina);
    printf("%s;%s;%s;%s;%d;%d", eines[einaEscollida - 1].nom, eines[einaEscollida - 1].creador, eines[einaEscollida - 1].type, eines[einaEscollida - 1].descripcio, eines[einaEscollida - 1].quantity, eines[einaEscollida - 1].numPieces);

    if (numPieceEina >= MAX_PIECE_PER_EINA) {
        printf("Maximum pieces for tool reached (16 pieces)");
        return;
    }

    strcpy(eines[einaEscollida - 1].pieces[numPieceEina], pieceE);
    eines[einaEscollida - 1].numPieces++;
    
    saveEines(eines, numEines);
}

void mostrarTempsTreballat(piece *pieces, int numPiece, eina *eines, int numEines, char user[MAX_STR]){
    int totalTempsPieces = 0, totalTempsEines = 0;
    int trobat = 0;
    
    for (int i = 0; i < numPiece; i++) {
        if (strcmp(pieces[i].creador, user) == 0) {
            printf("  %s: %d minuts\n", pieces[i].nom, pieces[i].durada);
            totalTempsPieces += pieces[i].durada;
            trobat = 1;
        }
    }

    for (int i = 0; i < numEines; i++) {
        if (strcmp(eines[i].creador, user) == 0) {
            printf("  %s: %d minuts\n", eines[i].nom, eines[i].temps);
            totalTempsEines += eines[i].temps;
            trobat = 1;
        }
    }

    if (trobat) {
        printf("\n--- TOTAL ---\n");
        printf("  Total temps treballat: %d minuts\n", totalTempsPieces + totalTempsEines);
    } else {
        printf("\nNo has creat cap peça ni eina.\n");
    }

}