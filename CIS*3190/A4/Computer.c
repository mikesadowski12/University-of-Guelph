/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

/* 
 * This file contains the functions that allow the computer player to move.
 * 
*/

#include "Computer.h"

/* Name: 
 * Description: 
 * Parameters: 
 * Return: 
*/ 
Computer createComputer(Computer computer)
{
	int i = 0;
	
	for (i = 0; i < MAXMOVES; i++)
	{
		computer.origin[i] = 0;
		computer.destination[i] = 0;
		
		computer.deletedOrigin[i] = 0;
		computer.deletedDestination[i] = 0;	
	} 

	return computer;
}


/* Name: 
 * Description: 
 * Parameters: 
 * Return: 
*/ 
int *computerMove(Gameboard board, Computer computer, int *move) 
{
	int i = 1;
	int movement = 0;
	
	for (i=0; i <= BOARDSIZE; i++)
	{
		/* Pick the pawn to move */
		if ( board.array[i] == 'X' )
		{		
			/* see if that pawn is able to move */
			movement = checkComputerPossibleMove(board, computer, i);
			printf("\nchar %d is x", i+1);
			printf("\nhe can move to %d", movement+1);
			
			printBoard(board);
						
			/* there exists a way to move */
			if ( movement != 0 )
			{	
				/* return the move the computer will make as an array */
				move[0] = i;
				move[1] = i+movement;
				return move;
			}
		}	
	}
		
	/* if no moves can be made by the computer, return null because he lost */	
	return NULL;	
} 


/* Name: 
 * Description: 
 * Parameters: 
 * Return: 
*/ 
int checkComputerPossibleMove(Gameboard board, Computer computer, int origin)
{
	int i = 0;
		
	/* Check a possible move forward 1 space, and that it's an allowed move */	
	if ( checkPlayerMove(board, (int[2]){origin, origin+3}, 'X', 'O') && !checkDeletedMoves(computer, origin, origin+3) )
	{
		return 3; /* return 3 for forward 1 space */
	}
	
	/* Check a possible move diagonally, down to the left, and that it's an allowed move */	
	if ( checkPlayerMove(board, (int[2]){origin, origin+2}, 'X', 'O') && !checkDeletedMoves(computer, origin, origin+2) )
	{
		return 2; /* return 2 for diagonally to the left */
	}
	
	/* Check a possible move diagonally, down to the right, and that it's an allowed move */
	if ( checkPlayerMove(board, (int[2]){origin, origin+4}, 'X', 'O') && !checkDeletedMoves(computer, origin, origin+4) )
	{
		return 4; /* return 4 for diagonally to the right */
	}
		
	return INVALIDMOVE;
}

Computer forgetMove(Computer computer, int origin, int destination)
{
	int i = 0;
		
	/* Make sure the move exists in the list */
	if ( checkAllowedMoves(computer, origin, destination) )
	{
		/* find the move in the allowed list */
		for (i = 0; i < MAXMOVES; i++)
		{
			if ( computer.origin[i] == origin && computer.destination[i] == destination )
			{				
				/* add it to the deleted move */
				computer = updateDeletedMoves(computer, origin, destination);
				
				/* remove it from the allowed list */
				computer.origin[i] = 0;
				computer.destination[i] = 0;
				break;
			}
		}
	}
	
	/* return the updated computer */
	return computer;
}

int checkAllowedMoves(Computer computer, int origin, int destination)
{
	int i = 0;
	
	for (i = 0; i <= MAXMOVES; i++)
	{
		/* check if the move is in the allowed list */
		if ( computer.origin[i] == origin && computer.destination[i] == destination )
		{
			return MOVEFOUND;
		}
	}
		
	return MOVENOTFOUND;
}

int checkDeletedMoves(Computer computer, int origin, int destination)
{
	int i = 0;
	
	for (i = 0; i <= MAXMOVES; i++)
	{
		/* check if the move is in the not allowed list */
		if ( computer.deletedOrigin[i] == origin && computer.deletedDestination[i] == destination )
		{
			return MOVEFOUND;
		}
	}
		
	return MOVENOTFOUND;
}

Computer updateAllowedMoves(Computer computer, int origin, int destination)
{
	int i = 0;
	
	for (i = 0; i <= MAXMOVES; i++)
	{
		/* check the next available spot in the deleted list */
		if ( computer.origin[i] == 0 && computer.destination[i] == 0 )
		{
			computer.origin[i] = origin;
			computer.destination[i] = destination;
			
			return computer;
		}		
	}
	
	return computer;
}

Computer updateDeletedMoves(Computer computer, int origin, int destination)
{
	int i = 0;
	
	for (i = 0; i <= MAXMOVES; i++)
	{
		/* check the next available spot in the deleted list */
		if ( computer.deletedOrigin[i] == 0 && computer.deletedDestination[i] == 0 )
		{
			computer.deletedOrigin[i] = origin;
			computer.deletedDestination[i] = destination;
						
			return computer;
		}		
	}
		
			
	return computer;
}

void printAllowed(Computer computer)
{
	int i = 0;
	
	printf("\n\nAllowed list is: \n");
	
	for (i = 0; i < MAXMOVES; i++)
	{
		printf("%d,%d - ", computer.origin[i], computer.destination[i]);
	}
}

void printDeleted(Computer computer)
{
	int i = 0;
	
	printf("\n\nDeleted list is: \n");
	
	for (i = 0; i < MAXMOVES; i++)
	{
		printf("%d,%d - ", computer.deletedOrigin[i], computer.deletedDestination[i]);
	}	
}


