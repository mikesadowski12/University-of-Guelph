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

identification division.
program-id. sqroot.

data division.
  working-storage section.
        01      resultApproximation     pic 9(11)V9(10)  value zeros.
        01      IterCount               pic 99           value zeros.
        01      result                  pic 9(11)V9(6)   value zeros.
        01      num                     pic 9(11)V9(10)  value zeros.

  linkage section. 
   	01 	LS-number 		pic 9(11)V9(6)   value zeros.
   	01 	LS-resultBabylonian	pic 9(11)V9(10)  value zeros.

procedure division using LS-number, LS-resultBabylonian.
*	Reset the counter
	move 0 to IterCount

*	get an initial approximation (num/2)
	divide LS-number by 2 giving resultApproximation

*	Calculate the square root using the babylonian method
	perform until IterCount = 33

*		divide number by approximation
		divide LS-number by resultApproximation giving result

*		add the numbers together and divide by 2 to average the numbers
*		use result as the next approximation		
		add resultApproximation to result giving result
		divide result by 2 giving resultApproximation
		
		add 1 to IterCount
	end-perform

*	return the result
	move resultApproximation to LS-resultBabylonian
exit program.
