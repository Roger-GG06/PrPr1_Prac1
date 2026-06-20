#ifndef EINES_H
#define EINES_H

#include "structs.h"
#include "utils.h"
#include "piece.h"

void loadEines(eina *eines, int *numEines);
void mostrarEinesACrear(eina *eines, int numEines);
void mostrarEinesCreades(eina *eines, int numEines);
void crearNovaEina(eina *eines, int *numEines, user *usuari, piece *pieces, int numPieces);

#endif