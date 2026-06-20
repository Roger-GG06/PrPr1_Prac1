#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_STR 100
#define MAX_LENGTH 1000
#define MAX_USERS 250
#define MAX_EINES 1000
#define MAX_TASKS 4000
#define MAX_PIECE 16000

#define MAX_PIECE_PER_EINA 16

#define USERS_FILE "Data\\users.txt"
#define EINES_FILE "Data\\eines.txt"
#define TASQUES_FILE "Data\\tasques.txt"
#define PIECES_FILE "Data\\pieces.txt"

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

//Cambiar todo otra puta vez
typedef struct{
    char nom[MAX_STR];
    char creador[MAX_STR];
    int temps;
    char type[MAX_STR];
    char descripcio[MAX_LENGTH];
    int quantity;
    State creacio;
    int numPieces;
    char pieces[MAX_PIECE_PER_EINA][MAX_STR];
} eina;

typedef struct {
    char nom[MAX_STR];
    char descripcio[MAX_LENGTH];
    int durada;
    char creador[MAX_STR];
} piece;

typedef struct{
    State pendent;
    char nom[MAX_STR];
    char usuari[MAX_STR];
    char hora[MAX_STR];
    int durada;
    char descripcio[MAX_LENGTH];
} task;

#endif