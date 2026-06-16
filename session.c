#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "session.h"

UserType login(user users[], int numUsers) {
    char username[MAX_STR];
    char password[MAX_STR];
    int pin;
    int userIndex;
    
    printf("\n=== LOGIN ===\n");
    
    printf("Username: ");
    fgets(username, MAX_STR, stdin);
    username[strcspn(username, "\n")] = '\0';
    
    //findUserByUsername(users, numUsers, username);
    userIndex = -1;
    
    if (userIndex == -1) {
        printf("User not found.\n");
        return NONE;
    }
    
    printf("Password: ");
    fgets(password, MAX_STR, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    //validatePassword(&users[userIndex], password)
    int validate = 0;
    if (validate) {
        printf("Login successful! Welcome %s.\n", users[userIndex].user);
        return users[userIndex].type;
    }
    
    printf("Incorrect password. Enter PIN: ");
    scanf("%d", &pin);
    //validatePin(&users[userIndex], pin)
    if (validate) {
        printf("PIN correct. Login successful! Welcome %s.\n", users[userIndex].user);
        return users[userIndex].type;
    }
    
    printf("Incorrect PIN. Access denied.\n");
    return NONE;
}

