/*
#NAME: Mike Sadowski
#DATE: September 21st, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 1
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ackermanFunction(int m, int n);


void ackermannMain (void)
{
	int m = 0;
	int n = 0;

	/*using an ackermann function calculator online, A(4,1)=65533, so that means it will not fit into an integer, 	since an 			integer can only hold -32000 to +32000, so that is how the for loop values came to be. m = 4, and n = 4 - m 			= 0 (or A(4,0) ) would be the last possible calculation.

	for (m = 0; m <= 4; m++)
	{
		for (n = 0; n < 5-m; n++)subtract m to always go 1 less on the next cycle for n
		{
			printf("A(%d,%d) = %d\n", m, n, ackermanFunction(m,n)); initial call of function
		}
	}
	*/
	printf("Keep in mind, max value is m=4 n=0: (4,0)=13 while (4,1)=65533\n");
	printf("Please enter an integer 'm': ");
	scanf("%d", &m);

	printf("Please enter an integer 'n': ");
	scanf("%d", &n);
	
	printf("Result of (%d,%d): %d\n", m,n, ackermanFunction(m,n));

}

/*check the conditions of the 2 numbers, calculate using ackermann function accordingly*/
int ackermanFunction(int m, int n)
{
	/*int returnValue = 0;*/
	
	if (m == 0)
	{
		/*returnValue = n + 1;*/
		/*return returnValue;*/

		return (n+1);/*n+1 for n >=0  */
	}
	else if(n == 0 && m > 0)
	{
		/*returnValue = ackermanFunction(m-1,1);*/
		/*return returnValue;*/

		/*call function again, this time using the new values for m and n*/
		return(ackermanFunction(m-1,1));/*A(m-1,1) for m > 0 and n = 0*/
	}
	else
	{
		/*subtract 1 from m, for n value call function again, using original m value and subtract 1 from n*/
		return(ackermanFunction(m-1,ackermanFunction(m,n-1)));/*A(m-1,A(m,n-1)) for m > 0 and n > 0*/
	}

	/*return returnValue;*/

}
