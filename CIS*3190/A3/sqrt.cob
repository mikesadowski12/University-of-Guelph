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

IDENTIFICATION DIVISION.
PROGRAM-ID. SQRT.

DATA DIVISION.
	WORKING-STORAGE SECTION.
		01	inNumber		PIC S9(11)V9(6)	VALUE ZEROS.
		01      positiveInNumber	PIC 9(11)V9(6)  VALUE ZEROS.
		01 	resultBabylonian	PIC 9(11)V9(10)  VALUE ZEROS.
		01      result			PIC 9(11)V9(6)  VALUE ZEROS.			
	        01	counter			PIC 99		VALUE ZEROS.
		01	negativeFlag		PIC 9(11)V9(6)  VALUE ZEROS.

procedure division.

*	infinite loop because I never increment counter
*	user needs to enter CNTRL-C to exit the program
	PERFORM UNTIL counter = 50

*		always reset the negativeflag to update for the new number
		MOVE 0 TO negativeFlag

*		get the user's input
		PERFORM getNumber

*		check if the number they input was negative, set the negativeflag accordingly
		IF inNumber >= 0 THEN
*			if it was positive, move the number data to an unsigned variable 
			MOVE inNumber TO positiveInNumber
			
*			SQROOT the number
			CALL 'SQROOT' USING positiveInNumber, resultBabylonian
	
*			round the result to the 6 decimal places
			COMPUTE result ROUNDED = resultBabylonian
		ELSE
*			number was negative
			MOVE 1 TO negativeFlag
		END-IF

*		display resulting number
		PERFORM displayResult
	END-PERFORM
	STOP RUN.

* Name: getNumber
* Description: Display the welcome board and the user input section
* Return: the inputted number is saved in the variable "inNumber"
getNumber.
	DISPLAY "".
        DISPLAY "".
        DISPLAY "           SQUARE ROOT APPROXIMATIONS".
        DISPLAY "------------------------------------------------".
	DISPLAY "> Enter number (CNTRL-C to EXIT): ", ACCEPT inNumber.

* Name: displayResult
* Description: Display the resulting number. If it was negative, INVALID INPUT is displayed instead of a value
* Return: none
displayResult.
	DISPLAY "".
	DISPLAY "------------------------------------------------".
	DISPLAY "       NUMBER                      SQUARE ROOT".
	DISPLAY "-------------------            ------------------".
	
*	don't print the value if the number inputted was negative
	IF negativeFlag = 0 THEN
		DISPLAY positiveInNumber, "            ", result
	ELSE
		DISPLAY inNumber, "               INVALID INPUT"
	END-IF.
	DISPLAY "".
        DISPLAY "".	

