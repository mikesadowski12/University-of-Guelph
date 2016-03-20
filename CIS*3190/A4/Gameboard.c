/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

/* 
 * This file contains the GameBoard functions that allow the player to make their move
 * as well as update the board once the player has made a valid move.
*/ 

#include "Gameboard.h"

/* Name: createBoard()
 * Description: creates a new gameboard
 * Parameters: board: a GameBoard
 * Return: the newly created gameboard
*/ 
Gameboard createBoard(Gameboard board) 
{
	int i = 0;
	
	/* both players start with 3 pawns */
	board.playerCount = 3;
	board.compCount = 3;
	
	for (i = 0; i < BOARDSIZE; i++)
	{
		if ( i < 3 )
		{
			board.array[i] = 'X';
		}
		else if ( i >= 3 && i < 6 )
		{
			board.array[i] = '.';
		}
		else if ( i >= 6 && i < 9 )
		{
			board.array[i] = 'O';
		}		
	}
	
	return board;
}

/* Name: printBoard
 * Description: Prints the contents of all 3 rows of the game board
 * Parameters: board: the board to be printed
 * Return: none
*/ 
void printBoard(Gameboard board) 
{
	int i = 0;
	
	/* print all rows of the board*/
	printf("\n\t");
	for (i = 0; i < BOARDSIZE; i++) 
	{
		printf("%c ", board.array[i]);	
		
		if( i == 2 || i == 5 )
		{
			printf("\n\t");
		}
		
	}	
	
	printf("\n");
	printf("\n");
}



/* Name: playerMove()
 * Description: Allows a player to enter a possible move.
 * Parameters: move: empty array of characters to store the move
 * Return: the move in a character array[3] (comma seperating the 2 numbers)
*/ 
int *playerMove(int *move) 
{	
	char pawnLocation[256] = {0};
	char newPawnLocation[256] = {0};
	int errorFlag = 1; /* assume input is wrong */
	
	/*loop until user enters a string that is an integer*/
	do
	{
		printf("> Enter pawn location: ");
		fgets(pawnLocation, sizeof(pawnLocation), stdin);
	
		if ( isStringAnInteger(pawnLocation) ) { errorFlag = 0; }
	} while (errorFlag);
	
	errorFlag = 1; /*assume 2nd input is wrong as well*/
	
	/*loop until user enters a string that is an integer*/
	do
	{
		printf("> Enter new pawn location: ");
		fgets(newPawnLocation, sizeof(newPawnLocation), stdin);
	
		if ( isStringAnInteger(newPawnLocation) ) { errorFlag = 0; }
	} while (errorFlag);
		
	/* build array for the player's move */
	move[0] = atoi(pawnLocation);
	move[1] = atoi(newPawnLocation);

	return move;
}

/* Name: CheckPlayerMove()
 * Description: Check the board to see if the player made a legal move. Move forward 1 to empty space, or move diagonally 1 to take enemy pawn
 * Parameters: board: current game, move: the move the player is trying to make, pawn: players pawn character, opposingPawn: enemy pawn character
 * Return: VALIDMOVE=1 if pass, INVALIDMOVE=0 if fail
*/ 
int checkPlayerMove(Gameboard board, int *move, char pawn, char opposingPawn) 
{
	int direction = 0;
	
	/* need to know the correct direction the pawn is supposed to move (up or down) */
	if ( pawn == 'X' )
	{
		direction = 1; /* X moves down */
	}
	else if ( pawn == 'O' )
	{
		direction = -1; /* O moves up */
	}
	
	/* Check if the move values are within the correct range 1-9 */
	if ( (move[0] >= 1 && move[0] <= 9) && ( move[1] >= 1 && move[1] <= 9) )
	{
		/* Check the gameboard to see if the player selected their own pawn */
		if ( board.array[move[0] - 1] == pawn)
		{
			/* if the (destination - origin) is 3, move forward 1 needs to be valid */
			if ( move[1] - move[0] == (3 * direction) )
			{
				/* Check the gameboard to see if the player selected an empty space */
				if ( board.array[move[1] - 1] == '.' )
				{			
					return VALIDMOVE; /* player can move forward 1 space */
				}
			}
			
			/* if the (destination - origin) is 2 or 4, move diagonally 1 needs to be valid */
			if ( move[1] - move[0] == (2 * direction) || move[1] - move[0] == (4 * direction) )
			{
				printf("moving diagonally\n");
				/* Check the gameboard to see if the player selected an enemy pawn */
				if ( board.array[move[1] - 1] == opposingPawn )
				{			
					return VALIDMOVE; /* player can take enemy pawn */
				}
			}
				 
		}	
	} 
	
	/*one of the above tests failed, return fail */	
	return INVALIDMOVE;
}

