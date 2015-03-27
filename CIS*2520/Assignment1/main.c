/*
#NAME: Mike Sadowski
#DATE: September 21st, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ackermannMain (void);
void carbonMain (void);
void newtonMain (void);

int main (void)
{
	char choice = 0;	

	do
	{
		system("clear");
		printf("1. Carbon Function\n");
		printf("2. Ackermann Function\n");
		printf("3. Newton Function\n");
		printf("4. Exit\n");
		printf("Choice: ");

		choice = getchar();

		if(choice == '1')
		{
			carbonMain();
		}
		else if (choice == '2')
		{
			ackermannMain();
		}
		else if (choice == '3')
		{
			newtonMain();
		}
		else
		{
			break;
		}

		printf("\n\nPress any key to continue...");	
		getchar();
		getchar();

	}while(choice != 4);

	return 1;
}
