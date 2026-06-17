#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "session.h"

void loadUsers(user *users, int *userCount) {
    FILE *fp = fopen(USERS_FILE, "r");
    char line[MAX_STR];

    *userCount = 0;
    
    if (fp == NULL) {
        printf("\nERROR: cannot read user file\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strlen(line)-1] = '\0';
        
        char userTemp[50], passTemp[50], pinTemp[50], typeTemp[50];
        int i = 0, j = 0;
        int camp = 0;
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ';') {
                if (camp == 0) userTemp[j] = '\0';
                else if (camp == 1) passTemp[j] = '\0';
                else if (camp == 2) pinTemp[j] = '\0';
                
                camp++;
                j = 0;
            } else {
                if (camp == 0) userTemp[j] = line[i];
                else if (camp == 1) passTemp[j] = line[i];
                else if (camp == 2) pinTemp[j] = line[i];
                else if (camp == 3) typeTemp[j] = line[i];
                j++;
            }
        }
        typeTemp[j] = '\0';
        
        strcpy(users[*userCount].user, userTemp);
        strcpy(users[*userCount].password, passTemp);
        users[*userCount].pin = atoi(pinTemp);

        if (strcmp(typeTemp, "GRU") == 0) users[*userCount].type = GRU;
        else if (strcmp(typeTemp, "MINION") == 0) users[*userCount].type = MINION;
        else if (strcmp(typeTemp, "SUPERMINION") == 0) users[*userCount].type = SUPERMINION;
        else if (strcmp(typeTemp, "MINION_ENG") == 0) users[*userCount].type = MINION_ENG;
        else users[*userCount].type = NONE;

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
        fprintf(fp, "%s;%s;%d;%s\n", users[i].user, users[i].password, users[i].pin, typeStr);


    }
    
    fclose(fp);
}

void initUsers(user *users, int *numUsers) {
    *numUsers = 4;
    
    // GRU
    strcpy(users[0].user, "gru");
    strcpy(users[0].password, "gru123");
    users[0].pin = 1111;
    users[0].type = GRU;
    
    // MINION
    strcpy(users[1].user, "kevin");
    strcpy(users[1].password, "kevin123");
    users[1].pin = 2222;
    users[1].type = MINION;
    
    // SUPERMINION
    strcpy(users[2].user, "bob");
    strcpy(users[2].password, "bob123");
    users[2].pin = 3333;
    users[2].type = SUPERMINION;
    
    // MINION ENGINEER
    strcpy(users[3].user, "stuart");
    strcpy(users[3].password, "stuart123");
    users[3].pin = 4444;
    users[3].type = MINION_ENG;
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



UserType login(user *users, int numUsers) {
    char username[MAX_STR];
    char password[MAX_STR];
    char trash;
    int pin;
    int userIndex;
    
    printf("\n=== LOGIN ===\n");
    
    printf("Username: ");
    fgets(username, MAX_STR, stdin);
    username[strcspn(username, "\n")] = '\0';
    
    userIndex = findUserByUsername(users, numUsers, username);
    
    if (userIndex == -1) {
        printf("User not found.\n");
        return NONE;
    }
    
    printf("Password: ");
    fgets(password, MAX_STR, stdin);
    password[strlen(password) - 1] = '\0';
    
    if (validatePassword(users[userIndex], password)) {
        printf("Login successful! Welcome %s.\n", users[userIndex].user);
        return users[userIndex].type;
    }
    
    printf("Incorrect password. Enter PIN: ");
    scanf("%d", &pin);
    scanf("%c", &trash);
    
    if (validatePin(users[userIndex], pin)) {
        printf("PIN correct. Login successful! Welcome %s.\n", users[userIndex].user);
        return users[userIndex].type;
    }
    
    printf("Incorrect PIN. Access denied.\n");
    return NONE;
}

UserType registerUser(user *users, int *numUsers){
    char name[MAX_STR];
    char password[MAX_STR];
    int pin = 0, type = 0; 
    printf("\n=== REGISTER ===\n");
    
    printf("Username: ");
    leerString(name);
    if(findUserByUsername(users, *numUsers, name) != -1){
        printf("Username already in use\n");
        return NONE;
    }

    printf("Password: ");
    leerString(password);

    printf("In case you forget the password. Enter a PIN: ");
    pin = leerInt();
    if(pin == -1){
        printf("It must be a number\n");
        return NONE;
    }

    printf("\nSelect User Type:\n");
    printf("\t1. GRU\n");
    printf("\t2. MINION\n");
    printf("\t3. SUPERMINION\n");
    printf("\t4. MINION_ENG\n");
    printf("Choose an option (1-4): ");
    type = leerInt();

    strcpy(users[*numUsers].user, name);
    strcpy(users[*numUsers].password, password);
    users[*numUsers].pin = pin;
    users[*numUsers].type = type;

    (*numUsers)++;
    return type;
}

