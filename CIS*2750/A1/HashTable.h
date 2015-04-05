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
so most of it is ripped out of an old assignment,but I also referred to:
stackoverflow.com/questions/142789/what-is-a-callback-in-c-and-how-are-they-implemented
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Boolean.h"
#include "List.h"

typedef int (*HashKeyGen)(void *);
typedef int (*HashKeyEquals)(void *, void*);

typedef struct HTNode
{
	void *data;
	void *HashKey;
} HTNode;

typedef struct HashTable
{
	HashKeyGen hashKey;
	HashKeyEquals hashEQ;
	int size;
	int count;
	List** index;
} HashTable;

HashTable* createTable(int size, HashKeyGen hashKey, HashKeyEquals hashEQ);
void deleteTable(HashTable* t);
void* getTableElement(HashTable* t, void* HashKey);
void addElementToTable(HashTable* t, void* HashKey, void* newValue);
int HashKeyGenerator(void* key);
int HashEquals(void* ls, void* rs);
