#ifndef PIECE_H
#define PIECE_H

#include "structs.h"
#include "utils.h"

void loadPieces(piece *pieces, int *numPieces);
void showPieces(piece *pieces, int numPieces);
void getPiece(piece *pieces, int piecePosition, char *namePiece);
void createNewPiece(piece *pieces, int *numPieces, char nameUser[MAX_STR]);

#endif  