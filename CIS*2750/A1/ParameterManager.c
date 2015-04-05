/*
#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
*/

#include "ParameterManager.h"

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

/* PM_create
	DESCRIPTION: creates a new parameter manager object, mallocs the value table and required parameters list as well

	PRE: size is a positive integer (size > 0)
	POST: returns a new parameter manager object initialize to be empty,
		NULL if memory allocation failure.
*/
ParameterManager * PM_create(int size)
{
	ParameterManager* newPM = malloc(sizeof(ParameterManager));
	if (size > 0 && newPM != NULL)/*if there is a size and the newPM was malloc'd, malloc the internal ADT's and return*/
	{
		newPM->paramValues = createTable(size, HashKeyGenerator, HashEquals);
		if (newPM->paramValues != NULL)/*if the param table was created, create new list*/
		{
			newPM->reqParamValues = createNewList();/*create the list inside of the PM object*/
		}
		else
		{
			free(newPM);/*if there was an error creating the PM required param list*/
			return NULL;
		}

		if (newPM->reqParamValues != NULL)
		{
			return newPM;/*if the PM was created, the table was created, and list created, return PM*/
		}
		else
		{
			free(newPM->paramValues);/*if there was an error creating the PM param list*/
			free(newPM);
			return NULL;
		}
		return NULL;/*ensures a null gets returned, although should never be triggered*/		
		
	}
	else
	{
		return NULL;
	}
}

/* PM_destory
	DESCRIPTION: destroys a parameter manager object, frees the internal list and table ADT's

	PRE: a PM exists
	POST: all memory associated with *p is freed; 
		returns 1 on success, 0 otherwise
*/
int PM_destroy(ParameterManager *p)
{
	deleteList(p->reqParamValues);
	deleteTable(p->paramValues);
	free(p);

	if(p == NULL)
	{
		return 1;/*success*/
	}
	else
	{
		return 0;
	}
}

/* PM_parseFrom
	extract values for parameters from an input stream

	PRE: fp is a valid input stream ready for reading that contains the desired parameters
	POST: All required parameters, and those optional parameters present, are assigned values
		that are consumed from fp, respecting comment as "start of comment" character if 			not null ('\0'); returns non zero on success, 0 otherwise (parse error, memory 
		allocation failure)
*/

int PM_parseFrom(ParameterManager *p, FILE *fp, char comment)
{
	Boolean commentMode = false;
	Boolean nameMode = true;
	Boolean valueMode = false;
	Boolean stringMode = false;

	char nameBuffer[9999] = {0};
	char valueBuffer[9999] = {0};
	char readChar = 0;
	int i = 0;
	ParameterValue* newParameter = NULL;

	if (fp == NULL)
	{
		printf("PARSE ERROR: Input-Stream is NULL\n");
		return 0;
	}

	/*read each character in the stream on by one*/
	while ((readChar = (char) fgetc(fp)) != EOF)
	{
		if (readChar == '\n' && commentMode == true)/*comment mode ended*/
		{
			commentMode = false;
		}
		
		if(stringMode == false && readChar == '"')
		{
			stringMode = true;
		}
		else if(stringMode == true && readChar == '"')
		{
			stringMode = false;
		}

		/*ignore all whitespace and everything if in comment mode*/
		if (readChar != ' ' && readChar != '\t' && commentMode == false || stringMode == true)
		{
			/*Figure out which mode we are in based on the character read in, */
			if (readChar == comment)/*comment mode*/
			{
				commentMode = true;
			}			
			else if (readChar == '=')/*value mode*/
			{
				if(nameMode == false)
				{
					printf("PARSE ERROR: Extra equal sign\n");
					return 0;
				}
				commentMode = false;
				nameMode = false;
				valueMode = true;

				nameBuffer[i] = '\0';/*null terminate the string*/
				i = 0;
			}
			else if (readChar == ';')/*parameter is complete, set the value of the parameter, switch to name mode*/
			{
				if(valueMode == false)
				{
					printf("PARSE ERROR: Extra semi-colon\n");
					return 0;
				}
				commentMode = false;
				nameMode = true;
				valueMode = false;
				newParameter = NULL;

				valueBuffer[i] = '\0';/*null terminate the string*/
				i = 0;

				/*grab the parameter information based on the name parsed*/
				newParameter = getTableElement(p->paramValues, nameBuffer);
				if(newParameter != NULL)/*ignore the parameter if it's not registered*/
				{
					switch(newParameter->ptype)/*determine the type of the parameter, call parse function and save value*/
					{
						case INT_TYPE:
							if(parseIntType(valueBuffer, &(newParameter->pvalue.int_val)) == 0)
							{
								printf("PARSE ERROR: INT_TYPE is invalid\n");
								return 0;
							}
							break;
						case REAL_TYPE:
							if(parseRealType(valueBuffer, &(newParameter->pvalue.real_val)) == 0)
							{
								printf("PARSE ERROR: REAL_TYPE is invalid\n");
								return 0;
							}
							break;
						case BOOLEAN_TYPE:
							if(parseBooleanType(valueBuffer, &(newParameter->pvalue.bool_val)) == 0)
							{
								printf("PARSE ERROR: BOOL_TYPE is invalid\n");
								return 0;
							}
							break;
						case STRING_TYPE:
							newParameter->pvalue.str_val = mallocNewString(valueBuffer);
							break;
						case LIST_TYPE:
							if(parseListType(valueBuffer, &(newParameter->pvalue.list_val)) == 0)
							{
								printf("PARSE ERROR: LIST_TYPE is invalid\n");
								return 0;
							}
							break;
					}	
					newParameter->initFlag = 1;	
				}
				/*clear buffers for next parameter*/
				nameBuffer[0] = '\0';					
				valueBuffer[0] = '\0';			
			}
			/*depending on which mode, store the name or value into the appropriate buffer*/
			else if(nameMode == true && readChar != '\n')
			{
				if ( i >= 9999)
				{
					printf("PARSE ERROR: Pname length exceeds 9999\n");
					return 0;/*string was way too big*/
				}
				nameBuffer[i++] = readChar;/*build the parameter name char by char*/	
			}
			else if(valueMode == true && readChar != '\n')
			{
				if ( i >= 9999)
				{
					printf("PARSE ERROR: Pvalue length exceeds 9999\n");
					return 0;/*string was way too big*/
				}
				valueBuffer[i++] = readChar;/*build the parameter value char by char*/
			}

		}
	}	
	/*if all required params are initialized, return 1, 0 otherwise*/
	if(initializedChecker(p) == 0)
	{
		printf("ERROR: Required Parameter Not Initialized\n");
		return 0;
	}		
	return 1;
}

