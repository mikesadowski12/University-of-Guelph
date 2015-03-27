/*                            Filename: a3.c 
 
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

#include <stdio.h>
#include <stdlib.h>
void main(void)
{
	int randNumber1 = 0; 
	int randNumber2 = 0; 
	int score = 0;
	int sizeOfDeck = 14;
	char MenuSelection = 0;
	
	system("clear");
	
	//high (1), low (2), or quit(0)
	do
	{
		srand (time(NULL));
		randNumber1 = rand()%sizeOfDeck;
		
		srand (time(NULL));
		randNumber2 = rand()%sizeOfDeck;
				
		//loop until user inputs either a 0 1 or 2
		do
		{
			printf("The current card is a %d.\n", randNumber1); 
		    printf("Will the next card be higher(1) or lower(2)? (press 0 to quit)\n");
			MenuSelection = getchar();
			
			if (MenuSelection == '0' || MenuSelection == '1' || MenuSelection == '2')
			{
				break;
			}
			else
			{
				system("clear");
			}
			
		}while(MenuSelection != '0' || MenuSelection != '1' || MenuSelection != '2');//loop until the input is a 0 1 or 2
		
		if (MenuSelection == '1' || MenuSelection == '2')//if user did not wish to quit, go into the loop to check their input..
		{
			do
			{
				if (MenuSelection == '1')//if they hit 1, check if the first number is higher than the 2nd, increase or decrease their score accordingly
				{
					if (randNumber1 > randNumber2)
					{
						printf("You have guessed correctly.\n");
						score++;
						printf("Your current score is %d!\n", score);//update score and print
						break;
					}
					else
					{
						printf("You have guessed inccorrectly.\n");
						score--;
						printf("Your current score is %d!\n", score);//update score and print
						break;
					}					
				}
			
				else if (MenuSelection == '2')//if they hit 2, check if the first number is lower than the 2nd, increase or decrease their score accordingly
				{
					if (randNumber1 < randNumber2)
					{
						printf("You have guessed correctly.\n");
						score++;
						printf("Your current score is %d!\n", score);//update score and print
						break;
					}
					else
					{
						printf("You have guessed inccorrectly.\n");
						score--;
						printf("Your current score is %d!\n", score);//update score and print
						break;
					}
					
					
				}
			
			}while(MenuSelection == '1' || MenuSelection == '2' );//loop while the user input is a 1 or 2..
		}
		
		else //user hit 0 to quit, so break out of the main loop and exit
		{
			break;
		}	
		
		
		
	}while(MenuSelection != '0');
	
	system("clear");
	printf("Your final score is %d!\n", score);//always print the final score before exiting
}
