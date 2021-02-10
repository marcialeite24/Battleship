#include "bs.h"

// ---- CONSTRUTORES ----

ShipBM *mkCarrierBM() {
  ShipBM *sBM = (ShipBM *)malloc(sizeof(ShipBM));
  sBM->nShip = CARRIER;
  sBM->size = 5;
  sBM->bitmap = (char **)calloc(5, sizeof(char *));
  for (int i = 0; i < 5; i++) {
    sBM->bitmap[i] = (char *)calloc(5, sizeof(char));
    for (int j = 0; j < 5; j++) {
      if (j == 2)
        sBM->bitmap[i][j] = SHIP;
      else
        sBM->bitmap[i][j] = WATER;
    }
  }
  return sBM;
}

ShipBM *mkTankerBM() {
  ShipBM *sBM = (ShipBM *)malloc(sizeof(ShipBM));
  sBM->nShip = TANKER;
  sBM->size = 4;
  sBM->bitmap = (char **)calloc(5, sizeof(char *));
  for (int i = 0; i < 5; i++) {
    sBM->bitmap[i] = (char *)calloc(5, sizeof(char));
    for (int j = 0; j < 5; j++) {
      if (j == 2 && i < 4)
        sBM->bitmap[i][j] = SHIP;
      else
        sBM->bitmap[i][j] = WATER;
    }
  }
  return sBM;
}

ShipBM *mkDestroyerBM() {
  ShipBM *sBM = (ShipBM *)malloc(sizeof(ShipBM));
  sBM->nShip = DESTROYER;
  sBM->size = 3;
  sBM->bitmap = (char **)calloc(5, sizeof(char *));
  for (int i = 0; i < 5; i++) {
    sBM->bitmap[i] = (char *)calloc(5, sizeof(char));
    for (int j = 0; j < 5; j++) {
      if (j == 2 && i > 0 && i < 4)
        sBM->bitmap[i][j] = SHIP;
      else
        sBM->bitmap[i][j] = WATER;
    }
  }
  return sBM;
}

ShipBM *mkSubmarineBM() {
  ShipBM *sBM = (ShipBM *)malloc(sizeof(ShipBM));
  sBM->nShip = SUBMARINE;
  sBM->size = 2;
  sBM->bitmap = (char **)calloc(5, sizeof(char *));
  for (int i = 0; i < 5; i++) {
    sBM->bitmap[i] = (char *)calloc(5, sizeof(char));
    for (int j = 0; j < 5; j++) {
      if (j == 2 && i > 0 && i < 3)
        sBM->bitmap[i][j] = SHIP;
      else
        sBM->bitmap[i][j] = WATER;
    }
  }
  return sBM;
}

ShipBM *mkFloaterBM() {
  ShipBM *sBM = (ShipBM *)malloc(sizeof(ShipBM));
  sBM->nShip = FLOATER;
  sBM->size = 1;
  sBM->bitmap = (char **)calloc(5, sizeof(char *));
  for (int i = 0; i < 5; i++) {
    sBM->bitmap[i] = (char *)calloc(5, sizeof(char));
    for (int j = 0; j < 5; j++) {
      if (j == 2 && i == 2)
        sBM->bitmap[i][j] = SHIP;
      else
        sBM->bitmap[i][j] = WATER;
    }
  }
  return sBM;
}

ShipBM *mkLShipBM() {
  ShipBM *sBM = (ShipBM *)malloc(sizeof(ShipBM));
  sBM->nShip = LSHIP;
  sBM->size = 4;
  sBM->bitmap = (char **)calloc(5, sizeof(char *));
  for (int i = 0; i < 5; i++) {
    sBM->bitmap[i] = (char *)calloc(5, sizeof(char));
    for (int j = 0; j < 5; j++) {
      if ((j == 2 && i < 3) || (j == 3 && i == 2))
        sBM->bitmap[i][j] = SHIP;
      else
        sBM->bitmap[i][j] = WATER;
    }
  }
  return sBM;
}

Coord *mkCoord(int r, int c) {
  Coord *coordinate = (Coord *)malloc(sizeof(Coord));
  coordinate->row = r;
  coordinate->col = c;
  return coordinate;
}

Piece *mkPiece(ShipBM *s, int r, Coord *p) {
  Piece *peca = (Piece *)malloc(sizeof(Piece));
  peca->nHits = 0;
  peca->rotation = r;
  peca->position = p;
  peca->ship = s;
  return peca;
}

