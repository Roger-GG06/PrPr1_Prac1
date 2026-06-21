#ifndef TASQUES_H
#define TASQUES_H

#include "structs.h"
#include "utilsFun.h"
#include "utils.h"

void loadTasques(task *tasques, int *numTasques);
int comprovarHorariUsuari(DateTime horaExist, int durada, DateTime novaHora);
void mostrarTasquesPendents(task *tasques, int numTasques);
void crearNovaTasca(task *tasques, int *numTasques, user *users, int numUsers);
void saveTasques(task *tasques, int numTasques);

#endif