/* initializedChecker
	DESCRIPTION: check if all required parameters were initialized based on their initialized flag

	PRE: none
	POST: returns 1 if all required parameters were initialized, 0 if they weren't
*/
int initializedChecker(ParameterManager* p)
{
	List *ptemp = headOfList(p->reqParamValues);
	char *pname = NULL;
	int flag = 0;
	
	while (ptemp != NULL)
	{
		pname = getCurrentElement(p->reqParamValues);/*get the parameter name, to search in the table for it's initialized flag*/
		flag = ((ParameterValue*)getTableElement(p->paramValues, pname))->initFlag;/*grab initialized flag from parameter*/

		if(flag == 0)
		{
			return 0;/*if the parameter had a initialized flag of 0, and it is in the list, it was not initialized and retun error*/
		}
		ptemp = nextInList(p->reqParamValues);/*get the next parameter in the list of required parameters*/		
	}
	return 1;
}

/* PM_manage
	DESCRIPTION: register a parameter for management

	PRE: pname does not duplicate the name
	POST: pname of type ptype is register with p as a parameter, if required is 0 it is
		considered to be optional, otherwise it is required;
		returns 1 on success, 0 otherwise (duplicate name, memory allocation failure)
*/
int PM_manage(ParameterManager *p, char *pname, param_t ptype, int required)
{
	char* allocatePname = (char *) malloc(sizeof(char) * (strlen(pname) + 10));
	ParameterValue* pValues = malloc(sizeof(ParameterValue));	
	/*check possible errors before proceeding*/
	if (allocatePname == NULL)
	{
		return 0;
	}
	if (pValues == NULL)
	{
		free(allocatePname);
		return 0;
	}
	if (getTableElement(p->paramValues, pname))/*if name already exists in table, do not add*/
	{
		return 0;
	}

	/*Initialize the internals on the PM element*/
	pValues->initFlag = 0;
	pValues->ptype = ptype;
	strcpy(allocatePname, pname);

	if (required != 0)/*if it was a required parameter, add it to the required list*/
	{
		endOfList(p->reqParamValues);
		addAfterPointer(p->reqParamValues, allocatePname);
	}

	addElementToTable(p->paramValues, allocatePname, pValues);/*add to the parameter table*/

	return 1;/*success*/
}

