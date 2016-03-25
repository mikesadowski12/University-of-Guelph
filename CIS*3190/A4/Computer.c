/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

/* 
 * This file contains the functions that allow the computer player to move and learn moves.
*/

#include "Computer.h"

/* Name: createComputer()
 * Description: Initializes a computer objects to be empty (no moves)
 * Parameters: computer object to initialize
 * Return: initialized computer object
*/ 
Computer createComputer(Computer computer)
{
	int i = 0;
		
	/* set all moves to be 0,0 and set count to be 0*/	
	for (i = 0; i < MAXMOVES; i++)
	{
		computer.origin[i] = 0;
		computer.destination[i] = 0;
		
		computer.moveCount = 0;
	} 

	return computer;
}

/* Name: computerMove()
 * Description: Cycle through the computer's learned move list, and return the first valid move he is able to complete
 * Parameters: board: the current game board, computer: the current computer object, move: the pointer that stores both integers for the move
 * Return: 1 if the computer is able to move, 0 if he can't. the move coordinates are stored in a pointer
*/ 
int computerMove(Gameboard board, Computer computer, int **move)
{
	int i = 0;
		
	/* loop through the learned moves array*/	
	for (i = 0; i < computer.moveCount; i++)
	{
		/* check each move in the array */
		if ( checkPlayerMove(board, (int[2]){computer.origin[i], computer.destination[i]}, 'X', 'O') )
		{
			/* store the first valid move */
			*(move[0]) = computer.origin[i];
			*(move[0]+1) = computer.destination[i];
			
			/*return he is able to move, and the first available move*/
			return 1;
		}
	}
	
	/* return he can't move*/
	return 0;
}

/* Name: findComputerMoves()
 * Description: Updates the computer's allowed move array with new moves
 * Parameters: board: the current game board, computer: the current computer object
 * Return: the updated computer object
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


/* Name: checkComputerPossibleMove()
 * Description: See if the computer is able to complete a possible move or not
 * Parameters: board: the current game board, computer: the current computer object, origin: the pawn to move, move: the destination of the move
 * Return: 0 if the move was not possible, the value of the move (2,3, or 4) if it was possible
*/ 
int checkComputerPossibleMove(Gameboard board, Computer computer, int origin, int move)
{
	/* Check a possible move forward 1 space, and that it's an allowed move */
	/* Check a possible move diagonally, down to the left, and that it's an allowed move */	
	/* Check a possible move diagonally, down to the right, and that it's an allowed move */	
	if ( checkPlayerMove(board, (int[2]){origin, origin+move}, 'X', 'O') )
	{
		/* return 2 3 or 4 if the computer can move in that direction */
		return move; 
	}
	
	return INVALIDMOVE;
}

/* Name: forgetMove()
 * Description: Remove a move from the allowed moves array
 * Parameters:computer: the current computer object, origin: the pawn to move, destination: the destination of the move
 * Return: the newly updated computer object
*/ 
Computer forgetMove(Computer computer, int origin, int destination)
{
	int i = 0;
			
	/* Make sure the move exists in the list before searching */
	if ( checkAllowedMoves(computer, origin, destination) )
	{
		/* cycle through the allowed list */
		for (i = 0; i < MAXMOVES; i++)
		{
			/* find the move's position in the list */
			if ( computer.origin[i] == origin && computer.destination[i] == destination )
			{	
				/* shift all proceeding elements left 1 position to erase the move */
				for (i = i; i < computer.moveCount; i++)
				{
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

/* Name: checkAllowedMoves()
 * Description: Check if a move exists in the allowed list by searching it's origin/destination
 * Parameters:computer: the current computer object, origin: the pawn to move, destination: the destination of the move
 * Return: 0 if the move does not exist, 1 if it does
*/
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

/* Name: updateAllowedMoves()
 * Description: Insert a move to the computer's allowed list move
 * Parameters:computer: the current computer object, origin: the pawn to move, destination: the destination of the move
 * Return: the updated computer object
*/
Computer updateAllowedMoves(Computer computer, int origin, int destination)
{
	int i = 0;
	
	for (i = 0; i <= MAXMOVES; i++)
	{
		/* check the next available spot in the allowed list */
		if ( computer.origin[i] == 0 && computer.destination[i] == 0 )
		{
			/* set that spot to be the new move and increment the total count of moves */
			computer.origin[i] = origin;
			computer.destination[i] = destination;
			
			computer.moveCount++;
			
			return computer;
		}		
	}
	
	return computer;
}

/* Name: printAllowed()
 * Description: print his allowed move list for debugging
 * Parameters:computer: the current computer object
 * Return: none
*/
void printAllowed(Computer computer)
{
	int i = 0;
	
	printf("\n\nAllowed list has %d:\n", computer.moveCount);
	
	for (i = 0; i < MAXMOVES; i++)
	{
		printf("%d,%d - ", computer.origin[i], computer.destination[i]);
	}
}



