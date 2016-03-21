/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

/* 
 * This file contains the GameBoard information struct
 * It holds the locations of learned moves/deleted moves for the computer players
 * 4 different arrays, 2 for the learned moves and 2 for the deleted moves
 * Each group of arrays correspond to eachother (eg origin[0], destination[0] is one move)
*/ 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "Gameboard.h"

#define MAXMOVES 50
#define MOVEFOUND 1
#define MOVENOTFOUND 0
#define FORWARD 3
#define DIAGONALLEFT 2
#define DIAGONALRIGHT 4


typedef struct Computer
{
	int origin[MAXMOVES]; /* Holds the pawn location for possible move */
	int destination[MAXMOVES]; /* Holds the pawn destination for possible move */

	int moveCount;
	
	int deletedOrigin[MAXMOVES]; /* Holds the pawn location for deleted move */
	int deletedDestination[MAXMOVES]; /* Holds the pawn destinatin for deleted move */
} Computer;

Computer createComputer(Computer computer);
Computer findComputerMoves(Gameboard board, Computer computer); 
int checkComputerPossibleMove(Gameboard board, Computer computer, int origin, int move);
int computerMove(Gameboard board, Computer computer, int **move);

Computer forgetMove(Computer computer, int origin, int destination);
int checkAllowedMoves(Computer computer, int origin, int destination);
int checkDeletedMoves(Computer computer, int origin, int destination);
Computer updateAllowedMoves(Computer computer, int origin, int destination);
Computer updateDeletedMoves(Computer computer, int origin, int destination);

void printAllowed(Computer computer);
void printDeleted(Computer computer);
