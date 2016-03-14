* Name:         Michael Sadowski
* ID:           0864810
* Course:       CIS*3190

* Assignment 3: BABYLONIAN SQUARE ROOTS

* This program calculates a square root of a number using the BABYLONIAN SQUARE ROOTS formula.
* It calculates an initial approximation of the final result by dividing the inputted number by 2
* It divides the inputted number by the approximation
* It adds the result of the divide to the initial approximation, and averaging the numbers by dividing by 2
* This new value becomes the new approximation, and the program repeats the above processes for the new approximation
* It loops 33 times because I found that to be accurate enough
* If a negative value was entered, INVALID INPUT is displayed 

* This file holds the EXTERNAL procedure to calculate the square root
* Parameter are the user's inputted number, and a variable to store the result of the square root
* Final result is placed in the LS-resultBabylonian variable, that is "returned" to the calling function
* -------------------------------------------------------------------------------------------------------------------

IDENTIFICATION DIVISION.
PROGRAM-ID. SQROOT.

DATA DIVISION.
  WORKING-STORAGE SECTION.
        01      resultApproximation     PIC 9(11)V9(10)  VALUE ZEROS.
        01      IterCount               PIC 99          VALUE ZEROS.
        01      result                  PIC 9(11)V9(6)  VALUE ZEROS.
        01      num                     PIC 9(11)V9(10)  VALUE ZEROS.

   LINKAGE SECTION.
   	01 	LS-number 		PIC 9(11)V9(6)  VALUE ZEROS.
   	01 	LS-resultBabylonian	PIC 9(11)V9(10)  VALUE ZEROS.


PROCEDURE DIVISION USING LS-number, LS-resultBabylonian.
*	Reset the counter
	MOVE 0 TO IterCount

*	get an initial approximation (num/2)
	DIVIDE LS-number BY 2 GIVING resultApproximation

*	Calculate the square root using the babylonian method
        PERFORM UNTIL IterCount = 33
*		 divide number by approximation
                DIVIDE LS-number BY resultApproximation GIVING result

*		add the numbers together and divide by 2 to average the numbers
*		use result as the next approximation		
                ADD resultApproximation TO result GIVING result
                DIVIDE result BY 2 GIVING resultApproximation
                ADD 1 TO IterCount
        END-PERFORM

*	return the result
	MOVE resultApproximation TO LS-resultBabylonian
EXIT PROGRAM.
