#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void getArrayOfNumbers(int *myArray);
int checkArrayForNumber(int *array1, int number);
int checkArraysForMatches(int *array1, int *array2);
char printMainMenu(void);
void lotto649Scanner(int numberOfMatches, char *usersName, int prizeTotal);

int main(void)
{
	char usersName[100] = {"\0"};
	char userInput = 0;
	char userInputString[100] = "\0";
	int prizeTotal = 0;
	int inputFlag = 0;
	int ticketNumbers[6] = {0};
	int winningNumbers[6] = {0};
	int numberOfMatches = 0;
	int y = 0;

	printf("Please enter your name: ");
	fgets(usersName, sizeof(usersName), stdin);

	/*get rid of line feed from string*/
	if(usersName[strlen(usersName)-1] < 33)
	{
		usersName[strlen(usersName)-1] = '\0';
	}

	/*ensure a number goes into the total prize pot*/
	do
	{
		printf("\nPlease enter the money to be won: ");
		fseek(stdin,0,SEEK_END);
		scanf("%d", &prizeTotal);
	}while(prizeTotal == 0);

	do
	{
		inputFlag = 0;
		userInput = printMainMenu();

		if (userInput == 'w')
		{
			printf("\n>>Please enter the WINNING numbers one-by-one \n");
			getArrayOfNumbers(winningNumbers);
			inputFlag = 1;
		}

		if (userInput == 't')
		{
			if (winningNumbers[0] != 0)
			{
				fseek(stdin,0,SEEK_END);
				printf("\n>>Please enter the TICKET numbers one-by-one \n");
				getArrayOfNumbers(ticketNumbers);
			}
			else
			{
				printf("\n>>Please enter the WINNING numbers first! \n");
				printf("\n>>Press any key: ");
				fseek(stdin,0,SEEK_END);
				getchar();
				fseek(stdin,0,SEEK_END);
			}
		}

		if (userInput == 'q')
		{
			break;
		}

		/*Check if there have been winning numbers and ticket numbers were inputted before checking them*/
		if (winningNumbers[0] != 0 && ticketNumbers[0] != 0 && inputFlag == 0)
		{
			numberOfMatches = checkArraysForMatches(winningNumbers, ticketNumbers);
			lotto649Scanner(numberOfMatches, usersName, prizeTotal);

			/*reset the ticket numbers*/
			for (y = 0; y <= 5; y++)
			{
				ticketNumbers[y] = 0;
			}
		}
	}while(userInput != 'q');

	return 1;
}

void lotto649Scanner(int numberOfMatches, char *usersName, int prizeTotal)
{
	double winnings = 0.0;

	if (numberOfMatches == 6)
	{
		winnings = (.795 * prizeTotal); 
	}

	if (numberOfMatches == 5)
	{
		winnings = (.05 * prizeTotal);
	}

	if (numberOfMatches == 4)
	{
		winnings = (.095 * prizeTotal);
	}

	if (numberOfMatches == 3)
	{
		winnings = 10;
	}

	if (numberOfMatches == 2)
	{
		printf("\n\n>>Congratulations %s, you have won a free play!", usersName);
	}

	if (numberOfMatches < 2)
	{
		printf("\n>>Sorry %s, you have won nothing!", usersName);
	}

	if(winnings != 0)
	{
		printf("\n>>Congratulations %s, you have won $%f!", usersName, winnings);
	}

	printf("\n>>You had %d/6 numbers correct!", numberOfMatches);
	printf("\n>>Press any key: ");
	fseek(stdin,0,SEEK_END);
	getchar();
	fseek(stdin,0,SEEK_END);
}


char printMainMenu(void)
{
	char userOption = 0;
	char allowedInput[6] = {'w', 't', 'q', 'W', 'T', 'Q'};
	int inputFlag = 0;
	int x = 0;

	do
	{
		system("cls");
		printf(">>**********LOTTO 6/49***********\n");
		printf(">>**                           **\n");
		printf(">>** Enter Winning Numbers (w) **\n");
		printf(">>** Enter Ticket Numbers  (t) **\n");
		printf(">>**       Quit            (q) **\n");
		printf(">>**                           **\n");
		printf(">>*******************************\n");
		/*fgets(userOption,sizeof(userOption), stdin);/*went with a string for easier error checking*/
		userOption = getchar();

		for (x = 0; x <= 5; x++)
		{
			if (userOption == allowedInput[x])
			{
				inputFlag = 1;
				return tolower(userOption);/*always return lower case letter if it was correct input*/
			}
		}

	}while(inputFlag == 0);

	return 0;
}



void getArrayOfNumbers(int *myArray)
{
	char lotteryNumArray[100] = "\0";
	int inputFlag = 0;
	int x = 0;

	for (x = 0; x <= 5; x++)
	{
		inputFlag = 0;
		printf("    >>Enter the number: ");
		fseek(stdin,0,SEEK_END);
		fgets(lotteryNumArray, sizeof(lotteryNumArray), stdin);
		/*scanf("%d", &lotteryNumArray[x]);*/

		/*check if a number was entered, and if it is between 1-49*/
		if (atoi(lotteryNumArray) >= 1 && atoi(lotteryNumArray) <= 49)
		{
			myArray[x] = atoi(lotteryNumArray);
		}
		else
		{
			do
			{
				printf("      >>Re-enter a number between 1-49: ");
				fseek(stdin,0,SEEK_END);
				fgets(lotteryNumArray, sizeof(lotteryNumArray), stdin);
				/*scanf("%d", &lotteryNumArray[x]);*/

				if (atoi(lotteryNumArray) >= 1 && atoi(lotteryNumArray) <= 49)
				{
					myArray[x] = atoi(lotteryNumArray);
					inputFlag = 1;
					break;
				}
			}while(inputFlag == 0);
		}/*end else*/
	}/*end for*/
}/*end funct*/



int checkArraysForMatches(int *array1, int *array2)
{
	int numCounter = 0;
	int x = 0;

	for(x = 0; x <= 5; x++)
	{
		if (checkArrayForNumber(array1, array2[x]) == 1)
		{
			numCounter++;
		}
	}

	return numCounter;
}



int checkArrayForNumber (int *array1, int number)
{
	int x = 0;

	for (x = 0; x < 6; x++)
	{
		if(array1[x] == number)
		{
			return 1;
		}
	}

	return 0;
}