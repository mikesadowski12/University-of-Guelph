#NAME: Mike Sadowski
#DATE: October 28th, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 3

======Important Notes:============
- could not figure out how to do question 1, just put the working functions i had in for hopefully a few marks at least, a3_1 does not compile properly..
- question 2 prints the contents of the text file, with the keys, calculated from the first 3 elements, as the first elements. Then it prints the final heap, sorted without the keys.

======Compilation/Running:==============
1: locate directory with all required files (a3_1.c tree_functions.c a3_2.c makefile) in terminal
2: type 'make' 
3: typing in './a3_1' - runs question 1
             './a3_2' - runs question 2, reads text file f.dat, creates a heap of it's objects

======Sample Output:============ 
--a3_2.c:
Printing the textfile contents with keys: 

54 25 12 17 82 52 53 5 3 68 64 
90 43 27 20 59 4 84 10 42 43 2 
137 81 14 42 21 9 69 5 30 20 91 
260 96 89 75 0 63 24 54 20 20 24 
185 41 62 82 46 69 42 74 68 79 28 
65 50 9 6 44 59 87 32 36 36 46 

Printing the now-sorted-heap: 

25 12 17 82 52 53 5 3 68 64 
16 14 27 99 29 99 79 45 59 19 
50 9 6 44 59 87 32 36 36 46 
12 0 68 68 49 68 74 32 9 30 
41 82 53 40 29 84 24 61 87 20 
25 41 11 88 15 39 88 69 31 49 
44 27 68 96 70 98 85 13 25 47 
9 83 22 90 74 56 64 75 67 55 

======Sources:============
www.cs.colb.edu/maxwell/courses/tutorials/maketutor/
The Textbook
Slides from moodle (course website) for functions/algorithms
stackoverflow.com/questions/628761/character-to-integer-in-c 



