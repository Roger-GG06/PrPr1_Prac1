#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_STR 100
#define MAX_USERS 100
#define USERS_FILE "Data\\users.txt"

typedef enum{
    GRU,
    MINION,
    SUPERMINION,
    MINION_ENG,
    NONE
} UserType;
 
typedef struct{
    char user[MAX_STR];
    char password[MAX_STR];
    int pin;
    UserType type;
} user;

#endif