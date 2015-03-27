#NAME: Mike Sadowski
#DATE: September 21st, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 1

======Important Notes:============
-no user checking is implemented(assignment did not specify any user input requirements)
-720 combination outputted by carbon recursion method
-maximum ackermann value allowed after testing was A(4,0)=13, since A(4,1)=65533 which is too large to store into an integer
-to time the 2 functions in Q3, use ./recursion and ./loop in the directory after compiling to be able to run each seperately with 'time ./loop' to see the execution time of both functions since the menu does not allow timing with command line

======Compilation/Running:==============
1: locate directory with all required c files (main.c, carbon.c,ackermann.c, newton.c, newtonRecursionTimed.c, newtonLoopTimed.c and makefile) in terminal
2: type 'make' 
3: typing in './a1' - runs main program, allowing user to use all functions in a menu
             './recursion' - allows recursion method for Q3 to be timed 
             './loop' - allows loop method for Q3 to be timed 

======Sample Output:============ 
---carbon.c:------------
r,n,b,o,a,c,
r,o,n,b,a,c,
r,n,o,b,a,c,
b,r,o,n,a,c,
b,r,n,o,a,c,
o,r,b,n,a,c,
n,r,b,o,a,c,
o,r,n,b,a,c,

(There should be 720 combinations like these)

---ackermann.c:--------------

A(2,1) = 5
A(2,2) = 7
A(2,3) = 9
A(2,4) = 11
A(2,5) = 13
A(3,0) = 5
A(3,1) = 13
A(3,2) = 29
A(3,3) = 61
A(3,4) = 125
A(3,5) = 253
A(4,0) = 13

(Using A(4,0) is the maximum value since A(4,1) is 65533 which is too large to store into an integer)

---newton.c------

Please enter a number to calculate it's square root: 16
Please enter the accuracy: 0.0001

Recursion Method:
Square root of 16 with accuracy of 1.000000e-04 is 4.100000e+00

Loop Method:
Square root of 16 with accuracy of 1.000000e-04 is 4.100000e+00

(Function calculates using both recursion and loop methods at once, to indivually time them there is ./recursion and ./loop that run the same functions, but without the menu)

======Sources:============
www.cs.colb.edu/maxwell/courses/tutorials/maketutor/
The Textbook




