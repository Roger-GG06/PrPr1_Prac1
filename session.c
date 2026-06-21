#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "session.h"

void loadUsers(user *users, int *userCount) {
    FILE *fp = fopen(USERS_FILE, "r");
    char line[MAX_STR * 4];

    *userCount = 0;
    
    if (fp == NULL) {
        printf("\nERROR: cannot read user file\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strlen(line)-1] = '\0';
        
        char userTemp[MAX_STR], passTemp[MAX_STR], pinTemp[MAX_STR], typeTemp[MAX_STR], fruitTemp[MAX_STR];
        int i = 0, j = 0;
        int camp = 0;
        
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ';') {
                if (camp == 0) userTemp[j] = '\0';
                else if (camp == 1) passTemp[j] = '\0';
                else if (camp == 2) pinTemp[j] = '\0';
                else if (camp == 3) typeTemp[j] = '\0';
                
                camp++;
                j = 0;
            } else {
                if (camp == 0) userTemp[j] = line[i];
                else if (camp == 1) passTemp[j] = line[i];
                else if (camp == 2) pinTemp[j] = line[i];
                else if (camp == 3) typeTemp[j] = line[i];
                else if (camp == 4) fruitTemp[j] = line[i];
                j++;
            }
        }
        
        
        if (camp >= 4) fruitTemp[j] = '\0';

        strcpy(users[*userCount].user, userTemp);
        strcpy(users[*userCount].password, passTemp);
        users[*userCount].pin = atoi(pinTemp);
        
        if (strcmp(typeTemp, "GRU") == 0) users[*userCount].type = GRU;
        else if (strcmp(typeTemp, "MINION") == 0) users[*userCount].type = MINION;
        else if (strcmp(typeTemp, "SUPERMINION") == 0) users[*userCount].type = SUPERMINION;
        else if (strcmp(typeTemp, "MINION_ENG") == 0) users[*userCount].type = MINION_ENG;
        else users[*userCount].type = NONE;

        strcpy(users[*userCount].fruit, fruitTemp);

        (*userCount)++;
    }

    fclose(fp);
}

void saveUsers(user *users, int userCount) {
    FILE *fp = fopen(USERS_FILE, "w");
    
    if (fp == NULL) {
        printf("\nERROR: cannot write user file\n");
        return;
    }
        
    for (int i = 0; i < userCount; i++) {
        const char *typeStr;
        
        switch (users[i].type) {
            case GRU:         typeStr = "GRU"; break;
            case MINION:      typeStr = "MINION"; break;
            case SUPERMINION: typeStr = "SUPERMINION"; break;
            case MINION_ENG:  typeStr = "MINION_ENG"; break;
            default:          typeStr = "NONE"; break;
        }
        
        fprintf(fp, "%s;%s;%d;%s;%s\n", users[i].user, users[i].password, users[i].pin, typeStr, users[i].fruit);
    }
    
    fclose(fp);
}

void initUsers(user *users, int *numUsers) {
    *numUsers = 4;
    
    strcpy(users[0].user, "gru");
    strcpy(users[0].password, "gru123");
    users[0].pin = 1111;
    users[0].type = GRU;
    strcpy(users[0].fruit, "NONE");
    
    strcpy(users[1].user, "min");
    strcpy(users[1].password, "min123");
    users[1].pin = 2222;
    users[1].type = MINION;
    strcpy(users[1].fruit, "BANANA");
    
    strcpy(users[2].user, "sMin");
    strcpy(users[2].password, "sMin123");
    users[2].pin = 3333;
    users[2].type = SUPERMINION;
    strcpy(users[2].fruit, "BANANA");
    
    strcpy(users[3].user, "minE");
    strcpy(users[3].password, "minE123");
    users[3].pin = 4444;
    users[3].type = MINION_ENG;
    strcpy(users[3].fruit, "BANANA");
}

int findUserByUsername(user *users, int userCount, char username[MAX_STR]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].user, username) == 0) {
            return i;
        }
    }
    return -1;
}



int validatePassword(user u, char password[MAX_STR]) {
    if (strcmp(u.password, password) == 0) {
        return 1;
    }
    return 0;
}



int validatePin(user u, int pin) {
    if (u.pin == pin) {
        return 1;
    }
    return 0;
}



int login(user *users, int numUsers) {
    char username[MAX_STR];
    char password[MAX_STR];
    int pin;
    int userIndex;
    
    printf("\n=== LOGIN ===\n");
    
    printf("Username: ");
    fgets(username, MAX_STR, stdin);
    username[strcspn(username, "\n")] = '\0';
    
    userIndex = findUserByUsername(users, numUsers, username);
    
    if (userIndex == -1) {
        printf("User not found.\n");
        return -1;
    }
    
    printf("Password: ");
    leerString(password);
    
    
    if (validatePassword(users[userIndex], password)) {
        printf("Login successful! Welcome %s.\n", users[userIndex].user);
        return userIndex;
    }
    
    printf("Incorrect password. Enter PIN: ");
    pin = leerInt();    
    
    if (validatePin(users[userIndex], pin)) {
        printf("PIN correct. Login successful! Welcome %s.\n", users[userIndex].user);
        return userIndex;
    }
    
    printf("Incorrect PIN. Access denied.\n");
    return -1;
}

int registerUser(user *users, int *numUsers){
    char name[MAX_STR];
    char password[MAX_STR];
    char fruita[MAX_STR];
    int pin = 0; 
    printf("\n=== REGISTER ===\n");
    
    printf("Username: ");
    if(leerString(name)){
        printf("Name can't be void\n");
        return -1;
    }    
    if(findUserByUsername(users, *numUsers, name) != -1){
        printf("Username already in use\n");
        return -1;
    }
    
    printf("Password: ");
    if(leerString(password)){
        printf("Password can't be void\n");
        return -1;
    }

    printf("In case you forget the password. Enter a PIN: ");
    pin = leerInt();
    if(pin == -1){
        printf("It must be a number\n");
        return -1;
    }

    printf("Which is your favorite fruit? ");
    if(leerString(fruita)){
        printf("Fruit can't be void\n");
        return -1;
    }    

    UserType selectedType = MINION;

    strcpy(users[*numUsers].user, name);
    strcpy(users[*numUsers].password, password);
    strcpy(users[*numUsers].fruit, fruita);
    users[*numUsers].pin = pin;
    users[*numUsers].type = selectedType;

    int posicioRetornar = *numUsers;
    (*numUsers)++;
    return posicioRetornar;
}

