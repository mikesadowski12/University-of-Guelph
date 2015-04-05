/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

#include "LinkedList.h"

/* createList
	DESCRIPTION: create the head of list

	PRE: none
	POST: returns a pointer to a new list object
*/
ParameterValue *createNode(char *pname, param_t ptype, int required)
{
	ParameterValue *newList = (ParameterValue*) malloc(sizeof(ParameterValue));
	
	if(newList == NULL)
    {
        return NULL;
    } 
       
    newList->pname = (char *) malloc(sizeof(char) * (strlen(pname) + 1));
	if(newList->pname == NULL)
	{
		return NULL;
	}	
	
	strcpy(newList->pname, pname);	
	newList->ptype = ptype;
	newList->next = NULL;
	newList->required = required;
    newList->initFlag = 0;
    
	return newList;
}

/* addToList
	DESCRIPTION: create a new node, add it to end of the list

	PRE: none
	POST: returns a pointer to new node
*/
ParameterValue *addToList(ParameterValue *head, char *pname, param_t ptype, int required)
{
	ParameterValue *newNode = NULL;
	ParameterValue *current = head;
		
    if(head == NULL)
    {
        return NULL;
    }
    
	newNode = (ParameterValue *)createNode(pname, ptype, required);

    while(current->next != NULL)
    {
		current = current->next;
	}
    current->next = newNode;
  
    return head;
}

/* searchList
	DESCRIPTION: locate the node that matches the name

	PRE: none
	POST: returns a pointer to node
*/
ParameterValue* searchList(ParameterValue *head, char *pname)
{
    ParameterValue *tempHead = head;

    while(tempHead != NULL)
    {
        if(strcmp(pname, tempHead->pname) == 0)
        {
            return tempHead;
        }
        tempHead = tempHead->next;
    }
    return tempHead;
}

/* freeList
	DESCRIPTION: free the entire list

	PRE: none
	POST: returns a pointer to new node
*/
ParameterValue* freeList(ParameterValue *head)
{
	ParameterValue *current = head;	
	ParameterValue *prev = head;
	
    do
    {
		prev = current;			
		free(prev->pname);
		free(prev);
		current = current->next;	
	}while(current != NULL);
}

void print_list(ParameterValue *head)
{
	ParameterValue *tempHead = head;
	char *item;

    while(tempHead != NULL)
    {
        printf("\n [%s]--",tempHead->pname);
        printf("--[%d]--",tempHead->ptype);
        
        if(tempHead->ptype == INT_TYPE){printf("--[%d]\n",tempHead->pvalue.int_val);}
        if(tempHead->ptype == REAL_TYPE){printf("--[%f]\n",tempHead->pvalue.real_val);}
        if(tempHead->ptype == BOOLEAN_TYPE){printf("--[%d]\n",tempHead->pvalue.bool_val);}
        if(tempHead->ptype == STRING_TYPE){printf("--[%s]\n",tempHead->pvalue.str_val);}
        if(tempHead->ptype == LIST_TYPE)
        {
			while(item = PL_next(tempHead->pvalue.list_val))
			{
				printf(" [%s]", item);
			}
			
		}
             
        tempHead = tempHead->next;
    }
}
