/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

#include "./Computer.h"

int main(void) 
{
	Gameboard board;
	Computer computer;
	char winner = '0';
	int *movePlayer = (int *)malloc(sizeof(int));
	int *moveComputer = (int *)malloc(sizeof(int));
	
	printUsage();
	
	computer = createComputer(computer);
	
	while(1)
	{
		board = createBoard(board);
		
		while(1)
		{
			printBoard(board);
		
			/* if the player made their move and it was valid, update the board */
			if ( checkPlayerMove(board, playerMove(movePlayer), 'O', 'X') )
			{
				printf("\nYou move %d,%d\n", movePlayer[0], movePlayer[1]);
				board = updateBoard(board, movePlayer, 'O', 'X');		
			}
			
			/* Check if player won the game before letting the computer go */
			winner = checkWinner(board);
			if ( winner != '0' ) 
			{
				/* if the player won, computer erases his last move and never performs it again */
				computer = forgetMove(computer, moveComputer[0], moveComputer[1]);				
				break;
			}
					
			/* Computer makes his move, updates his allowed move list as needed */		
			if ( computerMove(board, computer, moveComputer) )
			{
				printf("\nI move %d,%d\n", moveComputer[0], moveComputer[1]);
				board = updateBoard(board, moveComputer, 'X', 'O');
				
				/* if the move is not in the allowed list, put it in there */
				if ( !checkAllowedMoves(computer, moveComputer[0], moveComputer[1]) )
				{
					computer = updateAllowedMoves(computer, moveComputer[0], moveComputer[1]);
				}		
			}
			else
			{			
				/* if the computer can't move, computer erases his last move and never performs it again and resigns */
				computer = forgetMove(computer, moveComputer[0], moveComputer[1]);
				printf("\nI resign, you win!\n");
					
				winner = 'O';
				break;
			}
			
			/* Check if computer won the game before letting the player go */
			winner = checkWinner(board);		
			if ( winner != '0') {break;}		
		}
		
		/*print the final board, and who the winner is */
		system("clear");
		printf("\n\n*************************\n");
		printf("**    Winner is:  %c    **\n", winner);
		printf("*************************");
		printBoard(board);	
		
		printAllowed(computer);
		printDeleted(computer);	
	}
	
	free(movePlayer);
	free(moveComputer);

	
	return 1;
}
