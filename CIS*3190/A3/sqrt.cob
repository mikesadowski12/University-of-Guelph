* Name: 	Michael Sadowski
* ID:   	0864810
* Course:	CIS*3190

* Assignment 3: BABYLONIAN SQUARE ROOTS

* This program calculates a square root of a number using the BABYLONIAN SQUARE ROOTS formula.
* It calculates an initial approximation of the final result by dividing the inputted number by 2
* It divides the inputted number by the approximation
* It adds the result of the divide to the initial approximation, and averaging the numbers by dividing by 2
* This new value becomes the new approximation, and the program repeats the above processes for the new approximation
* It loops 33 times because I found that to be accurate enough
* If a negative value was entered, INVALID INPUT is displayed

* This file holds the main driver for the square root calculator.
* It allows the user to enter input, and then calls the Square Root function from the sqroot.cob file
* After the function returns the result it is printed to the user
* -------------------------------------------------------------------------------------------------------------------

identification division.
program-id. SQRT.

data division.
	working-storage section.
		01	inNumber		pic S9(11)V9(6)	value zeros.
		01      positiveInNumber	pic 9(11)V9(6)  value zeros.
		01 	resultBabylonian	pic 9(11)V9(10) value zeros.
		01      result			pic 9(11)V9(6)  value zeros.			
	        01	counter			pic 99		value zeros.
		01	negativeFlag		pic 9(11)V9(6)  value zeros.

procedure division.

*	infinite loop because I never increment counter
*	user needs to enter CNTRL-C to exit the program
        perform until counter = 50

*		always reset the negativeflag to update for the new number
		move 0 to negativeFlag

*		get the user's input
		perform getNumber
  
*		check if the number they input was negative, set the negativeflag accordingly
		if inNumber >= 0 then

*			if it was positive, move the number data to an unsigned variable 
			move inNumber to positiveInNumber
			
*			Square Root the number
			call 'sqroot' using positiveInNumber, resultBabylonian
			
*			round the result to the 6 decimal places
			compute result rounded = resultBabylonian
		else
*			number was negative
			move 1 to negativeFlag
		end-if

*		display resulting number
		perform displayResult
	end-perform
	stop run.

* Name: getNumber
* Description: Display the welcome board and the user input section
* Return: the inputted number is saved in the variable "inNumber"
getNumber.
	display "".
	display "".
	display "           SQUARE ROOT APPROXIMATIONS".
	display "------------------------------------------------".
	display "> Enter number (CNTRL-C to EXIT): ", ACCEPT inNumber.

* Name: displayResult
* Description: Display the resulting number. If it was negative, INVALID INPUT is displayed instead of a value
* Return: none
displayResult.
	display "".
	display "------------------------------------------------".
	display "       NUMBER                      SQUARE ROOT".
	display "-------------------            ------------------".
	
*	don't print the value if the number inputted was negative
	if negativeFlag = 0 then
		display positiveInNumber, "            ", result
	else
		display inNumber, "               INVALID INPUT"
	end-if
	display "".
	display "".
