#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

void leerString(char *string);
int leerInt();
float leerFloat();

int mostrarTypeDisponible(user *users, int numUsers, UserType type);
user retornarTypeDisponible(user *users, int numUsers, UserType type, int opcioEscollida);

#endif