/* PM_hasValue
	DESCRIPTION: test if a parameter has been assigned a value

	PRE: pname is currently managed by p
	POST: Returns 1 if pname has been assigned a value, 0 otherwise (no value, unknown parameter)
*/
int PM_hasValue(ParameterManager *p, char *pname)
{
	ParameterValue* newValue = getTableElement(p->paramValues, pname);
	if (newValue != NULL && newValue->initFlag == 1)
	{
		return 1;
	}
	return 0;
}

/* PM_getValue
	DESCRIPTION: obtain the value assigned to pname

	PRE: pname is currently managed by p and has been assigned a value
	POST: Returns the value assigned to pname; result is undefined if pname has no value or is 			unknown
*/
union param_value PM_getValue(ParameterManager *p, char *pname)
{
	ParameterValue* newValue = getTableElement(p->paramValues, pname);
	if (newValue != NULL && newValue->initFlag)
	{
		return newValue->pvalue;
	}
	return;
}

/* parseIntType
	DESCRIPTION: check the vailidity of an integer type in the buffer

	PRE: none
	POST: Returns 0 if the buffer is not an integer, 1 if it is.
*/
int parseIntType(char* buffer, int* pvalue)
{
	int i = 0;

	for (i = 0; i < strlen(buffer); i++)
	{
		if((buffer[i] >= '0' && buffer[i] <= '9') || 
			(i == 0 && buffer[i] == '-'))
		{}
		else
		{
			return 0;/*if the number is less than 0 or greater then 9, or if the negative is not the first char, error*/
		}
	}
	*pvalue = atoi(buffer);
	return 1;
}

/* parseRealType
	DESCRIPTION: check the vailidity of a float type in the buffer

	PRE: none
	POST: Returns 0 if the buffer is not a float, 1 if it is.
*/
int parseRealType(char* buffer, float* pvalue)
{
	int i = 0;
	Boolean decimalOccured = false;

	for (i = 0; i < strlen(buffer); i++)
	{
		if((buffer[i] >= '0' && buffer[i] <= '9') ||
				 (i == 0 && buffer[i] == '-'))
		{}
		else if(buffer[i] == '.' && decimalOccured == false)
		{
			decimalOccured = true;
		}
		else if(buffer[i] == '.' && decimalOccured == true)
		{
			return 0;/*if a decimal occured twice, error*/
		}
		else
		{
			return 0;
		}	
	}
	*pvalue = atof(buffer);
	return 1;
}

/* parseBooleanType
	DESCRIPTION: check the vailidity of a boolean type in the buffer. TRUE and FALSE are valid.

	PRE: none
	POST: Returns 0 if the buffer is not a boolean, 1 if it is.
*/
int parseBooleanType(char* buffer, Boolean* pvalue)
{
	int i = 0;

	/*convert buffer to all lower case letters*/
	while(buffer[i])
	{
		buffer[i] = tolower(buffer[i]);
		i++;
	}

	if(strcmp(buffer,"true") == 0)
	{
		*pvalue = true;
	}
	else if(strcmp(buffer,"false") == 0)
	{
		*pvalue = false;
	}
	else
	{
		return 0;/*buffer was not true or false,error*/
	}
	return 1;
}

/* parseListType
	DESCRIPTION: check the vailidity of a list type in the buffer.

	PRE: none
	POST: Returns 0 if the buffer is not a list, 1 if it is.
*/
int parseListType(char* buffer, ParameterList** pvalue)
{
	int i = 0;
	char buildString[9999] = {0};
	char *tokens = NULL;

	List* newList = createNewList();
	if(newList == NULL)
	{
		return 0;
	}

	if(buffer[0] != '{' || buffer[strlen(buffer)-1] != '}')
	{
		return 0;/*improper bracket positions*/
	}

	for(i = 1; i < strlen(buffer)-1; i++)/*skip the first bracket, and last bracket*/
	{
		if(buffer[i] == '{' || buffer[i] == '}')
		{
			return 0;/*found extra brackets in the list, error*/
		}
	} 

	buffer[strlen(buffer)-1] = '\0';/*get rid of the last } bracket*/
	
	tokens = strtok(buffer, "{ ,}");
	while(tokens != NULL)
	{	
		endOfList(newList);
		addAfterPointer(newList,mallocNewString(tokens));	
		tokens = strtok(NULL, "{ ,}");
	}

	*pvalue = PL_create(newList);
	if(!*pvalue)
	{
		deleteList(newList);
		return 0;
	}
	return 1;
}
