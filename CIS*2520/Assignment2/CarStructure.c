/*
#NAME: Mike Sadowski
#DATE: October 14th, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 2
*/

#include "carStructs.h"

/*update functions switch the value of the node, to the value provided*/ 
CarStructure* update_node_mileage(CarStructure* theNode, int mileage)
{
	theNode->mileage = mileage;
	return theNode;
}
CarStructure* update_node_charge(CarStructure* theNode, double charge)
{
	theNode->charge += charge;
	return theNode;
}
CarStructure* update_node_returnDate(CarStructure* theNode, int returnDate)
{
	theNode->returnDate = returnDate;
	return theNode;
}

/*searches for a node in a list based on the plate number, once found removes it from the list and returns a pointer to a node
to be added to a new list*/
CarStructure* delete_node(CarStructure** Head, char* plateNumber)
{
	CarStructure *thisNode = NULL;
	CarStructure *prev = NULL;
	CarStructure *next = NULL;

	/*if the list is empty, it is the new head of the list*/
	if (*Head == NULL)
	{
		return *Head;	
	}
	/*Find where it can be stored and store it*/
	else
	{
		prev = *Head;/*save the previous node for re-attaching*/
		thisNode = *Head;		
		while (thisNode != NULL)
		{
			next = thisNode->next;/*set a pointer to nodes next pointer, compare node's plate number to one being 							searched*/
			if (strcmp(thisNode->plateNumber, plateNumber) == 0)
			{
				break;/*if plate number was found, break out of loop*/
			}
			/*continue through the list*/
			prev = thisNode;
			thisNode = next;				
		}		
		if (*Head == thisNode)
		{

			*Head = thisNode->next;/*if node was at the top, the new head is it's next pointer, removing it from 							thelist*/ 					
		}
		else
		{
			if(thisNode != NULL)
			{
				prev->next = thisNode->next;/*if node was not at the top, assign the previous node's next pointer to 								  point to the current node's next pointer, removing it from the list*/
			}
		}
		
		if(thisNode != NULL)
		{
			thisNode->next = NULL;/*only do this if the node was not the last one in the list*/
		}
		
		return thisNode;/*return the matched node, now extracted out of the list*/
	}
	return NULL;/*if no match was found, return NULL pointer*/
}

/* 
This function creates a node for a linked list for the "AvailableToRent" struct. Since this is the only struct that
new cars will be added to, this is the only record-create function. Returns the newly created node
*/
CarStructure *createCarStructureNode(int newMileage,int returnDate, double charge, char* newPlateNumber)
{
	CarStructure *newBlock;

	newBlock = (CarStructure *)malloc(sizeof(CarStructure));
	newBlock->plateNumber = (char *)malloc(sizeof(char));
	if (newBlock == NULL)
	{
		printf("Error: No Memory\n");
		return NULL;;	
	}
	newBlock->mileage = newMileage;
	newBlock->charge = charge;
	newBlock->returnDate = returnDate;
	newBlock->next = NULL;
	strcpy(newBlock->plateNumber, newPlateNumber);
	return newBlock;
}

/* MENU OPTION 1
Adds a newly created node to a list 
*/
CarStructure *addNodeToList(CarStructure *Head, CarStructure *newBlock, int sortCode)
{
	CarStructure *thisNode = NULL;
	CarStructure *prev = NULL;
	CarStructure *next = NULL;

	/*if the list is empty, it is the new head of the list*/
	if (Head == NULL)
	{
		Head = newBlock;	
	}
	/*Find where it can be stored and store it*/
	else
	{
		prev = Head;/*save the previous node for re-attaching*/
		thisNode = Head;		
		while (thisNode != NULL)
		{
			next = thisNode->next;/*set a pointer to nodes next pointer, compare node's mileage to current node*/
			if(sortCode == MILEAGESORT)
			{
				if (thisNode->mileage >= newBlock->mileage)
				{
					break;/*if position to place was found, break out of loop*/
				}
			}
			else if(sortCode == RETURNDATESORT)
			{
				if (thisNode->returnDate >= newBlock->returnDate)
				{
					break;/*if position to place was found, break out of loop*/
				}
			}
			/*continue through the list*/
			prev = thisNode;
			thisNode = next;				
		}
		/*set the node to the correct position found in the above loop*/		
		if (Head == thisNode)
		{
			Head = newBlock;/*inserting node at the top of the list*/
		}
		else
		{
			prev->next = newBlock;/*inserting node not at the top of the list*/
		}
		newBlock->next = thisNode;

	}
	return Head;/*always return the head of the list*/
}


/* MENU OPTION 6
Cycles through the list, printing out each node
*/
void printList(CarStructure *Head)
{
	CarStructure *current = Head;

	/*Check if list is empty*/
	if (current != NULL)
	{
		system("clear");
		do/*cycle through te list, print each node*/
		{	
			printf("\n------------------------");
			printf("\nPlateNumber: %s", current->plateNumber);
			printf("\nMileage: %d", current->mileage);			
			printf("\nReturnDate: %d", current->returnDate);
			printf("\nCharge: $%0.2lf", current->charge);
			printf("\n------------------------");
			current = current->next;
		}while(current != NULL);/*keep going until end of list*/
	}
	getchar();/*let user see printed list*/	
	getchar();
}

/*save the list to a text file*/
void saveList(CarStructure *Head, char* fileName)
{
	FILE *fp = fopen(fileName, "w");
	CarStructure *current = Head;

	if (fp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}

	if(current != NULL)/*make sure list is not empty*/
	{
		do/*keep going until end of list*/
		{	
			fprintf(fp, "%d %d %lf %s\n", current->mileage, current->returnDate, current->charge, current->plateNumber); 
			current = current->next;
		}while(current != NULL);
	}
	

	fclose(fp);
}

/*load the list from a text file*/
CarStructure* LoadList(CarStructure *Head, char* fileName, int sortCode)
{
	FILE *fp = fopen(fileName, "r");
	char buffer[MAXSIZE] = {0};
	int i = 0;	
	int mileage = 0;
	int returnDate = 0;
	double charge = 0;
	char plateNumber[MAXSIZE] = {0};
	char *tokens;

	while(fgets(buffer, MAXSIZE, fp) != NULL)
	{	
		i = 0;
		tokens = strtok(buffer, " ");
		while(tokens != NULL)/*loop through the tokens, place each one in the appropriate variable*/
		{
			if(i == 0){mileage = atoi(tokens);}
			if(i == 1){returnDate = atoi(tokens);}
			if(i == 2){charge = atof(tokens);}
			if(i == 3){strcpy(plateNumber, tokens);}
			i++;
			tokens = strtok(NULL, " ");
		}
		/*Remove the newline character from the string*/
		if(plateNumber[strlen(plateNumber)-1] < 33)
		{		
			plateNumber[strlen(plateNumber)-1] = 0;
		}
		/*create node based on the tokens from the string above, send node to be added to the list*/
		Head = addNodeToList(Head, createCarStructureNode(mileage, returnDate, charge, plateNumber), sortCode);	
	}
	fclose(fp);
	return Head;
}
