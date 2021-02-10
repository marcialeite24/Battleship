#include "bs.h"

int main() {
  srand(time(NULL));
  // Limpar o terminal
  system("clear");
  
  printf("\n\t\t························\n");
  printf("\t\t··                    ··\n");
  printf("\t\t··     Welcome to     ··\n");
  printf("\t\t··     BATTLESHIP     ··\n");
  printf("\t\t··                    ··\n");
  printf("\t\t························\n\n");

  // MENU
  int menu;
  printf("=> MENU\n");
  printf("1) Start the game\n");
  printf("2) Instructions\n");
  printf("-> ");
  scanf("%d", &menu);

  // INSTRUÇÕES
  if(menu == 2) {
    system("clear");
    printf("\t\t\t**** INSTRUCTIONS ****\n\n");
    printf("· The game contains two boards for each player in which the coordinates\n");
    printf("range from 0 to size-1 (one that represents the layout of the player's\n");
    printf("boats, and another that represents the opponent's).\n");
    printf("· At the beginning of the game, the player chooses the size of the board,\n");
    printf("each player chooses to place their ships manually (coordinates, rotation)\n");
    printf("or randomly.\n");
    printf("· The number of ships is the same for both players, minimum 6 and maximum\n");
    printf("size * size / 25, with player 1 to be defined.\n");
    printf("· After the ships have been positioned, the game continues in a series of\n");
    printf("turns. In each turn, a player says a coordinate (eg: 3 3), on the opponent's\n");
    printf("board, if you hit a ship a red mark ('*') is placed, if there is no ship\n");
    printf("a gray mark ('m') is placed.\n");
    printf("· The objective is to hit all the opponent's ships faster than the opponent.\n\n");

    printf("Press 1 to start!\n -> ");
    scanf("%d", &menu);
  }

  sleep(1);
  system("clear");
  // Definir o nome do jogador 1
  char player1[30];
  printf("\nPlayer 1: ");
  scanf("%s", player1);

  // Definir o nome do jogador 2
  char player2[30];
  printf("\nPlayer 2: ");
  scanf("%s", player2);

  // Definir o tamanho do tabuleiro
  int size;
  printf("\n=> Size of board game (20 < size < 40): ");
  scanf("%d", &size);
  while(size < 20 || size > 40) {
    printf("Size isn't able to the game! Please choose between 20 and 40.\n=> Size: ");
    scanf("%d", &size);
  }
  int nShips = (size*size)/25; // Número de barcos
  int colocarPecas;
  int* nBoats = (int*) calloc(6, sizeof(int));  
  // PLAYER 1
  system("clear");
  printf("\n *** PLAYER %s ***\n (Player %s close your eyes!)\n", player1, player2);
  Tab* gameP1 = mkTab(size);
  printf("\n=> Choose one of the options below:\n");
  printf("1) Place the pieces randomly\n");
  printf("2) Place the pieces manually\n");
  printf("-> ");
  scanf("%d", &colocarPecas);
  // Definir o número de barcos para todos
  if(colocarPecas == 1)
    nPiecesRandom(nShips, nBoats);
  else
    nPiecesManual(nShips, nBoats);
  PlacePiecesOnBoard(colocarPecas, nShips, gameP1, nBoats);
  int flag = 0;
  while(flag != 1) {
    printf("Press 1 to Player %s's turn\n -> ", player2);
    scanf("%d", &flag);
  }
  // PLAYER 2
  system("clear");
  printf("\n *** PLAYER %s ***\n (Player %s close your eyes!)\n", player2, player1);
  Tab* gameP2 = mkTab(size);
  printf("\nTotal of ships: %d\n", nBoats[0]+nBoats[1]+nBoats[2]+nBoats[3]+nBoats[4]+nBoats[5]);
  printf("%d Carriers, ", nBoats[0]);
  printf("%d Tankers, ", nBoats[1]);
  printf("%d Destroyers, ", nBoats[2]);
  printf("%d Submarines, ", nBoats[3]);
  printf("%d Floaters, ", nBoats[4]);
  printf("%d Lships\n", nBoats[5]);
  printf("\n=> Choose one of the options below:\n");
  printf("1) Place the pieces randomly\n");
  printf("2) Place the pieces manually\n");
  printf("-> ");
  scanf("%d", &colocarPecas);
  PlacePiecesOnBoard(colocarPecas, nShips, gameP2, nBoats);
  flag = 0;
  while(flag != 1) {
    printf("Press 1 to start the game\n -> ");
    scanf("%d", &flag);
  }

  system("clear");

  // INÍCIO DO JOGO
  printf("\n\t\t························\n");
  printf("\t\t··                    ··\n");
  printf("\t\t··     LET'S PLAY     ··\n");
  printf("\t\t··                    ··\n");
  printf("\t\t························\n\n");
  sleep(2);
  int turn = 1; // (1 -> Player 1) e (2 -> Player 2)
  while(1) {
    if(turn == 1) {
      system("clear");
      printf("\n *** PLAYER %s ***\n (Player %s close your eyes!)\n\n", player1, player2);
      printTab(gameP1);
      printf("\n");
      printTabGAME(gameP2);
      printf("\n");
      chooseplay(gameP2);
      if(isWinner(gameP2) == TRUE) {
        system("clear");
        printf("\n\t\t**** PLAYER %s WINS! ****\n\n", player1);
        return 0;
      }
      sleep(4);
      turn = 2;
    }
    if(turn == 2) {
      system("clear");
      printf("\n *** PLAYER %s ***\n (Player %s close your eyes!)\n\n", player2, player1);
      printTab(gameP2);
      printf("\n");
      printTabGAME(gameP1);
      printf("\n");
      chooseplay(gameP1);
      if(isWinner(gameP1) == TRUE) {
        system("clear");
        printf("\n\t\t**** PLAYER %s WINS! ****\n\n", player2);
        return 0;
      }
      sleep(4);
      turn = 1;
    }
  }
  free(gameP1);
  free(gameP2);
}