Cell *mkCell(Piece *piece) {
  Cell *celula = (Cell *)malloc(sizeof(Cell));
  celula->p = piece;
  celula->shot = WATER;
  celula->shotGAME = WATER;
  return celula;
}

Tab *mkTab(int n) {
  Tab *matrix = (Tab *)malloc(sizeof(Tab));
  matrix->nShips = n * n / 25;
  matrix->size = n;
  matrix->tab = (Cell **)calloc(n, sizeof(Cell *));
  for (int i = 0; i < n; i++) {
    matrix->tab[i] = (Cell *)calloc(n, sizeof(Cell));
    for (int j = 0; j < n; j++) {
      matrix->tab[i][j].shot = WATER;
      matrix->tab[i][j].shotGAME = WATER;
      matrix->tab[i][j].p = NULL;
    }
  }
  return matrix;
}

// ---- FUNÇÕES AUXILIARES ----

// Default da escolha da forma como colocar os barcos no tabuleiro
void PlacePiecesOnBoard(int colocarPecas, int nShips, Tab *game, int *nBoats) {
  while ((colocarPecas != 1) && (colocarPecas != 2)) {
    printf("Invalid Option! Try again.\n");
    printf("-> ");
    scanf("%d", &colocarPecas);
  }
  sleep(2);
  if (colocarPecas == 1) {
    PlacePiecesRandom(game, nBoats);
  }
  else {
    PlacePiecesManualy(game, nBoats);
  }
  printf("\n");
}

// Determinar o número de peças de cada barco aleatoriamente
void nPiecesRandom(int nShips, int *nB) {
  int d = rand() % (nShips-5) + 6;
  while(1) {  
    // CARRIER
    nB[0] = rand() % (d-5) + 1;
    
    // TANKER
    nB[1] = rand() % (d-5) + 1;
    
    // DESTROYER
    nB[2] = rand() % (d-5) + 1;
    
    // SUBMARINE
    nB[3] = rand() % (d-5) + 1;
    
    // FLOATER
    nB[4] = rand() % (d-5) + 1;
    
    // LSHIP
    nB[5] = rand() % (nShips-5) + 1;
   
    if(d == (nB[0]+nB[1]+nB[2]+nB[3]+nB[4]+nB[5])) {
      printf("\nTotal of ships: %d\n", nB[0]+nB[1]+nB[2]+nB[3]+nB[4]+nB[5]);
      printf("%d Carriers, ", nB[0]);
      printf("%d Tankers, ", nB[1]);
      printf("%d Destroyers, ", nB[2]);
      printf("%d Submarines, ", nB[3]);
      printf("%d Floaters, ", nB[4]);
      printf("%d Lships\n", nB[5]);
      break;
    }
  }
}

// Determinar o número de peças de cada barco manualmente
void nPiecesManual(int nShips, int *nB) {
  printf("\nYou have %d ships in your command! You must have at least 1 ship of each type\n", nShips);
  // CARRIER
  printf("How many Carriers do you want?\n");
  ShipBM *shipC = mkCarrierBM();
  printBM(shipC, 0);
  printf("-> ");
  scanf("%d", &nB[0]);
  while (nB[0] < 1 || nB[0] > (nShips - 5)) {
    printf("Try again!\n-> ");
    scanf("%d", &nB[0]);
  }
  // TANKER
  printf("How many Tankers do you want?\n");
  ShipBM *shipT = mkTankerBM();
  printBM(shipT, 0);
  printf("-> ");
  scanf("%d", &nB[1]);
  while (nB[1] < 1 || nB[1] > (nShips - nB[0] - 4)) {
    printf("Try again!\n-> ");
    scanf("%d", &nB[1]);
  }
  // DESTROYER
  printf("How many Destroyers do you want?\n");
  ShipBM *shipD = mkDestroyerBM();
  printBM(shipD, 0);
  printf("-> ");
  scanf("%d", &nB[2]);
  while (nB[2] < 1 || nB[2] > (nShips - nB[0] - nB[1] - 3)) {
    printf("Try again!\n-> ");
    scanf("%d", &nB[2]);
  }
  // SUBMARINE
  printf("How many Submarines do you want?\n");
  ShipBM *shipS = mkSubmarineBM();
  printBM(shipS, 0);
  printf("-> ");
  scanf("%d", &nB[3]);
  while (nB[3] < 1 || nB[3] > (nShips - nB[0] - nB[1] - nB[2] - 2)) {
    printf("Try again!\n-> ");
    scanf("%d", &nB[3]);
  }
  // FLOATER
  printf("How many Floaters do you want?\n");
  ShipBM *shipF = mkFloaterBM();
  printBM(shipF, 0);
  printf("-> ");
  scanf("%d", &nB[4]);
  while (nB[4] < 1 || nB[4] > (nShips - nB[0] - nB[1] - nB[2] - nB[3] - 1)) {
    printf("Try again!\n-> ");
    scanf("%d", &nB[4]);
  }
  // LSHIP
  printf("How many LShips do you want?\n");
  ShipBM *shipL = mkLShipBM();
  printBM(shipL, 0);
  printf("-> ");
  scanf("%d", &nB[5]);
  while (nB[5] < 1 || nB[5] > (nShips - nB[0] - nB[1] - nB[2] - nB[3] - nB[4])) {
    printf("Try again!\n-> ");
    scanf("%d", &nB[5]);
  }
}

