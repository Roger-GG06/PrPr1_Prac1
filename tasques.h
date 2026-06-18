#ifndef TASQUES_H
#define TASQUES_H

#include "structs.h"
#include "utils.h"

void loadTasques(task *tasques, int *numTasques);
void mostrarTasquesPendents(task *tasques, int numTasques);
void crearNovaTasca(task *tasques, int *numTasques, user *users, int numUsers);

#endif