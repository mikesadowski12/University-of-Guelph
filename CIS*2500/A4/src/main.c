/*************************main.c****************************
Student Name: Michael Sadowski                      Student Number:  0864810
Date: March 22th, 2014                       Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include "linkedList.h"

	
int main(int argc, char* argv[]) 
{
	MusicRec *linkedListPTR = 0;

	/*create the list from the contents of the text file*/
	linkedListPTR = parseMusicFileAndInsertToLL(argv[1], linkedListPTR);
	
	/*Print all required information about the list*/
	printf("%s\n", convertPlayListTime(linkedListPTR));
	printf("%.2f\n", getAverageFileSizeOfList(linkedListPTR));
	printList(linkedListPTR);
	
	/*Destory the list before exiting program*/
	destroyList(linkedListPTR);
	
	return 0;

}


