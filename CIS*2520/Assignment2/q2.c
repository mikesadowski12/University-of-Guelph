/*
#NAME: Mike Sadowski
#DATE: October 14th, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 2
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STACKSIZE 15
#define MAXSIZE 9999

/*stack structure*/
typedef struct stack
{
	double array[STACKSIZE];
	int top;
}stack;

void createNewStack(stack *s);
double doExpression(char operation, double number1, double number2);
void push(stack *s, double number);
double pop(stack *s);

int main(int argc, char *argv[])
{
	stack myStack;
	char theExpression[MAXSIZE] = {0};
	double number1 = 0;
	double number2 = 0;
	double total = 0;
	int i = 0;

	/*check for the argument*/
	if (argc != 2)
	{
		printf(">>>> Please provide one postfix expression as a command line argument!\n");
		return 1;
	}

	strcpy(theExpression, argv[1]);/*copy the expression into a buffer*/
	createNewStack(&myStack);/*initialize top to 0*/	
	for (i = 0; i < strlen(theExpression); i++)
	{
		if(isdigit(theExpression[i]))
		{	
			push(&myStack, (double)theExpression[i]-'0');/*if the character is a digit,subtract '0' to get it's integer 								value and push the integer value on the stack instead of the ASCII value*/
		}
		else
		{
			number2 = pop(&myStack); /*pop last number off the stack, it is the 2nd number in the expression*/
			number1 = pop(&myStack); /*pop first number off the stack, it is the 1st number in the expression*/
			total = doExpression(theExpression[i], number1, number2);/* evaulate the expression*/
			push(&myStack, total);/* push the total back onto the stack*/
		}

	}

	total = pop(&myStack);/*whatever is left in the stack is the new total*/
	printf("Expression: %s\n", argv[1]);
	printf("Answer: %0.2lf\n", total);
	return 0;
}

/*initialize the top of the stack to be 0*/
void createNewStack(stack *s)
{
	s->top = 0;
}

/*evaulature the expression*/
double doExpression(char operation, double number1, double number2)
{
	/*perform the operation on the 2 numbers*/
	if(operation=='+'){return number1+number2;}
	if(operation=='-'){return number1-number2;}
	if(operation=='*'){return number1*number2;}
	if(operation=='/'){return number1/number2;}
	return 0.00;/*if there was bad input, return 0*/
}

/*This function was taken out of the slides from the course website
it pushes a value onto the stack
*/
void push(stack *s, double number)
{
	if(s->top >= STACKSIZE-1)
	{
		printf("\nStack is full");
		return;
	}
	s->top++;
	s->array[s->top] = number;
}

/*This function was taken out of the slides from the course website, but modified to return a double
instead of manipulating a pointer.
It pops a value off of the top of the stack and returns it
*/
double pop(stack *s)
{
	double number = 0;

	if(s->top < 0)
	{
		printf("\nStack is empty");
		return 0;
	}
	number = (float)s->array[s->top];
	s->top--;
	return number;
}
