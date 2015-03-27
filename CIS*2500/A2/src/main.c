/*************************main.c****************************
Student Name: Michael Sadowski                      Student Number:  0864810
Date: Feb 10th, 2014                       Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "curl_util.h"
#include "morsecode.h"

/* Get message to translate from the user.   Prepend the phrase message= to the front of it.  
	Use strcpy and strcat   suppose you wanted to translate 'hello world'.  The message string 
	would read "message=hello world".  You will need to allocate memory for the message before
	you can use it*/

/* Use the utility function to make a call to the website of your choice.  Catch the return
	value in a string (char *) */
	
int main(int argc, char* argv[]) 
{
	char* url = "http://mattfedder.com/cgi-bin/morse.pl"; /*you can use any URL you wish for this*/
	char* result;
	char *message;
	char *prevMsg;
	char userInput;
	char sendToWebsite[MAXCHARLIMIT+8] = {"message="}; /*set a string with the appropriate tags to be sent to website */

	userInput = 0;
	result = (char*) malloc (5000*sizeof(char));
	/*message = (char*) malloc (5000*sizeof(char));*/
	prevMsg = (char*) malloc (5000*sizeof(char));
		
	 while (userInput != '4')
	 {
		 system("clear");
		 userInput = printUI();
		 
		if( userInput == '1')
		{
			printf("\n\n>> Allowed Characters Are: any letter, any number, slashes(/), question mark(?) or a space");
			getchar();
			message = getMessageFromUser(1, 0);/*get an english message*/
			sendToWebsite[8] = '\0';
			if(message != NULL)
			{
				strcat(sendToWebsite, message);
				result = parseResponse(makeCurlCall(url, sendToWebsite));
			
				/* If result is null we didn't get any data */
				if (result == NULL) 
				{
					/*do something reasonable to let the user know that the translation failed */
					printf("\n>> ERROR: Cannot reach server\n");
					getchar();
				}
				else
				{
					strcpy(prevMsg, result);
					printf("\n>> Translated message is: %s\n\n", result);
					getchar();
					free(result);
					result = NULL;
				}
			}
			
			
		}
					
		if( userInput == '2')
		{
			printf("\n\n>> Allowed Characters Are: periods(.), hyphens(-), and spaces");			
			getchar();
			message = getMessageFromUser(0, 1);/*get a morse code message*/
			sendToWebsite[8] = '\0';
			
			if(message != NULL)
			{
				strcat(sendToWebsite, message);
				result = parseResponse(makeCurlCall(url, sendToWebsite));
				
				/* If result is null we didn't get any data */
				if (result == NULL) 
				{
					/*do something reasonable to let the user know that the translation failed */
					printf("\n>> ERROR: Cannot reach server\n");
					getchar();
				}
				else
				{
					strcpy(prevMsg, result);
					printf("\n>> Translated message is: %s\n\n", result);
					getchar();
					free(result);
					result = NULL;
				}
			}
			
		}
				
		if( userInput == '3')
		{
			getchar();
			printf("\nPrevious message was: %s", prevMsg);
			getchar();	
		}
			
		if( userInput == '4')
		{
			system("clear");
			printf(">> Goodbye!\n");
			break;						
		}
			
	}
/*this is probably the end of your outside loop*/


	/*don't forget to free the result memory before you call the utility again.  It mallocs memory
  every time you call it */
  
	if(message != NULL)
	{
		free(message);
	}

	if(prevMsg != NULL)
	{
		free(prevMsg);
	}

	if(result != NULL)
	{
		free(result);
	}

	return 0;
}


