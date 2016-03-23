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
	int *moveComputer = (int *)malloc(sizeof(int) * 2);
	int *movePlayer = (int *)malloc(sizeof(int) * 2);
	int *prevMoveComputer = (int *)malloc(sizeof(int) * 2);
	int playerScore = 0;
	int computerScore = 0;
	
	printUsage();
	
	srand(time(NULL));
	computer = createComputer(computer);
		
	while(1)
	{
		board = createBoard(board);
		printBoard(board);
		
		while(1)
		{		
		    while (!checkPlayerMove(board, playerMove(movePlayer), 'O', 'X'))
		    {	
				printf("\n\nInvalid move! Try again.. \n");
				printBoard(board);
			}
			
			/* if the player made their move and it was valid, update the board */
			printf("\nYou move %d,%d\n", movePlayer[0], movePlayer[1]);
			board = updateBoard(board, movePlayer, 'O', 'X');		
			printBoard(board);
			
			/* Check if player won the game before letting the computer go */
			winner = checkWinner(board);		
			if ( winner != '0') 
			{
				playerScore++;
				computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]);
				break;
			}
						
			if ( !checkAvailableMoves(board, 'X', 'O') ) 
			{ 
				winner = 'O';
				computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]); 
				playerScore++; 
				break;
			}
					
			/* Computer Moves */			
			if ( !computerMove(board, computer, &moveComputer) )
			{
				computer = findComputerMoves(board, computer);
				
				if ( !computerMove(board, computer, &moveComputer) )
				{
					printf("I resign, you win\n");
					computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]);
					break;
				}
			}
			
			/* save computer's previous move incase he needs to remove the move */
			prevMoveComputer[0] = moveComputer[0];
			prevMoveComputer[1] = moveComputer[1];
			
			/* Computer makes his move, updates his allowed move list as needed */	
			printf("\nI move %d,%d\n", moveComputer[0], moveComputer[1]);
			board = updateBoard(board, moveComputer, 'X', 'O');	
			printBoard(board);
			
			winner = checkWinner(board);		
			if ( winner != '0') {computerScore++; break;}
			if ( !checkAvailableMoves(board, 'O', 'X') ) { winner = 'X'; computerScore++; break;}								
		}
		
		/*print the final board, and who the winner is */
		system("clear");
		printf("\n\n**********************************\n");
		printf("**         Winner is:  %c        **\n", winner);
		printf("**    Score - You: %d  Me: %d     **\n", playerScore, computerScore);
		printf("**********************************\n");
		printBoard(board);	
		printAllowed(computer);
		
		
		printf("\n\nNew game!\n");	
	}
	
	free(movePlayer);
	free(moveComputer);
	free(prevMoveComputer);
	
	return 1;
}
