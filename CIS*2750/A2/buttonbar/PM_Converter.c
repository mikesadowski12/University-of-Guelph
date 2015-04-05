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

/*SOURCES:
 * 1. http://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html#zz-5.
*/ 

/*Global ParameterManager*/
ParameterManager *params;

ParameterManager *getParameterManagerFromJavaClass(JNIEnv* env, jobject thisObj)
{
	/*Get a reference to this object's class*/
	jclass thisClass = (*env)->GetObjectClass(env, thisObj);
   
	/*Get the Field ID of the instance variables "parameterManager"*/
	jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameterManager", "I");
	if (fidNumber == NULL)
	{
		return NULL;  
	}
	
	/*return a pointer to the instance variable in the java class, that is the pointer to the ParameterManager Object*/ 
	return (ParameterManager*) ((*env)->GetIntField(env, thisObj, fidNumber));
}

void saveParameterManagerToJavaClass(JNIEnv* env, jobject thisObj, ParameterManager* p)
{
	/*Get a reference to this object's class*/
	jclass thisClass = (*env)->GetObjectClass(env, thisObj);
	
	/*Get the Field ID of the instance variables "parameterManager"*/
	jfieldID fidNumber = (*env)->GetFieldID(env, thisClass, "parameterManager", "I");
	if (fidNumber == NULL)
	{
		return;  
	}
	
	/*set the pointer to the instance variable in the java class, that is the pointer to the new ParameterManager Object*/
	(*env)->SetIntField(env, thisObj, fidNumber, (jint) p);
}

/*
 * Class:     PM_Converter
 * Method:    PM_create_J
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_PM_1Converter_PM_1create_1J(JNIEnv *env, jobject thisObj)
{
	saveParameterManagerToJavaClass(env, thisObj, PM_create(25));
}

/*
 * Class:     PM_Converter
 * Method:    PM_destroy_J
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1destroy_1J(JNIEnv *env, jobject thisObj)
{
	return PM_destroy(getParameterManagerFromJavaClass(env, thisObj));
}

/*
 * Class:     PM_Converter
 * Method:    PM_manage_J
 * Signature: (Ljava/lang/String;CI)I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1manage_1J(JNIEnv *env, jobject thisObj, jstring name, jchar ptype, jint required)
{
	const char *pname = (*env)->GetStringUTFChars(env, name, NULL);
	param_t convertedPtype;
	jint manageFlag = 0;

	if((char)ptype == 'i'){convertedPtype = INT_TYPE;}
	if((char)ptype == 'f'){convertedPtype = REAL_TYPE;}
	if((char)ptype == 'b'){convertedPtype = BOOLEAN_TYPE;}
	if((char)ptype == 's'){convertedPtype = STRING_TYPE;}
	if((char)ptype == 'l'){convertedPtype = LIST_TYPE;}

	manageFlag = PM_manage(getParameterManagerFromJavaClass(env, thisObj), (char*)pname, convertedPtype, (int)required);
	(*env)->ReleaseStringUTFChars(env, name, pname);
	
	return manageFlag;
}

/*
 * Class:     PM_Converter
 * Method:    PM_parseFrom_J
 * Signature: (Ljava/lang/String;C)I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1parseFrom_1J(JNIEnv *env, jobject thisObj, jstring name, jchar comment)
{
	FILE *fp = NULL;	
	const char *fileName = (*env)->GetStringUTFChars(env, name, NULL);
	jint parseFlag = 0;	
	
	fp = fopen(fileName,"r");
	(*env)->ReleaseStringUTFChars(env, name, fileName);
	fclose(fp);
	parseFlag = PM_parseFrom(getParameterManagerFromJavaClass(env, thisObj),fp,comment);
	return parseFlag;
}

/*
 * Class:     PM_Converter
 * Method:    PM_hasValue_J
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_PM_1Converter_PM_1hasValue_1J(JNIEnv *env, jobject thisObj, jstring name)
{
	const char *pname = (*env)->GetStringUTFChars(env, name, NULL);
	jint hasValueFlag = 0;
	
	hasValueFlag = PM_hasValue(getParameterManagerFromJavaClass(env, thisObj),(char*)pname);
	(*env)->ReleaseStringUTFChars(env, name, pname);
	return hasValueFlag;	
}

/*
 * Class:     PM_Converter
 * Method:    PM_getValue_J
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_PM_1Converter_PM_1getValue_1J(JNIEnv *env, jobject thisObj, jstring name)
{

}




