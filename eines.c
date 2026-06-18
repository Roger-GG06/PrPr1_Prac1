#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "eines.h"

void loadEines(eina *eines, int *numEines) {
    FILE *fp = fopen(EINES_FILE, "r");
    char line[MAX_STR * 4];
    
    *numEines = 0;
    
    if (fp == NULL) {
        printf("\nERROR: cannot read eina file\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strlen(line) - 1] = '\0';
        
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
        

        if (camp == 4) creacioTemp[j] = '\0';
        
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