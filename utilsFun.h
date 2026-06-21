#ifndef UTILSFUN_H
#define UTILSFUN_H

#include "structs.h"

int leerString(char *string);
int leerInt();
float leerFloat();

int mostrarTypeDisponible(user *users, int numUsers, UserType type);
user retornarTypeDisponible(user *users, int numUsers, UserType type, int opcioEscollida);
int comprovarHorari(char hora[MAX_STR]);

#endif