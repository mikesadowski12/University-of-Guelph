/*
#NAME: Mike Sadowski
#DATE: February 5th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A2
*/

#include <stdio.h>
#include <jni.h>
#include "cfiles/ParameterManager.h"
#include "PM_Converter.h"

/*
 * Class:     PM_Converter
 * Method:    PM_create_J
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_PM_1Converter_PM_1create_1J(JNIEnv *env, jobject thisObj, jlong params)
{
	// Get a reference to this object's class
	jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	// Get the Field ID of the instance variables "number"
	jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameters", "J");
	if (NULL == fidNumber) return;	

	(*env)->SetLongField(env, thisObj, fidNumber, (jlong) PM_create(50));	
}



/*
 * Class:     PM_Converter
 * Method:    PM_destroy_J
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1destroy_1J(JNIEnv *env, jobject thisObj, jlong params)
{
	ParameterManager *pm = (ParameterManager*) params;
	// Get a reference to this object's class
	//jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	// Get the Field ID of the instance variables "number"
	//jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameters", "J");
	//if (NULL == fidNumber) return 0;	
	
	//ParameterManager *pm = (ParameterManager*) ((*env)->GetIntField(env, thisObj, fidNumber));		
	return PM_destroy(pm);
}
/*
 * Class:     PM_Converter
 * Method:    PM_manage_J
 * Signature: (Ljava/lang/String;CIJ)I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1manage_1J(JNIEnv *env, jobject thisObj, jstring name,  jchar ptype, jint required, jlong params)
{
	// Get a reference to this object's class
	//jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	// Get the Field ID of the instance variables "number"
	//jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameters", "L");
	//if (NULL == fidNumber) return 0;	
	
	ParameterManager *pm = (ParameterManager*) params;	

	const char *pname = (*env)->GetStringUTFChars(env, name, NULL);
	param_t convertedPtype;
	jint manageFlag = 0;

	if((char)ptype == 'i'){convertedPtype = INT_TYPE;}
	if((char)ptype == 'f'){convertedPtype = REAL_TYPE;}
	if((char)ptype == 'b'){convertedPtype = BOOLEAN_TYPE;}
	if((char)ptype == 's'){convertedPtype = STRING_TYPE;}
	if((char)ptype == 'l'){convertedPtype = LIST_TYPE;}

	manageFlag = PM_manage(pm, (char*)pname, convertedPtype, (int)required);

	(*env)->ReleaseStringUTFChars(env, name, pname);
	
	return manageFlag;	
}
/*
 * Class:     PM_Converter
 * Method:    PM_parseFrom_J
 * Signature: (Ljava/lang/String;CJ)I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1parseFrom_1J(JNIEnv *env, jobject thisObj, jstring name, jchar comment, jlong params)
{
	// Get a reference to this object's class
	//jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	// Get the Field ID of the instance variables "number"
	//jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameters", "I");
	//if (NULL == fidNumber) return 0;	
	
	ParameterManager *pm = (ParameterManager*) params;		
	
	FILE *fp = NULL;	
	const char *fileName = (*env)->GetStringUTFChars(env, name, NULL);
	jint parseFlag = 0;	
		
	fp = fopen(fileName,"r");
	parseFlag = PM_parseFrom(pm,fp,comment);
	(*env)->ReleaseStringUTFChars(env, name, fileName);
	if(fp != NULL)
	{
		fclose(fp);
	}
	
	return parseFlag;	
}
/*
 * Class:     PM_Converter
 * Method:    PM_hasValue_J
 * Signature: (Ljava/lang/String;J)I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1hasValue_1J(JNIEnv *env, jobject thisObj, jstring name, jlong params)
{
	// Get a reference to this object's class
	//jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	// Get the Field ID of the instance variables "number"
	//jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameters", "I");
	//if (NULL == fidNumber) return 0;	
	
	ParameterManager *pm = (ParameterManager*) params;	
	const char *pname = (*env)->GetStringUTFChars(env, name, NULL);
	jint hasValueFlag = 0;

	hasValueFlag = PM_hasValue(pm,(char*)pname);
	(*env)->ReleaseStringUTFChars(env, name, pname);
	return hasValueFlag;	
}
/*
 * Class:     PM_Converter
 * Method:    PM_getValue_J
 * Signature: (Ljava/lang/String;J)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_PM_1Converter_PM_1getValue_1J(JNIEnv *env, jobject thisObj, jstring name, jlong params)
{
	// Get a reference to this object's class
	//jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	// Get the Field ID of the instance variables "number"
	//jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameters", "I");
	//if (NULL == fidNumber) return NULL;	
	
	ParameterManager *pm = (ParameterManager*) params;
	
	const char* pname = (*env)->GetStringUTFChars(env, name, NULL);
	ParameterValue *pv = searchList(pm->parameters,(char*) pname);	
	char pvalue[100] = {0};
	char *buffer = NULL;
	jobjectArray value = NULL;
	int i = 0;

	if(pv->ptype == INT_TYPE)
	{
		value = (jobjectArray) (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);
		sprintf(pvalue,"%d",pv->pvalue.int_val);
		(*env)->SetObjectArrayElement(env, value, 0, (*env)->NewStringUTF(env, pvalue));		
	}
	if(pv->ptype == REAL_TYPE)
	{
		value = (jobjectArray) (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);		
		sprintf(pvalue,"%f",pv->pvalue.real_val);
		(*env)->SetObjectArrayElement(env, value, 0, (*env)->NewStringUTF(env, pvalue));		
	}
	if(pv->ptype == BOOLEAN_TYPE)
	{
		value = (jobjectArray) (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);		
		if(pv->pvalue.bool_val)
		{
			strcpy(pvalue,"true");
		}
		else
		{
			strcpy(pvalue,"false");
		}
		(*env)->SetObjectArrayElement(env, value, 0, (*env)->NewStringUTF(env, pvalue));
	}
	if(pv->ptype == STRING_TYPE)
	{
		value = (jobjectArray) (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);		
		sprintf(pvalue,"%s",pv->pvalue.str_val);
		(*env)->SetObjectArrayElement(env, value, 0, (*env)->NewStringUTF(env, pvalue));		
	}
	if(pv->ptype == LIST_TYPE)
	{
		value = (jobjectArray) (*env)->NewObjectArray(env, pv->pvalue.list_val->paramList->count, (*env)->FindClass(env, "java/lang/String"), NULL);
		while((buffer = PL_next(pv->pvalue.list_val)) != NULL)
		{
			(*env)->SetObjectArrayElement(env, value, i, (*env)->NewStringUTF(env, buffer));
			i++;
		}		
				
	}
	
	(*env)->ReleaseStringUTFChars(env, name, pname);

	return value;	
}
