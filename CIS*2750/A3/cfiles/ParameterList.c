/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

#include "ParameterList.h"

/* PM_mallocNewString
	DESCRIPTION: malloc a char* for a string

	PRE: none
	POST: returns a pointer to a new block for a string
*/
char* mallocNewString(char* value)
{
	char *s = (char *) malloc(sizeof(char) * (strlen(value) + 1));
	strcpy(s, value);
	return s;
}


/* PL_next
	DESCRIPTION: return the next parameter in a parameter list object

	PRE: none
	POST: next parameter is returned, NULL if end of the list
*/
char *PL_next(ParameterList *pl)
{
	if(pl != NULL)
	{
		headOfList(pl->paramList);
		return removeFromList(pl->paramList);
	}
	return NULL;
}

/* PL_create
	DESCRIPTION: creates a new parameter list object

	PRE: q is an already created queue
	POST: returns a new parameter list object initialize to contain the queue of strings,
		NULL if memory allocation failure.
*/
ParameterList *PL_create(List *l)
{
	ParameterList *newPL = malloc(sizeof(ParameterList));
	if(newPL == NULL)
	{
		return NULL;
	}
	newPL->paramList = l;
	return newPL;
}

/* PL_destroy
	DESCRIPTION: destroy a parameter list object

	PRE: none
	POST: all memory is freed
*/
void PL_destroy(ParameterList *pl)
{
	deleteList(pl->paramList);
	free(pl);
}

ParameterList *reverseList(List *l)
{
	ParameterList *tempPList = NULL;
	char *item = NULL;
	List *reverseList = createNewList();
	
	headOfList(l);
	tempPList = PL_create(l);
	
	while(item = PL_next(tempPList))
	{
		endOfList(reverseList);
		addBeforePointer(reverseList,item);	
	}
	
	PL_destroy(tempPList);
	tempPList = PL_create(reverseList);
	
	return tempPList;
}


/* PL_next
	DESCRIPTION: return the next parameter in a parameter list object

	PRE: none
	POST: next parameter is returned, NULL if end of the list
*/
char *PL_next_noRemove(ParameterList *pl)
{
	int x = 0;
	
	if(pl != NULL)
	{
		headOfList(pl->paramList);
		for(x = 0; x < pl->paramList->count; x++)
		{			
			printf("list---%s\n",pl->paramList->data[x]);
		}
	}
	return NULL;
}


