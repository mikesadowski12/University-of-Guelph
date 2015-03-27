/*                            Filename: a4.c 
 
   Student Name: Michael Sadowski                       Student Number:  0864810
   Date: October 2nd, 2013                        Course Name: CIS1500 (Intro to Programming)
   
   I have exclusive control over this submission via my password.
   By including this statement in this header comment, I certify that:
       1) I have read and understood the University policy on academic integrity;
       2) I have completed the Computing with Integrity Tutorial on Moodle; and
       3) I have achieved at least 80% in the Computing with Integrity Self Test.
  I assert that this work is my own. I have appropriately acknowledged any and all material
   (data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
   Furthermore, I certify that this assignment was prepared by me specifically for this course.
*/


#include<stdio.h>
#include<string.h>
#define MAX 100
#define ERROR 9
#define ADDITIONFLAG 101
#define MULTIPLICATIONFLAG 102
#define ERROR2 'x'

int mathFlashCardMaker(int *numOne, int *numTwo, int flag);
char printMenuAndCheckInput(void);
int flashCardDisplay(int correctNum, int numOne, int numTwo, char addOrMultiply, int score, int questionNum);
int atoi();

int main(void)
{
	int firstNum = 0;
	int secondNum = 0;
	int correctNum = 0;
	char userInput = 0;
	int score = 0;
	int x = 0;
	
	int system();
	system("clear");
	printf(">>>   Welcome to the Math Flashcard Game! <<<");

	do
	{
		system("clear");
		userInput = printMenuAndCheckInput();
		score = 0;/*reset score for each round*/
		
		if (userInput == 'a')
		{
			for (x = 0; x <= 5; x++)
			{
				correctNum = mathFlashCardMaker(&firstNum, &secondNum, ADDITIONFLAG);
				score += flashCardDisplay(correctNum, firstNum, secondNum, '+', score, x);
			}
		}
		
		if (userInput == 'm')
		{
			for (x = 0; x <= 5; x++)
			{
				correctNum = mathFlashCardMaker(&firstNum, &secondNum, MULTIPLICATIONFLAG);
				score += flashCardDisplay(correctNum, firstNum, secondNum, 'X', score, x);
			}
		}		
		
		if (userInput == 'q')
		{
			break;	
		}	
		
	}while(userInput != 'q');


	return 0;
}



/*
 * NAME: printMenuAndCheckInput
 * DESCRIPTION: prints a menu for the user, and ensures correct input is taken
 * PARAMETERS: none
 * RETURN: a character indicating either addition (a), multiplication (m), or quit (q) was chosen
*/
char printMenuAndCheckInput(void)
{
	char userOption = 0;
	char allowedInput[6] = {'a', 'A', 'm', 'M', 'q', 'Q'};/*array that stores the only allowed input characters for the menu*/
	int x = 0;
	int goodInputFlag = 0;

	/*loop until user inputs either an 'a', 'm' or 'q', or any of those chars in capitals*/
	do
	{	
		printf("\n>>>   Choose an option from the menu by pressing the corresponding letter in the parantheses  <<< ");
		printf("\n>>-------------------<<");
		printf("\n>> (a)ddition        <<");
		printf("\n>> (m)ultiplication  <<");
		printf("\n>> (q)uit            <<");
		printf("\n>>-------------------<<");
		
		userOption = getchar();
		getchar();/*clear keyboard buffer*/

		/*cycle through the array to find a match*/
		for (x = 0; x <= 5; x++)
		{
			if (userOption == allowedInput[x])
			{
				goodInputFlag = 1;
				return userOption;
			}
		}
		
		system("clear");
		printf("\n\n>>> Invalid input Detected! <<<");
		printf("\n>>> Please try again!       <<<\n\n");
		
	}while(goodInputFlag == 0);/*loop until the flag is anything but 0, so until user inputs either an 'a', 'm' or 'q', or any of those chars in capitals*/
	
	/*if the user inputted the correct letter in capitals, this switch block will ensure a lower case will get returned. */
	switch (userOption)
	{
		case 'A':
			return 'a';
			
		case 'M':
			return 'm';
			
		case 'Q':
			return 'q';	
			
		default:
			return userOption;
	}
	
	return userOption;
}

/*
 * NAME: mathFlashCardMaker
 * DESCRIPTION: creates 2 random numbers between 0-9, and returns the total of either the 2 numbers multiplied, or added together 
 * PARAMETERS: 2 integer pointers, and a flag (to decide to return the multiplication total or added total)
 * RETURN: 2 random numbers through pointers, and either the 2 random numbers multiplied, or added together 
*/
int mathFlashCardMaker(int *numOne, int *numTwo, int flag)
{
	int maxRandNum = 8;
	int randNumber1 = 0;
	int randNumber2 = 0;
	
	int rand();
	int srand();
	int time();
	srand (time(NULL));
	randNumber1 = rand()%maxRandNum;
	randNumber2 = rand()%maxRandNum;
	
	/*send the random values back through pointers to be used in main*/
	*numOne = randNumber1;
	*numTwo = randNumber2;
	
	/*depending on the users choice to have multiplication or addition, return the correct answer accordingly..*/
	if (flag == ADDITIONFLAG)
	{
		return (randNumber1 + randNumber2);/*return the correct answer*/
	}
	
	if (flag == MULTIPLICATIONFLAG)
	{
		return (randNumber1 * randNumber2);/*return the correct answer*/
	}
	
	return ERROR;/*since the above returns in the if statements were not executed, there was an error with the flag variable*/
}


int flashCardDisplay(int correctNum, int numOne, int numTwo, char addOrMultiply, int score, int questionNum)
{
	char userGuess[MAX] = {"\0"};
	
	printf("\nYour current score is %d out of %d\n", score, questionNum);
	printf("\nWhat is %d %c %d? ", numOne,  addOrMultiply, numTwo);
	
	fgets(userGuess, sizeof(userGuess), stdin);

	
	if (atoi(userGuess) == correctNum)
	{
		printf("\nCorrect!\n");
		return 1;
	}
	else
	{
		printf("\nIncorrect, the correct answer was %d\n", correctNum);
		return 0;
	}
	
	return ERROR;
}
