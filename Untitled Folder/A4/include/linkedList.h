#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#ifndef BOOL_DEF
#define BOOL_DEF
/*Judi's home made bool type.*/
typedef int bool;
enum {false, true};
#endif


/***************************************
struct and operations that work directly on the struct
The struct operations and definition could be in their 
own .c and .h files (and sometimes should be).
****************************************/


struct Music{
  char * title;
  char * artist;
  double  sizeInKB;
  int lengthInSeconds;
  char type;
  struct Music * next;
};

/*do not remove this typedef.  We need it for testing your code */

typedef struct Music MusicRec;

/*NAME: parseMusicFileAndInsertToLL
 *DESCRIPTION: Opens the file specified on command line, parses the lines of info into a linked list
 *PARAMETERS: filename, head of linked list
 *RETURN: head ofthe linked list
*/
MusicRec *parseMusicFileAndInsertToLL(char * fileName, MusicRec *headOfList);

/*NAME: parseLineForInfo
 *DESCRIPTION: parse the line from the text file, store all info into a MusicRec struct
 *PARAMETERS: the line as a string
 *RETURN: the new node of information
*/
MusicRec *parseLineForInfo(char *line);


/*NAME: getAverageFileSizeOfList
 *DESCRIPTION: determine the average filze size of the entire list
 *PARAMETERS: the head of the list pointer
 *RETURN: the average of the file sizes in the list
*/
double getAverageFileSizeOfList(MusicRec *theList);


/*NAME: convertPlayListTime
 *DESCRIPTION: convert the total seconds into hours, minutes and seconds
 *PARAMETERS: the head of the list pointer
 *RETURN: a string with the converted times as HH:MM:SS 
*/
char *convertPlayListTime(MusicRec *theList);

/******************************
 Functions operating on  structs 
 *******************************/

/*This function takes in two strings for title and artist, the fileSize 
of the tune and the length in seconds. 
The function allocates memory for the struct, initializes the variables to the supplied
values,  initializes the next pointer to null and returns a pointer to the allocated memory. 
Returns NULL on failure.The value for title and artist are copied into newly allocated memory.
The passed-in memory for title and artist must be released elsewhere in the program.
Memory for the struct must be freed elsewhere in the program. 
*/
MusicRec * createRecord(char * title, char * artist, double fileSize, int length, char theType);


/*This function takes a pointer to a music record and returns a pointer to a string 
that contains the information from the struct formatted
in the  following manner:  "Title (Artist):lengthInSeconds[fileSize]  The string should not 
contain a newline. File size should be reported to two decimal places.
The string memory is allocated in this function and must be freed elsewhere in 
the program.
*/

char * printRecord(MusicRec * toPrint);


/*Takes a pointer to a music record and frees the memory for the internal variables.
the music record pointer must be freed separately */
void destroyRecord(MusicRec * theRecord);

/********************************
List operations
*********************************/


/*addToFront(MusicRec * theList, MusicRec * toBeAdded)
Takes a pointer to the head of the list and an initialized music 
record.  Adds the music record to the front of the linked list and
returns a pointer to the head of the list.  */
MusicRec * addToFront(MusicRec * theList, MusicRec * toBeAdded);

/*addToBack(MusicRec *  theList, MusicRec * toBeAdded)
Takes a pointer to the head of the list and an initialized music 
record.  Adds the music record to the back of the linked list and
returns a pointer to the head of the list.  */
MusicRec * addToBack(MusicRec *  theList, MusicRec * toBeAdded);

/*removeFromFront(MusicRec * theList)
Takes a pointer to the head of the list.  Removes the front
item from the head of the list.  Does not free the memory for 
the item removed.  Returns a pointer to the head of the list.
Returns NULL if the list is empty*/
MusicRec * removeFromFront(MusicRec * theList);

/*removeFromBack(MusicRec *  theList)
Takes a pointer to the head of the list.  Removes the last
item from the head of the list.  Does not free the memory for 
the item removed.  Returns a pointer to the removed item.
Returns NULL if the list is empty.
*/
MusicRec * removeFromBack(MusicRec *  theList);

/*getLastItem(MusicRec * theList)
Takes a pointer to the head of the list.  Returns 
a pointer to the item at the end of the list.
Returns NULL if the list is empty.
*/
MusicRec * getLastItem(MusicRec * theList);

/*isEmpty(MusicRec * theList)
Takes a pointer to the head of the list.  Returns 
TRUE if the list is empty and FALSE 
if the list has any elements.
*/
bool isEmpty(MusicRec * theList);

/*printList(MusicRec *  theList)
Takes a pointer to the head of the list.  Prints to stdout
 all of the elements of the list (formatted 
as specified for the printRecord function) separated by newlines.

*/
void printList(MusicRec *  theList);


/*destroyList(MusicRec * theList)
Takes a pointer to the list and frees the memory for each struct in the list.

*/
void  destroyList(MusicRec * theList);

