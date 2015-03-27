/*
#NAME: Mike Sadowski
#DATE: September 21st, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double newtonLoop(long x, double e, double a);

int main(void)
{
	long x = 64;
	double e = 0.001;
	double a = x/2;

	a = newtonLoop(x,e,a);
	printf("Square root of %lu with accuracy of %e is %e\n",x,e,a);
	return 1;
}

/*square roots a number x with newtons method to the accuracy of e, but using a loop instead of recursion*/
double newtonLoop(long x, double e, double a)
{
	do
	{
		a = (a + (x/a)) / 2;/*calculate a with newtons formula*/
	}while(abs(a * a - x) > e);/*want condition to keep on looping instead of stopping or exiting, so reverse less than*/

	return a;


}
