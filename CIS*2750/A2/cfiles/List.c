/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

/*A lot of this is my interpretation of the C++ code from:
www.mycodinglab.com/abstract-data-type-lists-in-c
*/

#include "List.h"

/* createList
	DESCRIPTION: creates a new list object

	PRE: none
	POST: returns a new list object, that has all the values initialized and malloc'd.
*/
List* createNewList(void)
{
	List* newList = malloc(sizeof(List));
	if (newList == NULL)
	{
	    return NULL;
	}

	newList->size = 1;
	newList->data = malloc(sizeof(void*) * newList->size);
	newList->count = 0;
	newList->ptr = 0;

	return newList;
}

/* deleteList
	DESCRIPTION: deletes a list object

	PRE: none
	POST: returns a new list object, that has all the values initialized and malloc'd.
*/
void deleteList(List* l)
{
	int i = 0;
	
	if (l != NULL)
	{
		for (i = 0; i < l->count; i++)
		{
			free(l->data[i]);
		}

		free(l->data);
		free(l);
	}
}

/* headOfList
	DESCRIPTION: set pointer to head of list

	PRE: a list exists
	POST: position is now the first element in the list, returns the new head pointer
*/
List* headOfList(List* l)
{
	if (l->count == 0)
	{
		return NULL;
	}
	else
	{
		l->ptr = 1;
		return l;
	}
	return l;
}

/* endOfList
	DESCRIPTION: set pointer to end of list

	PRE: a list exists
	POST: position is now the last element in the list, returns the new pointer to the end of the list
*/
List* endOfList(List* l)
{
	if (l->count == 0)
	{
		return NULL;
	}	
	else
	{
		l->ptr = l->count;
		return l;
	}
	return l;
}

/* nextInList
	DESCRIPTION: return pointer to next element in the list

	PRE: none
	POST: element is inserted into the list
*/
List* nextInList(List* l)
{
	if(l->ptr >= l->count || l->count == 0)
	{
		return NULL;		
	}
	l->ptr++;
	return l;
}

/* addAfterPointer
	DESCRIPTION: insert a new element immediately after the current on

	PRE: none
	POST: element is inserted into the list
*/
List* addAfterPointer(List* l, void* data)
{
	int i = 0;

	if (l->ptr == 0)
	{
		l->ptr = 1;/*shift ptr to first spot (beginning of list)*/
	}
	
	if(l->count + 1 >= l->size)/*check to see if the list needs to be resized*/
	{
		l->size += 5;
		l->data = realloc(l->data, sizeof(void*) * l->size);
		if(!l->data)
		{
			return NULL;
		}
	}

	if(l->count == 0)/*list empty*/
	{
		l->data[0] = data;/*if the count of the list was 0, insert data to first position*/
	}
	else
	{
		for (i = l->count - 1; i >= l->ptr; i--)
		{
			l->data[i + 1] = l->data[i];/*shift all element over one*/
		}
		l->data[l->ptr] = data;/*insert new element*/		
	}

	l->count += 1;/*increase count to account for new element*/
	return l;
}

/* getCurrentElement
	locate, return the data from an element in the list.

	PRE: a list exists
	POST: returns the data from the element
*/
void* getCurrentElement(List* l)
{
	if (l->count == 0)
	{
		return NULL;/*list was empty*/
	}
	return l->data[l->ptr-1];

}

/* removeFromList
	locate, return the data from an element in the list. Element is then removed from the list.

	PRE: a list exists
	POST: returns the data from the element, and removes the element
*/
void* removeFromList(List* l)
{
	int i;
	void* dataElement;
	
	if (l->count == 0)
	{
		return NULL;
	}
	dataElement = l->data[l->ptr-1];

	if (l->count > 1)
	{
		for (i = l->ptr - 1; i < l->count-1; i++)
		{
			l->data[i] = l->data[i+1];/*move over one, removing current element*/
		}
		l->count-=1;
		l->ptr-=1;
	}
	else/*list had one element, set everything to 0 to remove it*/
	{
		l->count = 0;
		l->ptr = 0;
	}
	return dataElement;
}
