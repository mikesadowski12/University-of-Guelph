/*
#NAME: Mike Sadowski
#DATE: September 21st, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 6

void permutation(int pos, int *posValue, int *arrayInt, char *permuteString);
void printArray(int *array, char *permuteString);

void carbonMain (void)
{
	char *permuteString;
	int arrayInt[LENGTH] = {0}; /*keep array of 6 integers, each representing a letter in word 'carbon'*/
	int posValue = -1;/*started at -1 to include first permutation*/
	
	permuteString = (char*) malloc(LENGTH);
	
	strcpy(permuteString, "carbon");/*initialize the permute string*/

	permutation(0, &posValue, arrayInt, permuteString);/*initial call*/
}

/*print the permutated string as per the current permutation in the array*/
void printArray(int *array, char *permuteString)
{
	int i = 0;	

	for(i = 0; i < LENGTH; i++)
	{
		printf("%c,", permuteString[array[i]-1]);
	}
	printf("\n");
}

void permutation(int pos, int *posValue, int *arrayInt, char *permuteString)
{
	int p = 0;	

	arrayInt[pos] = ++(*posValue);/*take the next value, and put it into the array*/

	if(*posValue == LENGTH)/*when posValue is maximum, the permutation is ready to print*/
	{
		printArray(arrayInt, permuteString);		
	}
	else
	{
		for(p = 0; p < LENGTH;	p++)/*loop through int array values*/
		{
			if(arrayInt[p] == 0)/*find next unassigned position*/
			{
				permutation(p, posValue, arrayInt, permuteString);/*call itself again with new position*/

			}	
		}

	}
	arrayInt[pos] = 0;/*upon exit, reset the current position to 0*/
	--(*posValue);/*decrement current value of the position*/
	
}



/*code below is all previous attempts*/


/*
	remaining = (char*) malloc(6);
	prefix = (char*) malloc(strlen(remaining)+1);
	
	strcpy(remaining, "permuteString");

void permutation(char *prefix, char* remaining)
{
	int lengthRemaining = strlen(remaining);
	int lengthPrefix = strlen(prefix);
	int i = 0;
	char string1[6] = {""};
	char string2[6] = {""};
	char string3[6] = {""};
	
	printf("pre: %s\n",prefix);
	printf("re: %s\n",remaining);

	if (lengthRemaining == 0)
	{
		printf("%s", prefix);
	}
	else
	{
		for(i = 0; i < lengthRemaining; i++)
		{
			printf("I: %d\n",i);
			strcpy(string3,prefix);
			string3[strlen(string3)] = remaining[i];
			string3[lengthPrefix+1] = '\0';
			printf("4: %s\n",string3);
			getchar();

			strncpy(string1, remaining, i);
			printf("1: %s\n",string1);
			strncpy(string2, remaining+i+1, lengthRemaining-i);
			printf("2: %s\n",string2);

			strcat(string1, string2);
			printf("3: %s\n",string1);
			getchar();
	
			permutation(string3, string1); 
		}

	}

}
*/
/*
void permutation(char *prefix, char* remaining)
{
	char string[6];
	int length = 0;
	printf("%s %s", remaining, prefix);

	if(strlen(remaining) > 0){
		append last character of remaining to prefix, delete it, call permuation again
		length = strlen(prefix);
		
		prefix[length] = remaining[strlen(remaining)-1];copy the last char into prefix		
		prefix[length+1] = '\0';end the string with the new char at the end of it	
		remaining[strlen(remaining)-1] = '\0';remove the last char that was copied

		permutation(prefix,remaining);start again with the new strings
	}
}

*/