/*
 * This function print the UI for the user
 * and reads their response. Their response
 * is return as an INTEGER.
*/
char printUI(void)
{
	char userInput;
	userInput = 0;
	
	do
	{
		system("clear");
		printf("\n>>***WELCOME TO THE MORSE CODE TRANSLATOR***<<");
		printf("\n>>    1. ENGLISH TO MORSE TRANSLATION       <<");
		printf("\n>>    2. MORSE TO ENGLISH TRANSLATION       <<");
		printf("\n>>    3. YOUR PREVIOUS TRANSLATION          <<");
		printf("\n>>    4. EXIT                               <<");
		printf("\n>>------------------------------------------<<");
		printf("\n\n Please enter a corresponding menu number: ");
		userInput = getchar();
	}while (userInput != '1' && userInput != '2' && userInput != '3' && userInput != '4');		

	return userInput;
}


/*
 * This function find the message in the response
 * from the website, parses it out, and returns just the 
 * message back.
*/
char* parseResponse(char* result)
{
	char* message;
	char* translatedMessage;
	int x = 0;
	
	message = (char*) malloc (5000*sizeof(char));
	translatedMessage = (char*) malloc (500*sizeof(char));
	
	/*Start at the beginning of the response from the website, and go 270 characters over to the beginning of the translation message, 
	 * and copy this into a new variable
	 */
	strncpy(message, result+270, strlen(result));
		
	/*Loop through the response from the website starting from the beginning of the translated message, to the 
	 * end of it by find the first < in the string (it will signify the end of the translation and the start of more 
	 * html code.
	 */	
	for(x = 0; x < strlen(message); x++)
	{
		if(message[x] == '<')
		{
			strncpy(translatedMessage, message, x);/*every up to the position of the first < in the string to another variable, this is the message*/
			translatedMessage[x] = '\0';
			break;
		}
	}
	
	/*Free up memory*/
	free(message);
	
	return translatedMessage;/*Return the parsed out message*/
}


/*
 * This function, based on the flags it's been given when called,
 * will allow the user to enter an english message or a morse code message
 * to be translated.
*/
char* getMessageFromUser(int englishFlag, int morseFlag)
{
	char* message;
	int x;
	int y;
	int correctChars;
	
	/*These array hold the characters that are the only allowed chars for each type of translation*/
	char allowedMorseChars[3] = {' ', '-', '.',};
	char allowedEnglishChars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'x', 'Y', 'Z', '/', ':', '?','"', '@', '=', '(', ')', '[', ']', '1', '2','3','4','5','6','7','8','9','0'}; 
	
	message = (char*) malloc (MAXCHARLIMIT*sizeof(char));
	x = 0;
	y = 0;
	correctChars = 1;

	printf("\nPlease Enter Your Message: ");
	fgets(message, MAXCHARLIMIT, stdin);
	
	if(strlen(message) > MAXCHARLIMIT)
	{
		printf("Your message is longer than 200 characters");
		return NULL;
	}
	
	/*Check each individual char to see if it is in the allowed chracter's array*/
	if(englishFlag == 1)/*If user chose to enter english text*/
	{
		for (y = 0; y <= strlen(message); y++)
		{
			for (x = 0; x <= sizeof(allowedEnglishChars); x++)/*63 because thats how many total characters are allowed in english translation*/
			{
				if(message[y] == allowedEnglishChars[x])
				{
					correctChars++; /*count how many correct chars we get, if its less then the total amount of chars, one was incorrect*/
					break;
				}
			}
		}
	}
	
	/*Check each individual char to see if it is in the allowed chracter's array*/
	if(morseFlag == 1)/*If user chose to enter morse code*/
	{
		for (y = 0; y <= strlen(message); y++)
		{
			for (x = 0; x <= sizeof(allowedMorseChars); x++)
			{
				if(message[y] == allowedMorseChars[x])
				{
					correctChars++; /*count how many correct chars we get, if its less then the total amount of chars, one was incorrect*/
					break;
				}
			}
		}
	}
	


	/*Check the amount of correct chars, if it equals the amount of total chars, all chars passed the test*/
	if (correctChars == strlen(message))/*minus the one from the count because of line feed */
	{
		return message;
	}
	else
	{
		free(message);
		printf("\n\n\n>>>>>Your message did not contain appropriate characters\n\n");
		getchar();
		return NULL;
	}
}


