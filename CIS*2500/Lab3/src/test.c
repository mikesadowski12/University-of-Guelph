/*************************main.c****************************
Student Name: Michael Sadowski                      Student Number:  0864810
Date: March 8th, 2014                       Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include "list.h"

	
int main(void) 
{
	struct Student *headPtr = NULL;
	struct Student *newElement = NULL; 

	newElement = createRecord(newElement, "Mike", "Sadowski", 123, 67.5);
	headPtr = addToFront(headPtr, newElement);
	newElement = createRecord(newElement, "Mike2", "Sadowski2", 321, 100.0);
	headPtr = addToFront(headPtr, newElement);
	newElement = createRecord(newElement, "Mike3", "Sadowski3", 777, 87.7);
	headPtr = addToFront(headPtr, newElement);
	newElement = createRecord(newElement, "Mike4", "Sadowski4", 999, 100.0);
	headPtr = addToFront(headPtr, newElement);
	
	printStudentLinkedList(headPtr);
	deleteList(headPtr);
		
	return 0;
}


struct Student *createRecord(struct Student *newELement, char *firstName, char *lastName, int studentID, float GPA)
{
	struct Student *newBlock;
	
	newBlock = (StudentRec*)malloc(sizeof(struct Student));	
	if( newBlock == NULL)
	{
		return NULL;
	}
	
	/*Set all the new info on a new block*/
	strcpy(newBlock->firstName, firstName);
	strcpy(newBlock->lastName, lastName);
	newBlock->studentID = studentID;
	newBlock->GPA = GPA;
	
	newELement = newBlock;
	
	return newELement;	
}



void printStudentLinkedList(struct Student *headOfList)
{
	struct Student *ptr = headOfList;
	
	do
	{
		printf("FirstName: %s, LastName: %s, ID: %d, GPA: %f\n", ptr->firstName, ptr->lastName, ptr->studentID, ptr->GPA);  		
		ptr = ptr->next;
		
	}while(ptr != NULL);	
}


void deleteList(struct Student *head)
{
	struct Student *ptr = NULL;
	
	while(head != NULL)
	{
		ptr = head;
		head = head->next;
		free(ptr);
	}

}
