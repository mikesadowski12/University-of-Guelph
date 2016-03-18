/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

#include "./Gameboard.h"

int main(void) 
{
	Gameboard board;
	char winner = '0';
	int i = 0;
	int error = 1;
	int *move = (int *)malloc(sizeof(int));
	
	
	printUsage();
	
	board = createBoard(board);
	
	while(1)
	{
		printBoard(board);
	
		/* if the player made their move and it was valid, update the board */
		if ( checkPlayerMove(board, playerMove(move), 'O', 'X') )
		{
			board = updateBoard(board, move, 'O', 'X');
			
		}
		
		winner = checkWinner(board);
		
		if ( winner != '0') { break; }		
	}
	
	free(move);
	
	/*print the final board, and who the winner is */
	system("clear");
	printf("\n\n*************************\n");
	printf("**    Winner is:  %c    **\n", winner);
	printf("*************************");
	printBoard(board);
	
	return 1;
}
