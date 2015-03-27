//NAME: Mike Sadowski
//STUDENT NUMBER: 0864810
//DATE: September 12th, 2013


//INCLUDE STATEMENTS
#include <stdio.h>

//CONSTANTS
#define magicBMInum 703

//PROTOTYPES
float CalculateBMI(float Height, float Weight);
void printBMIinfo(float BMI, float height, float weight);

void main(void)
{
	float weight = 0.0;
	float height = 0.0;
	float bmi = 0.0;

	system("clear");
	printf("Please enter a height: ");
	scanf("%f", &height);	

	printf("\nPlease enter a weight: ");
	scanf("%f", &weight);	

	bmi = CalculateBMI(height, weight);//Calculate BMI
	printBMIinfo(bmi, height, weight);//Print user's bmi, height and weight
}



//NAME: CalculateBMI
//DESCRIPTION: Calculate the users Body Mass Index based on their height and weight
//PARAMETERS: Two floats representing height and weight
//RETURNS: New BMI as a float
float CalculateBMI(float height, float weight)
{
	float newBMI = 0.0;
	
	//BMI = ( Weight in Pounds / ( Height in inches x Height in inches ) ) x 703
	newBMI = ((weight / (height * height)) * magicBMInum);

	return newBMI;
}



//NAME: printBMIinfo
//DESCRIPTION: Print the users Body Mass Index, their height and weight
//PARAMETERS: Three floats representing BMI, height and weight
//RETURNS: NONE
void printBMIinfo(float BMI, float height, float weight)
{
	system("clear");
	printf("Height: %.4f\n", height);
	printf("Weight: %.4f\n", weight);
	printf("BMI:    %.4f\n", BMI);
	printf("\n\n");
}



