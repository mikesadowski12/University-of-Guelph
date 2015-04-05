/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

#include <stdlib.h>
#include <string.h>
#include "List.h"

typedef struct ParameterList
{
	List *paramList;
}ParameterList;

char* mallocNewString(char* value);
ParameterList *PL_create(List *l);
char *PL_next(ParameterList *pl);
void PL_destroy(ParameterList *pl);

