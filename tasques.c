#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tasques.h"

void loadTasques(task *tasques, int *numTasques) {
    FILE *fp = fopen(TASQUES_FILE, "r");
    char line[MAX_LENGTH * 2];
    
    *numTasques = 0;
    
    if (fp == NULL) {
        printf("\nERROR: cannot read tasques file\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        char pendentTemp[MAX_STR], nomTemp[MAX_STR], usuariTemp[MAX_STR];
        char horaTemp[MAX_STR], duradaTemp[MAX_STR], descripcioTemp[MAX_STR];
        
        int i = 0, j = 0;
        int camp = 0;
        
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ';') {
                if (camp == 0) pendentTemp[j] = '\0';
                else if (camp == 1) nomTemp[j] = '\0';
                else if (camp == 2) usuariTemp[j] = '\0';
                else if (camp == 3) horaTemp[j] = '\0';
                else if (camp == 4) duradaTemp[j] = '\0';
                
                camp++;
                j = 0;
            } else {
                if (camp == 0) pendentTemp[j] = line[i];
                else if (camp == 1) nomTemp[j] = line[i];
                else if (camp == 2) usuariTemp[j] = line[i];
                else if (camp == 3) horaTemp[j] = line[i];
                else if (camp == 4) duradaTemp[j] = line[i];
                else if (camp == 5) descripcioTemp[j] = line[i];
                j++;
            }
        }
        
        if (camp == 5) descripcioTemp[j] = '\0';
        
        // Asignar valores
        if (strcmp(pendentTemp, "PENDENT") == 0) {
            tasques[*numTasques].pendent = PENDENT;
        } else if (strcmp(pendentTemp, "EN_CURS") == 0) {
            tasques[*numTasques].pendent = EN_CURS;
        } else if (strcmp(pendentTemp, "ACABAT") == 0) {
            tasques[*numTasques].pendent = ACABAT;
        } else {
            tasques[*numTasques].pendent = PENDENT;
        }
        
        strcpy(tasques[*numTasques].nom, nomTemp);
        strcpy(tasques[*numTasques].usuari, usuariTemp);
        strcpy(tasques[*numTasques].hora, horaTemp);
        tasques[*numTasques].durada = atof(duradaTemp);
        strcpy(tasques[*numTasques].descripcio, descripcioTemp);
        
        (*numTasques)++;
    }
    
    fclose(fp);
}
