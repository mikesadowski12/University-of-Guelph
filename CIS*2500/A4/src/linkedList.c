/*************************linkedList.c****************************
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

/*Completed all tests, everything tested in the test module works*/
/*isempty works*/
/*printlist works*/
/*destroy list works*/


MusicRec * createRecord(char * title, char * artist, double fileSize, int length, char theType)
{
	MusicRec *newBlock;
	
	newBlock = (MusicRec*)malloc(sizeof(MusicRec));	
	newBlock->title = (char*)malloc(sizeof(char) * 1000);
	newBlock->artist = (char*)malloc(sizeof(char) * 1000);
		
	if( newBlock == NULL)
	{
		return NULL;
	}
	
	/*Set all the new info on the new block*/
	strcpy(newBlock->title, title);
	strcpy(newBlock->artist, artist);
	newBlock->sizeInKB = fileSize;
	newBlock->lengthInSeconds = length;
	newBlock->type = theType;
	newBlock->next = NULL;
	
	return newBlock;/*return the new node of info*/			
}

char * printRecord(MusicRec * toPrint)
{
	char *thePrintString = 0;
	
	thePrintString = (char*)malloc(sizeof(char) * 1000);
	
	/*"Title (Artist):lengthInSeconds[fileSize]" format gets put into a string*/
	sprintf(thePrintString, "%s (%s):%d[%.2f]", toPrint->title, toPrint->artist, toPrint->lengthInSeconds, toPrint->sizeInKB);
	
	return thePrintString;	/*return the string in the format wanted*/
}

void destroyRecord(MusicRec * theRecord)
{
	/*free the char*'s, as well as the entire node itself*/
	free(theRecord->title);
	free(theRecord->artist);
	free(theRecord);	
}

MusicRec * addToFront(MusicRec * theList, MusicRec * toBeAdded)
{
	/*inset the new node to the front of the list*/
	toBeAdded->next = theList;
	
	return toBeAdded;	/*return the new node*/	
}

MusicRec * addToBack(MusicRec *  theList, MusicRec * toBeAdded)
{			
	MusicRec *ptr = theList;
	
	/*loop until the end of the list is found*/
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	
	ptr->next = toBeAdded;/*set the last node next pointer to point to the new node, which is the new end*/
	
	return theList;	
}

MusicRec * removeFromFront(MusicRec * theList)
{
	MusicRec *ptr = theList;
	
	if(theList != NULL)
	{
		/*move the front of the list to be the 2nd node, and return the new pointer to the front (pointer to 2nd node)*/
		ptr = ptr->next;
		return ptr;
	}
	
	return NULL;	
	
}

MusicRec * removeFromBack(MusicRec *  theList)
{
	MusicRec *ptr = theList;
	MusicRec *prev = NULL;
	
	if(theList != NULL)
	{	
		/*find the end of the list*/
		while(ptr->next != NULL)
		{
			/*save the 2nd last node in prev*/
			prev = ptr;
			ptr = ptr->next;
		}
		/*set the 2nd last node next pointer to be null, which means its the new end*/
		prev->next = NULL;
		return ptr; /*return the deleted node's pointer*/
	}

	return NULL;		
		
	
}

MusicRec * getLastItem(MusicRec * theList)
{
	MusicRec *ptr = theList;
	
	if(theList != NULL)
	{	
		/*find the end of the list, store the last node in ptr*/
		do
		{
			ptr = theList;
			theList = theList->next;
			if(theList == NULL)
			{
				return ptr;/*when the end is found, return a pointer to the node*/			
			}					
		}while(ptr != NULL);	
	}

	return NULL;		
	
}

bool isEmpty(MusicRec * theList)
{
	if(theList == NULL)
	{
		return true;/*return true if the list is not empty*/		
	}
	
	return false;
	
}

void printList(MusicRec *  theList)
{
	MusicRec *ptr = theList;
	/*go through the list, printing each node*/
	do
	{
		printf("%s\n", printRecord(ptr)); 		
		ptr = ptr->next;/*print the above statement for all the nodes of the list*/		
	}while(ptr != NULL);			
}

void  destroyList(MusicRec * theList)
{
	MusicRec *ptr = NULL;
	
	/*go through the list, destryoing each node*/
	while(theList != NULL)
	{
		/*iterate through the list, deleting and freeing all the nodes*/
		ptr = theList;
		theList = theList->next;
		destroyRecord(ptr);
	}	
	
}