/* Name: updateBoard()
 * Description: updates the board after the player has made their move
 * Parameters: board: current game, move: the move the player is trying to make, pawn: players pawn character, opposingPawn: enemy pawn character
 * Return: the updated gameboard
*/ 
Gameboard updateBoard(Gameboard board, int *move, char pawn, char opposingPawn) 
{
	/*if it was a diagonal move, subtract 1 from the enemy count*/
	if ( board.array[move[1] - 1] == opposingPawn )
	{
		if ( pawn == 'X' )
		{
			board.playerCount = board.playerCount - 1;
		}
		else if ( pawn == 'O' )
		{
			board.compCount = board.compCount - 1;
		}	
	}
	
	board.array[move[0] - 1] = '.';
	board.array[move[1] - 1] = pawn;
	
	return board;
}

/* Name: printUsage()
 * Description: prints usage statements and instructions if user chooses to do so
 * Parameters: board: current game, move: the move the player is trying to make
 * Return: the updated gameboard
*/ 
void printUsage(void)
{	
	char choice = 0;	
	system("clear");
	
	printf("\n	Welcome to Hexapawn!\n");
		
	printf("\n> Instructions? (Y-N): ");		
	choice =  getYesNo();
	
	if ( choice == 'y' )
	{
		printf("\nThe numbering of the board is as follows:\n");
	
		printf("		1 2 3\n");
		printf("		4 5 6\n");
		printf("		7 8 9\n");
		
		printf("\nInput will loop until a valid move is entered\n");
		printf("You are 'O'\n");
		printf("Computer is 'X'\n");
		printf("Empty spaces are '.'\n");
		
		printf("\nExample: move your right most pawn forward is as follows:\n");
		printf("> Enter pawn location: 9\n");
		printf("> Enter new pawn location: 6\n\n");
				
		do
		{
			printf("> Continue? (Y-N): ");
			choice = getYesNo();	
		} while (choice == 'n');
	}
	
	system("clear");
	printf("\nGame has started!\n");
}

/* Name: checkWinner
 * Description: Check if there is a winner in the game (no pawns left, or pawn reached other side)
 * Parameters: none
 * Return: the character that won ('X' or 'O"), or '0' for no winner
*/ 
char checkWinner(Gameboard board)
{
	int i = 0;
	
	for (i = 0; i < BOARDSIZE; i++)
	{
		/* Check top row for player's pawn */
		if ( i == 1 || i == 2 || i == 3 )
		{
			if ( board.array[i - 1] == 'O' ) { return 'O'; }
		}
		
		/* Check bottom row for computers's pawn */
		if ( i == 7 || i == 8 || i == 9 )
		{
			if ( board.array[i - 1] == 'X' ) { return 'X'; }
		}	
	}
	
	/* check if either play's pawn count is 0 */
	if ( board.playerCount == 0 )
	{
		return 'X';
	}
	else if ( board.compCount == 0 )
	{
		 return 'O';
	}
	
	/* if no winner is found, return */
	return '0';
}

/* Name: checkDraw()
 * Description: Determines if there is a draw (no player can make a move)
 * Parameters: board: the current game being played
 * Return: 
*/ 
int checkDraw(Gameboard board)
{
	return 0;
}

/* Name: isStringAnInteger()
 * Description: Determines if string contains an integer or not
 * Parameters: string: the string to be checked
 * Return: NOTINTEGER=0 if it failed, ISINTEGER=1 if passed
*/ 
int isStringAnInteger(char *string)
{
	int i = 0;
		
	for (i = 0; i < strlen(string); i++) 
	{	
		if ( !isdigit(string[i]) )
		{
			if ( string[i] != '\n' ) /*checking new line since it is contained in the string*/
			{
				return NOTINTEGER; /* if it was not a number and not a new line, return it is incorrect*/
			}
		}	
	}
	
	return ISINTEGER;
}

/* Name: getYesNo
 * Description: gets user to input yes or no
 * Parameters: none
 * Return: y for yes, n for no
*/ 
char getYesNo(void)
{
	char userInput[256] = {""};
	int errorFlag = 1; /* assume input is wrong */
	int yes = 0;
	int no = 0;
	
	/* loop until user enters a a proper response */
	do
	{
		fgets(userInput, sizeof(userInput), stdin);
	
		if ( strcmp(userInput, "y\n") == 0 || strcmp(userInput, "Y\n") == 0 || strcmp(userInput, "yes\n") == 0 
			|| strcmp(userInput, "YES\n") == 0 )
		{
			yes = 1;
			errorFlag = 0;
		}	
		else if ( strcmp(userInput, "n\n") == 0 || strcmp(userInput, "n\n") == 0 
			|| strcmp(userInput, "no\n") == 0 || strcmp(userInput, "NO\n") == 0  ) 
		{ 
			no = 1;
			errorFlag = 0; 
		}
	} while (errorFlag);	
	
	if ( yes ) { return 'y'; }
	if ( no ) { return 'n'; }
	
	return 'e'; /* error */
}



