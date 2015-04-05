/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "Boolean.h"

/*A lot of this is from:
www.mycodinglab.com/abstract-data-type-lists-in-c

and 

https://github.com/Bananattack/uoguelph/tree/master/CIS2520
*/

typedef struct List
{
	int count;/*number of elements in the entire list*/
	int size;/*total size of the list*/
	int ptr;/*position of the pointer into the list*/
	void** data;
	char *type;
} List;

List* createNewList(void);
void deleteList(List* l);
List* headOfList(List* l);
List* endOfList(List* l);
List* nextInList(List* l); 
List* addAfterPointer(List* l, void* data); 
void* getCurrentElement(List* l); 
void* removeFromList(List* l);
List* addBeforePointer(List* this, void* data); 

#endif
