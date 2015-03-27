/*************************parse.c****************************
Student Name: Michael Sadowski                      Student Number:  0864810
Date: March 8th, 2014                       Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include "headers.h"

/* These group of functions are to handle getting the information from the text file, and sending back an entire array of every
 * room's information and the positions of all the objects in the room */




/*NAME: readContentsOfTextFile
 *DESCRIPTION: opens a file specified from paramter, reads each line into a buffer, and returns the buffer
 *PARAMETERS: file name to be opened
 *RETURN: NONE 
*/
struct roomInfo *readContentsOfTextFile(char * fileName, struct roomInfo *roomsForGame)
{
	FILE * infile;
	char buffer[6][MAXCHARLIMIT];
	int x = 0;
	struct roomInfo rooms[6];
		
	infile = fopen(fileName,"r");
	if (infile == NULL) 
	{
		printf ("Error opening file!\n"); exit(0);
	}

	/* This while loop will read the text file line by line, putting each room information in a different element of buffer */
	while(fgets(buffer[x], MAXCHARLIMIT, infile))
    {		
		x++;
    }
	
	/* Remove all the \n's at the end of each line.. the != 5 is there so that the last character on the last line does not get deleted */
	for (x = 0; x <= 5; x++)
	{
		if (buffer[x][strlen(buffer[x])] <= 33 && x != 5)
		{
			buffer[x][strlen(buffer[x])-1] = '\0';
		}
	}
	
	for (x = 0; x <= 5; x++)
	{
		rooms[x] = parseRoomInfoFromLine(buffer[x]);
	}
		
    fclose(infile);
    
    roomsForGame = rooms;
    
    return roomsForGame;
}



/*NAME: parseRoomInfoFromLine
 *DESCRIPTION: takes a string, seperates the 'tokens' by spaces, sorts all the room information like door positions etc into arrays, then all of the positions into a struct
 *PARAMETERS: line to have the room information extracted from 
 *RETURN: struct with all the room's information 
*/
struct roomInfo parseRoomInfoFromLine(char *line)
{
	struct roomInfo room;
	char *cutString;
	char tokes[500][100];
	int tokeCount = 0;
	int x = 0;
	int posX = 0;
	int posY = 0;
	
	/*allocate memory for the dynamic arrays for each of the objects that can be multiples*/
	room.doorPositionNum = (int *) malloc (5000*sizeof(int));
	room.doorPositionLetter = (char *) malloc (5000*sizeof(char));		
	room.stairPosition = (int *) malloc (5000*sizeof(int));
	room.potionPosition = (int *) malloc (5000*sizeof(int));
	room.monsterPosition = (int *) malloc (5000*sizeof(int));
	room.weaponPosition = (int *) malloc (5000*sizeof(int));	
	room.goldPosition = (int *) malloc (5000*sizeof(int));
	
	room.doorCount = 0;
	room.stairCount = 0;
	room.weaponCount = 0;
	room.potionCount = 0;
	room.monsterCount = 0;
	room.goldCount = 0;
	room.heroPosition[0] = 0;
	room.heroPosition[1] = 0;
	
/* CUt the string into tokens based on the space, and put the tokens into the tokes array. tokeCount var keeps count of how many tokens there are*/
	cutString = strtok (line, " ");
	while (cutString != NULL)
	{			
		/*extractNumbers(cutString);*/
		strcpy(tokes[tokeCount], cutString);
		tokeCount++;
		cutString = strtok (NULL, " ");	
	}

/* send the array of tokens from the line to get the information extracted from them */
	for (x = 0; x <= (tokeCount-1); x++)
	{
		/*printf("TOKENINFO: %s --- ", tokes[x]);*/
		extractNumbers(tokes[x], &posX, &posY);		
		/*printf("POS X: %i || POS Y: %i\n", posX, posY);*/
		
		if (isdigit(tokes[x][0]) != 0)
		{
			room.dimensions[0] = posX;
			room.dimensions[1] = posY;
		}
				
		if (tokes[x][0] == 'h') 
		{
			room.heroPosition[0] = posX;
			room.heroPosition[1] = posY;
		}
		
		if (tokes[x][0] == 'd')
		{
			room.doorPositionNum[room.doorCount] = posX;
			room.doorPositionLetter[room.doorCount] = tokes[x][1];
			room.doorCount++;
		}
		
		if (tokes[x][0] == 's')
		{
			room.stairPosition[room.stairCount] = posX;
			room.stairPosition[room.stairCount+1] = posY;
			room.stairCount++;
		}
		
		if (tokes[x][0] == 'p')
		{
			room.potionPosition[room.potionCount] = posX;
			room.potionPosition[room.potionCount+1] = posY;
			room.potionCount++;			
		}	
		
		if (tokes[x][0] == 'm')
		{
			room.monsterPosition[room.monsterCount] = posX;
			room.monsterPosition[room.monsterCount+1] = posY;
			room.monsterCount++;			
		}
		
		if (tokes[x][0] == 'w')
		{
			room.weaponPosition[room.weaponCount] = posX;
			room.weaponPosition[room.weaponCount+1] = posY;
			room.weaponCount++;			
		}	
		
		if (tokes[x][0] == 'g')
		{
			room.goldPosition[room.goldCount] = posX;
			room.goldPosition[room.goldCount+1] = posY;
			room.goldCount++;			
		}				
	}
	

		
	return room;
}


