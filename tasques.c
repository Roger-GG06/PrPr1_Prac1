#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tasques.h"

int parseTimeToInt(char horari[MAX_STR]){
    int resultat = 0;
    int multiplicador = 600;
    int size = strlen(horari);
    for(int i = 0; i < size; i++){
        if(horari[i] == ':'){
            multiplicador = 10;
        } else if (horari[i] >= '0' && horari[i] <= '9'){
            resultat = (horari[i] - '0') * multiplicador;
            multiplicador = multiplicador / 10;
        }
    }

    return resultat;
}

int comprovarHorariUsuari(int durada,char hora[MAX_STR], char novaHora[MAX_STR]){
    int horaMin = parseTimeToInt(hora);
    int novaHoraMin = parseTimeToInt(novaHora);

    if(novaHoraMin >= horaMin && novaHoraMin <= horaMin + durada){
        return 0;
    } 

    return 1;
}

int comprovatTotesTasquesHorari(task *tasques, int numTasques, char name[MAX_STR], char novaHora[MAX_STR]){
    for(int i = 0; i < numTasques; i++){
        if(strcmp(name, tasques[i].usuari) == 0){
            if(!comprovarHorariUsuari(tasques[i].durada, tasques[i].hora, novaHora)){
                return 0;
            }
        }
    }
    return 1;
}

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

void mostrarTasquesPendents(task *tasques, int numTasques) {
    int tasquesMostrades = 0;
    
    if (numTasques == 0) {
        printf("\nNo hi ha tasques disponibles.\n");
        return;
    }
    
    printf("\n\t\t=== LLISTAT DE TASQUES PENDENTS ===\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Estat\t\t | Nom\t\t\t\t | Usuari\t\t | Hora\t | Durada | Descripcio\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < numTasques; i++) {
        char estatStr[MAX_STR];
        int mostrar = 1;
        
        switch (tasques[i].pendent) {
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
        
        if (mostrar) {
            printf("%-15s | %-30s | %-20s | %-5s | %-7.1f | %s\n", 
                   estatStr, 
                   tasques[i].nom, 
                   tasques[i].usuari, 
                   tasques[i].hora, 
                   tasques[i].durada, 
                   tasques[i].descripcio);
            tasquesMostrades++;
        }
    }
    
    if (tasquesMostrades == 0) {
        printf("Totes les tasques estan acabades.\n");
    }
    printf("------------------------------------------------------------------------------------------------------\n");
}

void crearNovaTasca(task *tasques, int *numTasques, user *users, int numUsers){
    int tipusInput;
    int usersAEscollir = 0, userEscollit = 0;
    float duration = 0.0f;
    char horari[MAX_STR], descripition[MAX_LENGTH], nomTask[MAX_STR];
    UserType typeTask = NONE;
    user userTriat = {0};
    task newTask = {0};
    
    printf("What is the name of the task: ");
    leerString(nomTask);

    printf("Which type of task do you want to create:\n");
    printf("\t1. Creation of parts\n");
    printf("\t2. Ensallament d'eines\n");
    printf("Option: ");

    tipusInput = leerInt();

    switch (tipusInput){
        case 1:
            typeTask = MINION;
            break;
        case 2:
            typeTask = SUPERMINION;
            break;
        default:
            printf("It has to be 1 or 2");
            return;
    }
    usersAEscollir = mostrarTypeDisponible(users, numUsers, typeTask);
    printf("\nWhich user are u assigning the new task? ");
    userEscollit = leerInt();

    if(userEscollit <=  0 || userEscollit > usersAEscollir){
        printf("It has to be 1 - %d", usersAEscollir);
        return;
    }
    userTriat = retornarTypeDisponible(users, numUsers, typeTask, userEscollit);

    printf("Make a brief description: ");
    leerString(descripition);

    printf("Which schedule format -> (xx:xx) : ");
    leerString(horari);

    if(!comprovarHorari(horari)){
        printf("It has to be this format -> (xx:xx)");
        return;
    }

    if(!comprovatTotesTasquesHorari(tasques, *numTasques, userTriat.user, horari)){
        printf("This user it already has a task in this schedule");
        return;
    }

    printf("How long does it take? ");
    duration = leerFloat();

    strcpy(newTask.descripcio, descripition);
    newTask.durada = duration;
    strcpy(newTask.hora, horari);    
    strcpy(newTask.nom, nomTask);
    newTask.pendent = PENDENT;
    printf("\n%s\n", userTriat.user);
    strcpy(newTask.usuari, userTriat.user);

    tasques[(*numTasques)] = newTask;
    (*numTasques)++;
}
 

void saveTasques(task *tasques, int numTasques) {
    FILE *fp = fopen(TASQUES_FILE, "w");
    
    if (fp == NULL) {
        printf("\nERROR: cannot write tasques file\n");
        return;
    }
    
    for (int i = 0; i < numTasques; i++) {
        const char *estatStr;
        
        switch (tasques[i].pendent) {
            case PENDENT:   estatStr = "PENDENT"; break;
            case EN_CURS:   estatStr = "EN_CURS"; break;
            case ACABAT:    estatStr = "ACABAT"; break;
            default:        estatStr = "PENDENT"; break;
        }
        
        fprintf(fp, "%s;%s;%s;%s;%.1f;%s\n", 
                estatStr,
                tasques[i].nom,
                tasques[i].usuari,
                tasques[i].hora,
                tasques[i].durada,
                tasques[i].descripcio);
    }
    
    fclose(fp);
}