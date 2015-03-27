/*here you put the declarations for the functions you need to create the morse code translator.
you also put any constants you need in the .h file.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Student *createRecord(struct Student *newELement, char *firstName, char *lastName, int studentID, float GPA);
struct Student *addToFront(struct Student *oldHead, struct Student *newElement);
void printStudentLinkedList(struct Student *headOfList);
void deleteList(struct Student *head);

struct Student
{
	char firstName[100];
	char lastName[100];
	int studentID;
	float GPA;
	
	struct Student *next;

};

typedef struct Student StudentRec;

	
	
	
	
