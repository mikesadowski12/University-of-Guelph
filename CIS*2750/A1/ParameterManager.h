/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

#include <stdlib.h>
#include "Boolean.h"
#include "HashTable.h"
#include "ParameterList.h"
#include "List.h"
#define PARAM_MAX_IDENTIFER_LENGTH 4096

typedef enum {INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, STRING_TYPE, LIST_TYPE } param_t;

union param_value
{
	int int_val;
	float real_val;
	Boolean bool_val;
	char* str_val;
	ParameterList *list_val;
};

/*struct to store the value, type of each parameter. also has a flag to check for initialization for required params*/
typedef struct ParameterValue
{
	param_t ptype;
	union param_value pvalue;
	int initFlag;
}ParameterValue;

typedef struct ParameterManager
{
	HashTable *paramValues;/*paramater values*/
	List *reqParamValues;/*parameters that are required to be initialized*/
	
}ParameterManager;

/*Prototypes*/
ParameterManager * PM_create(int size);
int PM_destroy(ParameterManager *p);
int PM_parseFrom(ParameterManager *p, FILE *fp, char comment);
int PM_manage(ParameterManager *p, char *pname, param_t ptype, int required);
int PM_hasValue(ParameterManager *p, char *pname);
union param_value PM_getValue(ParameterManager *p, char *pname);
char* mallocNewString(char* value);

Boolean __parseListLiteral(char* value, ParameterList** val);
Boolean __parseBooleanLiteral(char* value, Boolean* val);
Boolean __parseRealLiteral(char* value, float* val);
Boolean __parseIntegerLiteral(char* value, int* val);
int PM_hasInitializedAllRequired(ParameterManager* this);
