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
		
		computer.moveCount = 0;
	} 

	return computer;
}

/* Name: 
 * Description: 
 * Parameters: 
 * Return: 
*/ 
int computerMove(Gameboard board, Computer computer, int **move)
{
	int i = 0;
		
	for (i = 0; i < computer.moveCount; i++)
	{
		if ( checkPlayerMove(board, (int[2]){computer.origin[i], computer.destination[i]}, 'X', 'O') )
		{
			*(move[0]) = computer.origin[i];
			*(move[0]+1) = computer.destination[i];
			
			return 1;
		}
	}
	
	return 0;
}

/* Name: 
 * Description: 
 * Parameters: 
 * Return: 
*/ 
Computer findComputerMoves(Gameboard board, Computer computer) 
{
	int i = 0;
	int j = 0;
	int movement = 0;

	for (i=1; i <= BOARDSIZE; i++)
	{	
		/* Pick the pawn to move */
		if ( board.array[i-1] == 'X' )
		{								
			/* see if that pawn is able to move in any of the 3 directions (3=forward, 2=diagonal left, 4=diagonal right) */
			for (j = 2; j <= 4; j++)
			{				
				movement = checkComputerPossibleMove(board, computer, i, j);
				
				/* there exists a way to move */
				if ( movement != 0 )
				{	
					/* If it's not already in the list, add it */
					if ( !checkAllowedMoves(computer, i, i+movement) )
					{
						computer = updateAllowedMoves(computer, i, i+movement);
					}
				}			
			}						
		}
	} 
		
	return computer;
}


/* Name: 
 * Description: 
 * Parameters: 
 * Return: 
*/ 
int checkComputerPossibleMove(Gameboard board, Computer computer, int origin, int move)
{
	/* Check a possible move forward 1 space, and that it's an allowed move */
	/* Check a possible move diagonally, down to the left, and that it's an allowed move */	
	/* Check a possible move diagonally, down to the right, and that it's an allowed move */	
	if ( checkPlayerMove(board, (int[2]){origin, origin+move}, 'X', 'O') )
	{
		return move; 
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
				for (i = i; i < computer.moveCount; i++)
				{
					printf("\ni = %d", i);
					computer.origin[i] = computer.origin[i+1];
					computer.destination[i] = computer.destination[i+1];
				}
				
				break;
			}
		}		
	}
	
	computer.moveCount--;
	
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
			
			computer.moveCount++;
			
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
	
	printf("\n\nAllowed list has %d:\n", computer.moveCount);
	
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


