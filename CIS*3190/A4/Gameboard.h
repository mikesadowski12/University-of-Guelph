/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

/* 
 * This file contains the GameBoard information struct
 * It holds the board and locations of all pawns, and the count of the player's/computer's pawns
*/ 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARDSIZE 9
#define INVALIDMOVE 0
#define VALIDMOVE 1
#define ISINTEGER 1
#define NOTINTEGER 0

typedef struct Gameboard
{
	char array[BOARDSIZE]; /* the board */
	
	int playerCount; /* player's pawn count */
	int compCount; /* computer's pawn count */
	
} Gameboard;

Gameboard createBoard(Gameboard board);
void printBoard(Gameboard board);

int *playerMove(int *move);
int checkPlayerMove(Gameboard board, int *move, char pawn, char opposingPawn);

Gameboard updateBoard(Gameboard board, int *move, char pawn, char opposingPawn);
char checkWinner(Gameboard board);
int checkAvailableMoves(Gameboard board, char pawn, char enemy);
int checkDraw(Gameboard board);
void printUsage(void);

int isStringAnInteger(char *string);
char getYesNo(char *message);
