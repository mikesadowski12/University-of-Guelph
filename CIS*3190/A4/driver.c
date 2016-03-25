/*
#NAME: Mike Sadowski
#DATE: March 17th, 2016
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS3190 A4
*/

/* 
 * This file contains the main game loop for HEXAPAWN
 * It uses the Computer struct, the Gameboard struct, and all of their functions to play.
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
		/* initialize the new game */
		board = createBoard(board);
		printBoard(board);
		
		while(1)
		{		
			/* loop until the player enters a valid move */
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
				
				/* since player won, computer forgets his last move */
				computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]);
				break;
			}	
			/* check if computer pawns are able to move */			
			if ( !checkAvailableMoves(board, 'X', 'O') ) 
			{ 
				printf("I CAN'T MOVE, SO YOU WIN.");
				winner = 'O';
				
				/* since player won, computer forgets his last move */
				computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]); 
				playerScore++; 
				break;
			}
					
			/* Computer Moves */			
			if ( !computerMove(board, computer, &moveComputer) )
			{
				/*if he could not complete a move from his current list, update the list with new moves */
				computer = findComputerMoves(board, computer);
				
				/* if he still cannot move, he resigns and forgets his last move*/
				if ( !computerMove(board, computer, &moveComputer) )
				{
					printf("I RESIGN, YOU WIN.");
					
					/* since player won, computer forgets his last move */
					computer = forgetMove(computer, prevMoveComputer[0], prevMoveComputer[1]);
					break;
				}
			}
			
			/* save computer's previous move incase he needs to remove the move */
			prevMoveComputer[0] = moveComputer[0];
			prevMoveComputer[1] = moveComputer[1];
			
			/* Computer makes his move, his allowed move list was updated if needed */	
			printf("\nI MOVE FROM %d TO %d\n", moveComputer[0], moveComputer[1]);
			board = updateBoard(board, moveComputer, 'X', 'O');	
			printBoard(board);
			
			/* check if computer won before letting the player go */
			winner = checkWinner(board);		
			if ( winner != '0') 
			{
				printf("I WIN.");
				computerScore++; 
				break;
			}
			/* check if the player's pawns are able to move */
			if ( !checkAvailableMoves(board, 'O', 'X') ) 
			{ 
				printf("YOU CAN'T MOVE, SO I WIN.");
				winner = 'X'; 
				computerScore++; 
				break;
			}								
		}
		
		/* print who the winner is */
		printf("\nI HAVE WON %d AND YOU %d OUT OF %d GAMES", computerScore, playerScore, playerScore+computerScore);	
			
		/* begin a new game */		
		printf("\n\nNew game!\n");	
	}
	
	free(movePlayer);
	free(moveComputer);
	free(prevMoveComputer);
	
	return 1;
}
