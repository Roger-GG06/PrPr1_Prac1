#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "piece.h"

#define PIECES_FILE "Data\\pieces.txt"

void loadPieces(piece *pieces, int *numPieces) {
    FILE *fp = fopen(PIECES_FILE, "r");
    char line[MAX_LENGTH * 2];
    
    *numPieces = 0;
    
    if (fp == NULL) {
        printf("\nERROR: cannot read pieces file\n");
        return;
    }
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        char nomTemp[MAX_STR], descripcioTemp[MAX_LENGTH], duradaTemp[MAX_STR];
        
        int i = 0, j = 0;
        int camp = 0;
        
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ';') {
                if (camp == 0) nomTemp[j] = '\0';
                else if (camp == 1) descripcioTemp[j] = '\0';
                
                camp++;
                j = 0;
            } else {
                if (camp == 0) nomTemp[j] = line[i];
                else if (camp == 1) descripcioTemp[j] = line[i];
                else if (camp == 2) duradaTemp[j] = line[i];
                j++;
            }
        }
        
        if (camp == 2) duradaTemp[j] = '\0';
        
        strcpy(pieces[*numPieces].nom, nomTemp);
        strcpy(pieces[*numPieces].descripcio, descripcioTemp);
        pieces[*numPieces].durada = atof(duradaTemp);
        
        (*numPieces)++;
    }
    
    fclose(fp);
}

void showPieces(piece *pieces, int numPieces){
    printf("PIECES AVAILABLE\n");
    for(int i = 1; i < numPieces; i++){
        printf("%d) %s\n", i, pieces[i-1].nom);
    }
}

void getPiece(piece *pieces, int piecePosition, char *namePiece){
    strcpy(namePiece, pieces[piecePosition].nom);
}