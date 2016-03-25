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
				printf("\n\nILLEGAL CO-ORDINATES.\n");
				printBoard(board);
			}
			
			/* if the player made their move and it was valid, update the board */
			printf("\nYOUR MOVE: %d TO %d\n", movePlayer[0], movePlayer[1]);
			board = updateBoard(board, movePlayer, 'O', 'X');		
			printBoard(board);
			
			/* Check if player won the game before letting the computer go */
			winner = checkWinner(board);		
			if ( winner != '0') 
			{
				printf("YOU WIN.");
				playerScore++;
				computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]);
				break;
			}
						
			if ( !checkAvailableMoves(board, 'X', 'O') ) 
			{ 
				printf("I CAN'T MOVE, SO YOU WIN.");
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
					printf("I RESIGN, YOU WIN.");
					computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]);
					break;
				}
			}
			
			/* save computer's previous move incase he needs to remove the move */
			prevMoveComputer[0] = moveComputer[0];
			prevMoveComputer[1] = moveComputer[1];
			
			/* Computer makes his move, updates his allowed move list as needed */	
			printf("\nI MOVE FROM %d TO %d\n", moveComputer[0], moveComputer[1]);
			board = updateBoard(board, moveComputer, 'X', 'O');	
			printBoard(board);
			
			winner = checkWinner(board);		
			if ( winner != '0') 
			{
				printf("I WIN.");
				computerScore++; 
				break;
			}
			
			if ( !checkAvailableMoves(board, 'O', 'X') ) 
			{ 
				printf("YOU CAN'T MOVE, SO I WIN.");
				winner = 'X'; 
				computerScore++; 
				break;
			}								
		}
		
		/*print the final board, and who the winner is */
		printf("\nI HAVE WON %d AND YOU %d OUT OF %d GAMES", computerScore, playerScore, playerScore+computerScore);
		//printBoard(board);	
				
		printf("\n\nNew game!\n");	
	}
	
	free(movePlayer);
	free(moveComputer);
	free(prevMoveComputer);
	
	return 1;
}
