#ifndef EINES_H
#define EINES_H

#include "structs.h"
#include "utils.h"
#include "piece.h"

void loadEines(eina *eines, int *numEines);
void saveEines(eina *eines, int numEines);
void mostrarEinesACrear(eina *eines, int numEines);
void mostrarEinesCreades(eina *eines, int numEines);
void crearNovaEina(eina *eines, int *numEines, user *usuaris, int posicioUsuari, piece *pieces, int numPieces);
void afegirPiece(piece *pieces, int numPiece, eina *eines, int numEines);
void mostrarTempsTreballat(piece *pieces, int numPiece, eina *eines, int numEines, char user[MAX_STR]);

#endif