// Colocar as peças aleatoriamente
void PlacePiecesRandom(Tab *game, int *nB) {
  int i = 0;
  while (i < nB[0]) {
    positionShipRandom(mkCarrierBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[1]) {
    positionShipRandom(mkTankerBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[2]) {
    positionShipRandom(mkDestroyerBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[3]) {
    positionShipRandom(mkSubmarineBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[4]) {
    positionShipRandom(mkFloaterBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[5]) {
    positionShipRandom(mkLShipBM(), game);
    i++;
  }
  printf("\n");
  printTab(game);
}

// Colocar as peças manualmente
void PlacePiecesManualy(Tab *game, int *nB) {
  int i = 0;
  while (i < nB[0]) {
    positionShip(mkCarrierBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[1]) {
    positionShip(mkTankerBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[2]) {
    positionShip(mkDestroyerBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[3]) {
    positionShip(mkSubmarineBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[4]) {
    positionShip(mkFloaterBM(), game);
    i++;
  }
  i = 0;
  while (i < nB[5]) {
    positionShip(mkLShipBM(), game);
    i++;
  }
}

// Posicionamento dos barcos aleatoriamente
void positionShipRandom(ShipBM *sBM, Tab *game) {
  int linha = rand() % game->size;
  int coluna = rand() % game->size;
  int nRotacao = 0+rand()/(RAND_MAX/4 + 0);
  int rotacao = 0;
  switch (nRotacao) {
  case 0:
    rotacao = 0;
    break;
  case 1:
    rotacao = 90;
    break;
  case 2:
    rotacao = 180;
    break;
  case 3:
    rotacao = 270;
    break;
  default:
    break;
  }

  Piece *peca = mkPiece(sBM, rotacao, mkCoord(linha, coluna));
  rotateBM(peca->ship, peca->rotation);
  while (isPossibleInsert(game, peca) == FALSE) {
    linha = rand() % game->size;
    coluna = rand() % game->size;
    nRotacao = 0+rand()/(RAND_MAX/4 + 0);
    switch (nRotacao) {
    case 0:
      rotacao = 0;
      break;
    case 1:
      rotacao = 90;
      break;
    case 2:
      rotacao = 180;
      break;
    case 3:
      rotacao = 270;
      break;
    default:
      break;
    }
    peca -> position -> row = linha;
    peca -> position -> col = coluna;
    peca -> rotation = rotacao;
    resetPiece(peca, rotacao, mkCoord(linha, coluna));
    rotateBM(peca -> ship, rotacao);
  }
  updateTab(game, peca);
}

// Posicionamento dos barcos manualmente
void positionShip(ShipBM *sBM, Tab *game) {
  int linha, coluna;
  int rotacao;
  printf("\nWhere you want your %s?\n", PieceTypeTOString(sBM -> nShip));
  printBM(sBM, 1);
  printf(" => Insert the coordenate (e.g. 3 3): ");
  scanf("%d %d", &linha, &coluna);
  while ((linha < 0 || linha >= game->size) || (coluna < 0 || coluna >= game->size)) {
    printf(" Try another coordenate!\n -> ");
    scanf("%d %d", &linha, &coluna);
  }
  printf(" => Insert the ship's rotation: ");
  scanf("%d", &rotacao);
  while (rotacao != 0 && rotacao != 90 && rotacao != 180 && rotacao != 270) {
    printf(" Try another rotation!(0, 90, 180 or 270)\n -> ");
    scanf("%d", &rotacao);
  }
  Piece *peca = mkPiece(sBM, rotacao, mkCoord(linha, coluna));
  rotateBM(peca->ship, peca->rotation);
  while (isPossibleInsert(game, peca) == FALSE) {   
    printf("\nThat is impossible insert this ship on this coordenates with that rotation.\nPlease try again with another!\n\n");
    printf("Where you want your %s?\n", PieceTypeTOString(sBM -> nShip));
    printf(" => Insert the coordenate (e.g. 3 3): ");
    scanf("%d %d", &linha, &coluna);
    while ((linha < 0 || linha >= game->size) || (coluna < 0 || coluna >= game->size)) {
      printf(" Try another coordenate!\n -> ");
      scanf("%d %d", &linha, &coluna);
    }
    printf(" => Insert the ship's rotation: ");
    scanf("%d", &rotacao);
    while (rotacao != 0 && rotacao != 90 && rotacao != 180 && rotacao != 270) {
      printf(" Try another rotation!(0, 90, 180 or 270)\n -> ");
      scanf("%d", &rotacao);
    }
    peca -> position -> row = linha;
    peca -> position -> col = coluna;
    peca -> rotation = rotacao;
    resetPiece(peca, rotacao, mkCoord(linha, coluna));
    rotateBM(peca -> ship, rotacao);
  }
  updateTab(game, peca);
  printTab(game);
}

// Reset da peça em relação ao bitmap
void resetPiece(Piece*peca, int r, Coord* pos) {
  peca -> rotation = r;
  peca -> position -> row = pos -> row;
  peca -> position -> col = pos -> col;
  switch (peca -> ship -> nShip) {
  case CARRIER:
    peca -> ship = mkCarrierBM();
    break;
  case TANKER:
    peca -> ship = mkTankerBM();
    break;
  case DESTROYER:
    peca -> ship = mkDestroyerBM();
    break;
  case SUBMARINE:
    peca -> ship = mkSubmarineBM();
    break;
  case FLOATER:
    peca -> ship = mkFloaterBM();
    break;
  case LSHIP:
    peca -> ship = mkLShipBM();
    break;
  default:
    break;
  }
}

// Verificar se é possível inserir o barco no tabuleiro
Bool isPossibleInsert(Tab *mat, Piece *peca) {
  int coluna = peca->position->col;
  int linha = peca->position->row;
  int xBM = 0;
  int yBM = 0;
  for (int i = linha - 2; i <= linha + 2; i++) {
    yBM = 0;
    for (int j = coluna - 2; j <= coluna + 2; j++) {
      if (peca->ship->bitmap[xBM][yBM] == SHIP) {
        if (i < 0 || j < 0 || i >= mat->size || j >= mat->size) {
          return FALSE;
        }
        else if (mat->tab[i][j].shot == SHIP) {
          return FALSE;
        }
      }
      yBM++;
    }
    xBM++;
  }
  return TRUE;
}

// Rotação do bitmap
void rotateBM(ShipBM *sBM, int rot) {
  for (int r = 270; r >= rot; r = r - 90) {
    for (int i = 0; i < 5 / 2; i++) {
      for (int j = i; j < 5 - i - 1; j++) {
        char temp = sBM -> bitmap[i][j];
        sBM->bitmap[i][j] = sBM->bitmap[j][5 - 1 - i];
        sBM->bitmap[j][5 - 1 - i] = sBM->bitmap[5 - 1 - i][5 - 1 - j];
        sBM->bitmap[5 - 1 - i][5 - 1 - j] = sBM->bitmap[5 - 1 - j][i];
        sBM->bitmap[5 - 1 - j][i] = temp;
      }
    }
  }
}

// Atualizar o tabuleiro do jogador
void updateTab(Tab *mat, Piece *peca) {
  int coluna = peca->position->col;
  int linha = peca->position->row;
  int xBM = 0;
  int yBM = 0;
  for (int i = linha - 2; i <= linha + 2; i++) {
    yBM = 0;
    for (int j = coluna - 2; j <= coluna + 2; j++) {
      if (peca->ship->bitmap[xBM][yBM] == SHIP) {
        mat->tab[i][j].shot = SHIP;
        mat->tab[i][j].p = peca;
      }
      yBM++;
    }
    xBM++;
  }
}

// Imprimir o bitmap de cada barco
void printBM(ShipBM *bmap, int flag) {
  for (int i = 0; i < 5; i++) {
    printf(" ");
    for (int j = 0; j < 5; j++) {
      if(bmap->bitmap[i][j] == WATER)
        printf("\033[0;34m"); // Azul
      if(i == 2 && j == 2 && flag == 1)
        printf("\033[0;33m");
      printf("%c ", bmap->bitmap[i][j]);
      printf("\033[0m"); // Reset da cor
    }
    printf("\n");
  }
}

// Imprimir o tabuleiro de jogo
void printTab(Tab *matrix) {
  for (int i = 0; i < matrix->size; i++) {
    printf(" ");
    for (int j = 0; j < matrix->size; j++) {
      if(matrix->tab[i][j].shot == WATER)
        printf("\033[0;34m"); // Azul
      else if(matrix->tab[i][j].shot == HIT)
        printf("\033[1;31m"); // Vermelho
      else if(matrix->tab[i][j].shot == MISS)
        printf("\033[0;90m"); // Cinzento
      printf("%c ", matrix->tab[i][j].shot);
      printf("\033[0m"); // Reset da cor
    }
    printf("\n");
  }
}

// Imprimir o tabuleiro do jogador adversário
void printTabGAME(Tab *matrix) {
  for (int i = 0; i < matrix->size; i++) {
    printf(" ");
    for (int j = 0; j < matrix->size; j++) {
      if(matrix->tab[i][j].shotGAME == WATER)
        printf("\033[0;34m"); // Azul
      else if(matrix->tab[i][j].shotGAME == HIT)
        printf("\033[1;31m"); // Vermelho
      else if(matrix->tab[i][j].shotGAME == MISS)
        printf("\033[0;90m"); // Cinzento
      printf("%c ", matrix->tab[i][j].shotGAME);
      printf("\033[0m"); // Reset da cor
    }
    printf("\n");
  }
}

// Passar uma PieceType para String
char* PieceTypeTOString(PieceType n) {
  char* nameS = (char*) malloc(sizeof(char));
  switch (n) {
  case CARRIER:
    nameS = "Carrier";
    break;
  case TANKER:
    nameS = "Tanker";
    break;
  case DESTROYER:
    nameS = "Destroyer";
    break;
  case SUBMARINE:
    nameS = "Submarine";
    break;
  case FLOATER:
    nameS = "Floater";
    break;
  case LSHIP:
    nameS = "LShip";
    break;
  default:
    break;
  }
  return nameS;
}

// ---- FUNÇÕES PARA JOGAR ----

// Alterar o tabuleiro do adversário de acordo com a jogada do respetivo player
void chooseplay(Tab* game) {
  // Inserir as coordenadas
  int linha, coluna;
  printf(" => Insert your play, coordenates (e.g. 3 3): ");
  scanf("%d %d", &linha, &coluna);
  while ((linha < 0 || linha >= game->size) || (coluna < 0 || coluna >= game->size) || (game -> tab[linha][coluna].shotGAME != WATER)) {
    printf(" Try another coordenates!\n -> ");
    scanf("%d %d", &linha, &coluna);
  }
  // Verificar se atingiu ou não e Alterar o tabuleiro do adversário
  if(game -> tab[linha][coluna].shot == SHIP) {
    game -> tab[linha][coluna].shotGAME = HIT;
    game -> tab[linha][coluna].shot = HIT;
    game -> tab[linha][coluna].p -> nHits++;
    if(game -> tab[linha][coluna].p -> nHits == game -> tab[linha][coluna].p -> ship -> size) {
      printf("You destroy a %s!\n", PieceTypeTOString(game -> tab[linha][coluna].p -> ship -> nShip));
    }
    else printf("You hit in a ship!\n");
  }
  else if(game -> tab[linha][coluna].shot == WATER) {
    game -> tab[linha][coluna].shotGAME = MISS;
    game -> tab[linha][coluna].shot = MISS;
    printf("You miss my friend eheh\n");
  }
}

// Verificar se o respetivo jogador ganhou
Bool isWinner(Tab* game) {
  for(int i = 0; i < game -> size; i++) {
    for(int j = 0; j < game -> size; j++) {
      if(game -> tab[i][j].shot == SHIP)
        return FALSE;
    }
  }
  return TRUE;
}
