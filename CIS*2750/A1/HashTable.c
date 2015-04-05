/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

/* 
A lot of this hash table code is interpreted from this github I found:
https://gist.github.com/tonious/1377667

The call back stuff was what we used to create Hash functions at Conestoga College,
so most of it is ripped out of an old assignment, but I also referred to:
stackoverflow.com/questions/142789/what-is-a-callback-in-c-and-how-are-they-implemented
*/

#include "HashTable.h"

/* createTable
	DESCRIPTION: create an empty table

	PRE: none
	POST: new table memory allocated, pointer to it returned. NULL return if memory allocation error
*/
HashTable* createTable(int size, HashKeyGen hashKey, HashKeyEquals hashEQ)
{
	int i = 0;
	int x = 0;

	/*Allocate a new table, and a new List* for index*/
	HashTable* newHTable = malloc(sizeof(HashTable));
	if (newHTable == NULL)
	{
		return NULL;
	}
	newHTable->index = malloc(sizeof(List*) * size);
	if(newHTable->index == NULL)
	{
		free(newHTable);
		return NULL;
	}
	
	for(i = 0; i < size; i++)/*create and malloc a new list for every element of the table*/
	{
		newHTable->index[i] = createNewList();
		if(newHTable->index[i] == NULL)/*if error, free each list one by one, then the table, and return null*/
		{
			for(x = 0; x < i; x++)/*free all elements that were malloc'd*/
			{
				deleteList(newHTable->index[x]);
			}
			free(newHTable->index);
			free(newHTable);
			return NULL;
		}
	}

	/*initialize the newly malloc'd table*/
	newHTable->size = size;
	newHTable->count = 0;
	newHTable->hashKey = hashKey;
	newHTable->hashEQ = hashEQ;

	return newHTable;
}

/* deleteTable
	DESCRIPTION: delete an entire hash table

	PRE: hash table exists
	POST: hash table is deleted
*/
void deleteTable(HashTable* t)
{
	int i = 0;
	for(i = 0; i < t->size; i++)
	{
		deleteList(t->index[i]);/*iterate and delete each list in the table*/
	}
	free(t->index);/*free pointers*/
	free(t);
}

/* getTableElement
	DESCRIPTION: find the data that maps to the hash key provided

	PRE: a table exists
	POST: return data that maps to the hash key, NULL if an error occurs
*/
void* getTableElement(HashTable* t, void* HashKey)
{
	HTNode* node = NULL;
	int index = t->hashKey(HashKey) % t->size;

	headOfList(t->index[index]);
	do 
	{
		node = (HTNode*) getCurrentElement(t->index[index]);
		if(node != NULL  && t->hashEQ(node->HashKey, HashKey))
		{
			return node->data;/*find the element using the hash key, and if the node exists, return it*/
		}
	} while(nextInList(t->index[index]) != NULL);
	return NULL;/*if node was not found, return null*/
}

/* addElementToTable
	DESCRIPTION: add an element into the hash table using a hash key

	PRE: a hash table exists
	POST: element is inserted into the hash table based on it's hash key generated
*/
void addElementToTable(HashTable* t, void* HashKey, void* newValue)
{
	HTNode* node = NULL;
	int index = t->hashKey(HashKey) % t->size;
	bool found = false;

	headOfList(t->index[index]);
	/* Loop until we either find the entry or reach the end of the list. */
	do 
	{
		node = (HTNode*) getCurrentElement(t->index[index]);
		if(node != NULL && t->hashEQ(node->HashKey, HashKey))
		{
			found = true;
			break;
		}
	} while(nextInList(t->index[index]) != NULL);

	/* If we didn't find the key earlier, make a new node with this key */
	if(!found)
	{		
		node = malloc(sizeof(node));
		node->HashKey = HashKey;
		node->data = newValue;
		addAfterPointer(t->index[index], node);
		t->count++;
	}
	else
	{
		fprintf(stderr, "\n\tERROR: Attempting to overwrite existing key.\n");
		exit(-1);	
	}
}

/* HashKeyGenerator
	DESCRIPTION: generates a hash key for "key" (NOTE: I DID NOT WRITE THIS FUNCTION, SEE REFERENCE AT TOP OF FILE)

	PRE: none
	POST: hash key generated based on the key provided
*/
int HashKeyGenerator(void* key)
{
	int i = 0;
	int hash = 0;
	char* s = key;
	int len = 16;

	len = (len < strlen(s)) ? len : strlen(s);

	while(i < len)
	{
		hash += (int) s[i];
		i++;
	}
	return hash;
}

/* HashEquals
	DESCRIPTION: collision detector for a hash table (NOTE: I DID NOT WRITE THIS FUNCTION, SEE REFERENCE AT TOP OF FILE)

	PRE: none
	POST: returns if keys are the same or not
*/
int HashEquals(void* ls, void* rs)
{
	return !strcmp(ls, rs);
}