/*10X16 de4 ds8 g8,7 m3,4 h6,5 p2,2*/
/*NAME: extractNumbers
 *DESCRIPTION: takes a string, seperates coordinates of objects from it (gold, weapons, stairs, hero, etc) based on their format
 *PARAMETERS: line to have the object coords extracted from, pointers to ints for the positions of the object (x and y coords)
 *RETURN: NONE, uses pointers to do the returns
*/
void extractNumbers(char *tokenOfInfo, int *posX, int *posY)
{
	char buffer[10];
	char *destination = 0;

	/*This will retrieve the information of the coordinates for gold monsters hero potion and weapons and stairs*/
	if (tokenOfInfo[0] == 'g' || tokenOfInfo[0] == 'm' ||tokenOfInfo[0] == 'h' || tokenOfInfo[0] == 'p' || tokenOfInfo[0] == 'w' || tokenOfInfo[0] == 's')
	{ 
		
		destination = strtok (tokenOfInfo+1, ",");
		*posX = atoi (destination);
		
		while (destination != NULL)
		{
			destination = strtok (NULL, ",");
			*posY = atoi (destination);
			break;					
		}
				
	}
	/*This will retrieve the information of the coordinates forthe room size*/
	if (isdigit(tokenOfInfo[0]) != 0)
	{
		destination = strtok (tokenOfInfo, "X");
		*posX = atoi (destination);
		while (destination != NULL)
		{
			destination = strtok (NULL, "X");
			*posY = atoi (destination);
			break;
		}
		
	}
	/*This will retrieve the information of the coordinates for the doors*/
	if (tokenOfInfo[0] == 'd')
	{
		strcpy(buffer, tokenOfInfo+2); /*copies from 2nd element into destination var since thats where the doors coords are*/
		*posX = atoi (buffer);		
	}
	
}

/*NAME: printRoomStruct
 *DESCRIPTION: serves no purpose other than to print a room's information of the position of objects for testing
 *PARAMETERS: roomInfo struct, and the counts of all the objects in the room
 *RETURN: NONE
*/
void printRoomStruct(struct roomInfo theRoom)
{
	int x = 0;
	
	printf(">>> ROOMINFO: \n");
	printf(">ROWS: %i\n", theRoom.dimensions[0]);
	printf(">COLS: %i\n", theRoom.dimensions[1]);
	printf("-------------------\n");
	
	printf(">HEROX: %i\n", theRoom.heroPosition[0]);
	printf(">HEROY: %i\n", theRoom.heroPosition[1]);
	
	printf("-------------------\n");
	for (x = 0; x <= (theRoom.doorCount-1); x++)
	{
		printf(">DOOR: letter-%c   num-%i\n", theRoom.doorPositionLetter[x], theRoom.doorPositionNum[x]);		
	}
	
	printf("-------------------\n");
	for (x = 0; x <= (theRoom.stairCount-1); x++)
	{
		printf(">STAIRS: x-%i   y-%i\n", theRoom.stairPosition[x], theRoom.stairPosition[x+1]);
	}
	
	printf("-------------------\n");
	for (x = 0; x <= (theRoom.potionCount-1); x++)
	{
		printf(">POTION: x-%i   y-%i\n", theRoom.potionPosition[x], theRoom.potionPosition[x+1]);
	}
	
	printf("-------------------\n");
	for (x = 0; x <= (theRoom.monsterCount-1); x++)
	{
		printf(">MONSTER: x-%i   y-%i\n", theRoom.monsterPosition[x], theRoom.monsterPosition[x+1]);
	}	
	
	printf("-------------------\n");
	for (x = 0; x <= (theRoom.weaponCount-1); x++)
	{
		printf(">WEAPON: x-%i   y-%i\n", theRoom.weaponPosition[x], theRoom.weaponPosition[x+1]);
	}
	
	printf("-------------------\n");
	for (x = 0; x <= (theRoom.goldCount-1); x++)
	{
		printf(">GOLD: x-%i   y-%i\n", theRoom.goldPosition[x], theRoom.goldPosition[x+1]);
	}			
}
