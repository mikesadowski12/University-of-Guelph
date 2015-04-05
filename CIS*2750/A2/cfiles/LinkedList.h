/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

#include "ParameterList.h"

typedef enum {INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, STRING_TYPE, LIST_TYPE } param_t;

union param_value
{
	int int_val;
	float real_val;
	Boolean bool_val;
	char* str_val;
	ParameterList *list_val;
};

typedef struct ParameterValue
{
	char *pname;
	param_t ptype;
	union param_value pvalue;
	int required;
	int initFlag;
	
	struct ParameterValue *next;
}ParameterValue;

ParameterValue *createNode(char *pname, param_t ptype, int required);
ParameterValue *addToList(ParameterValue *head, char *pname, param_t ptype, int required);
ParameterValue* searchList(ParameterValue *head, char *pname);
ParameterValue* freeList(ParameterValue *head);
void print_list(ParameterValue *head);
