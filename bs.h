#ifndef __bs_h__
#define __bs_h__

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <time.h>

// ---- ESTRUTURAS ----

#define WATER '~'
#define HIT '*'
#define MISS 'm'
#define SHIP '#'

typedef struct _ShipBM ShipBM;
typedef struct _Coord Coord;
typedef struct _Piece Piece;
typedef struct _Cell Cell;
typedef struct _Tab Tab;

// Booleanos
typedef enum {TRUE, FALSE} Bool;

// Tipos de Navios
typedef enum {
    CARRIER,
    TANKER,
    DESTROYER,
    SUBMARINE,
    FLOATER,
    LSHIP
} PieceType;

// Bitmap para cada tipo de navio
struct _ShipBM {
    PieceType nShip;
    char **bitmap;
    int size;
};

// Coordenadas dos navios
struct _Coord {
    int row, col; // Linha e coluna correspondente
};

// Informação do barco
struct _Piece {
    int nHits; // Número de vezes em que a peça é atingida 
    ShipBM* ship; //Tipo de barco (Bitmap)
    int rotation; // Rotação do barco (0, 90, 180, 270)
    Coord* position; // Posição do barco do extremo do barco
};

// Célula do tabuleiro
struct _Cell {
    Piece *p; // Apontador para a Peça nessa Célula (pode ser null)
    char shot;
    char shotGAME; // para o jogador adversário
};

// Tabuleiro de jogo
struct _Tab {
    int nShips; // Número de barcos no tabuleiro
    int size; // Tamanho do tabuleiro (n*n)
    Cell **tab; // Matriz composta por células
};

// ---- CONSTRUTORES ----

ShipBM* mkCarrierBM();
ShipBM* mkTankerBM();
ShipBM* mkDestroyerBM();
ShipBM* mkSubmarineBM();
ShipBM* mkFloaterBM();
ShipBM* mkLShipBM();
Coord* mkCoord(int r, int c);
Piece* mkPiece(ShipBM *s, int r, Coord* p);
Cell* mkCell(Piece *piece);
Tab* mkTab(int n);

// ---- FUNÇÕES AUXILIARES ----

void PlacePiecesOnBoard(int colocarPecas, int nShips, Tab* game, int *nBoats);
void nPiecesRandom(int nShips, int *nB);
void nPiecesManual(int nShips, int *nB);
void PlacePiecesRandom(Tab *game, int *nB);
void PlacePiecesManualy(Tab* game, int *nB);
void positionShipRandom(ShipBM *sBM, Tab *game);
void positionShip(ShipBM* sBM, Tab* game);
Bool isPossibleInsert(Tab *mat, Piece *peca);
void resetPiece(Piece*peca, int r, Coord* pos);
void updateTab(Tab* mat, Piece* p);
void rotateBM(ShipBM* sBM, int rot);
void printBM(ShipBM* bmap, int flag);
void printTab(Tab* matrix);
void printTabGAME(Tab *matrix);
char* PieceTypeTOString(PieceType n);

// ---- FUNÇÕES PARA JOGAR ----

void chooseplay(Tab* game);
Bool isWinner(Tab* game);

#endif
