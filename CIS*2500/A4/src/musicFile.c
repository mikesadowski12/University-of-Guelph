/*************************musicFile.c****************************
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

MusicRec *parseMusicFileAndInsertToLL(char * fileName, MusicRec *headOfList)
{
	FILE *infile = 0;
	char *buffer = 0;
	MusicRec *newElement;
	
	/*Open the file*/
	infile = fopen(fileName,"r");
	if (infile == NULL) 
	{
		printf ("Error opening file!\n"); exit(0);
	}
	
	buffer = (char*) malloc (sizeof(char) *1000);
	
	/*read each line of the file*/
	while(fgets(buffer, 1000, infile))
	{
		newElement = parseLineForInfo(buffer);/*parse the line read for its contents*/
		
		/*according to the type, place the node into the correct place in the list*/
		if(newElement->type == 'a')
		{
			headOfList = addToFront(headOfList, newElement);
		}
		else if(newElement->type == 'b')
		{
			headOfList = addToBack(headOfList, newElement);
		}		
	}
	
	return headOfList;/*return the head of the list*/
	
}

MusicRec *parseLineForInfo(char *line)
{
	char *cutString;
	char tokes[5][100];
	int tokeCount = 0;
	char title[100] = {0};
	char artist[100] = {0};
	int length = 0;
	double size = 0.0;
	char type = 0;
	
	cutString = (char*) malloc (sizeof(char)*1000);
	
	/* CUt the string into tokens based on the space, and put the tokens into the tokes array. [0] = artist, [1] = title, [2] = length, [3]=size, [4]=type*/
	cutString = strtok (line, ",");
	while (cutString != NULL)
	{			
		/*extractNumbers(cutString);*/
		strcpy(tokes[tokeCount], cutString);
		tokeCount++;
		cutString = strtok (NULL, ",");	
	}
	
	/*copy all information to appropriate variable to send to create the node*/
	strcpy(artist,tokes[0]);
	strcpy(title,tokes[1]);
	length = atoi(tokes[2]);
	size = atof(tokes[3]);
	type = tokes[4][0];

	free(cutString);
	return(createRecord(title,artist,size,length,type ));/*return the created node*/
	
}

char *convertPlayListTime(MusicRec *theList)
{
	
	MusicRec *ptr = theList;
	int total = 0;
	char *theReturn = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	
	theReturn = (char*) malloc (sizeof(char)*1000);
	
	/*go through the whole list adding up the lengthInSeconds of every node*/
	while(ptr != NULL)
	{
		total = total + ptr->lengthInSeconds;				
		ptr = ptr->next;
	}	
	
	/*calculate total number of hours, minutes and seconds from total number of seconds*/	
	hours = total / 3600;
	total -= hours * 3600;
	minutes = total / 60;
	total -= minutes * 60;
	seconds = total % 60;
		
	/*put all the info into a formatted string*/
	sprintf(theReturn, "%.2d:%.2d:%.2d", hours, minutes, seconds);
	
	free(theReturn);
	return theReturn;/*return the formatted string*/
	
}

double getAverageFileSizeOfList(MusicRec *theList)
{
	MusicRec *ptr = theList;
	double total = 0;
	int count = 0;
	
	/*go through the whole list adding up the sizeInKb of each node, and counting how many elements there are to calculate the average*/
	while(ptr != NULL)
	{
		total = total + ptr->sizeInKB;
		count++;				
		ptr = ptr->next;
	}

	return (total/count);/*return the average of the sizes*/
	
}
