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
        
        char nomTemp[MAX_STR], typeTemp[MAX_STR], descripcioTemp[MAX_STR];
        char quantityTemp[MAX_STR], creacioTemp[MAX_STR];
        
        int i = 0, j = 0;
        int camp = 0;
        
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ';') {
                if (camp == 0) nomTemp[j] = '\0';
                else if (camp == 1) typeTemp[j] = '\0';
                else if (camp == 2) descripcioTemp[j] = '\0';
                else if (camp == 3) quantityTemp[j] = '\0';
                
                camp++;
                j = 0;
            } else {
                if (camp == 0) nomTemp[j] = line[i];
                else if (camp == 1) typeTemp[j] = line[i];
                else if (camp == 2) descripcioTemp[j] = line[i];
                else if (camp == 3) quantityTemp[j] = line[i];
                else if (camp == 4) creacioTemp[j] = line[i];
                j++;
            }
        }
        
        if (camp == 4)creacioTemp[j] = '\0';

        strcpy(eines[*numEines].nom, nomTemp);
        strcpy(eines[*numEines].type, typeTemp);
        strcpy(eines[*numEines].descripcio, descripcioTemp);
        eines[*numEines].quantity = atoi(quantityTemp);
        

        if (strcmp(creacioTemp, "PENDENT") == 0) {
            eines[*numEines].creacio = PENDENT;
        } else if (strcmp(creacioTemp, "EN_CURS") == 0) {
            eines[*numEines].creacio = EN_CURS;
        } else if (strcmp(creacioTemp, "ACABAT") == 0) {
            eines[*numEines].creacio = ACABAT;
        } else {
            eines[*numEines].creacio = PENDENT;
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
    printf("---------------------------------------------------------------------\n");
    printf(" Name\t\t\t| Type\t\t\t| Quantity  | State\n");
    printf("---------------------------------------------------------------------\n");
    
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
            printf("%-24s | %-20s | %-9d | %s\n", eines[i].nom, eines[i].type, eines[i].quantity, estatStr);
            einesMostrades++;
        }  

    }
    if(einesMostrades == 0){
        printf("Totes les eines estan acabades.\n");
    }
    printf("---------------------------------------------------------------------\n");
}

void mostrarEinesCreades(eina *eines, int numEines) {
    int einesMostrades = 0;
    if (numEines == 0) {
        printf("\nNo hi ha eines disponibles.\n");
        return;
    }
    
    printf("\n\t\t=== FINISHED TOOLS ===\n");
    printf("---------------------------------------------------------------------\n");
    printf(" Name\t\t\t| Type\t\t\t| Quantity  | State\n");
    printf("---------------------------------------------------------------------\n");
    
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
            printf("%-24s | %-20s | %-9d | %s\n", eines[i].nom, eines[i].type, eines[i].quantity, estatStr);
            einesMostrades++;
        }  

    }
    if(einesMostrades == 0){
        printf("There are no tools finished yet\n");
    }
    printf("---------------------------------------------------------------------\n");
}

