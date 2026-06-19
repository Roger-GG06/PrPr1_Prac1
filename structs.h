#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_STR 100
#define MAX_LENGTH 1000
#define MAX_USERS 250
#define MAX_EINES 1000
#define MAX_TASKS 2000
#define MAX_PIECE 4000

#define MAX_PIECE_PER_EINA 4

#define USERS_FILE "Data\\users.txt"
#define EINES_FILE "Data\\eines.txt"
#define TASQUES_FILE "Data\\tasques.txt"

typedef enum{
    GRU,
    MINION,
    SUPERMINION,
    MINION_ENG,
    NONE
} UserType;

typedef enum {
    PENDENT = 0,
    EN_CURS = 1,
    ACABAT = 2
} State;
 
typedef struct{
    char user[MAX_STR];
    char password[MAX_STR];
    int pin;
    UserType type;
} user;

typedef struct{
    char nom[MAX_STR];
    char type[MAX_STR];
    char descripcio[MAX_LENGTH];
    int quantity;
    State creacio;
    piece *pieces;
} eina;

typedef struct{
    State pendent;
    char nom[MAX_STR];
    char usuari[MAX_STR];
    char hora[MAX_STR];
    float durada;
    char descripcio[MAX_LENGTH];
} task;

typedef struct {
    char nom[MAX_STR];
    char descripcio[MAX_LENGTH];
    float durada;
} piece;

#endif