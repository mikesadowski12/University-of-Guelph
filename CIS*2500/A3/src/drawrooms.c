/*************************drawrooms.c****************************
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

/* these sets of functions are meant to handle everything that has to do with displaying each room */
/*NAME: initCurses (i did not write this function. Gotten from a ncurses tutorial)
 *DESCRIPTION: Initializes screen for ncurses
 *PARAMETERS: NONE
 *RETURN: NONE
*/
void initCurses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	
}

/*NAME: printInventory
 *DESCRIPTION: displays the count of items that were picked up
 *PARAMETERS: roomInfo struct for each room
 *RETURN: NONE
*/
void printInventory(struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix)
{
	int inventoryCount[3] = {0};
		
	clear();	
	refresh();
	inventoryCount[0] = roomOne.inventory[0]+roomTwo.inventory[0]+roomThree.inventory[0]+roomFour.inventory[0]+roomFive.inventory[0]+roomSix.inventory[0];
	inventoryCount[1] = roomOne.inventory[1]+roomTwo.inventory[1]+roomThree.inventory[1]+roomFour.inventory[1]+roomFive.inventory[1]+roomSix.inventory[1];
	inventoryCount[2] = roomOne.inventory[2]+roomTwo.inventory[2]+roomThree.inventory[2]+roomFour.inventory[2]+roomFive.inventory[2]+roomSix.inventory[2];
	
	printw("Your Inventory is: \n"); 
	printw(">POTIONS: %i\n", inventoryCount[0]); 
	printw(">WEAPONS: %i\n", inventoryCount[1]);
	printw(">GOLD: %i\n\n\n\n", inventoryCount[2]);
	printw(">>>Press any key to continue..");	
	refresh();	
	getchar();
	
}



/*NAME: drawRooms
 *DESCRIPTION: Draws the walls of each room inside of this function. Calls other functions to place the doors + objects
 *PARAMETERS: roomInfo struct for each room
 *RETURN: NONE
*/
void drawRooms(struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix)
{
	int displacementX = 0;
	int displacementY = 0;
	int i = 0;
	int tall = 0;
	int wide = 0;
	
	/*determine the room with the greatest row value in the first 3 rooms*/
	if (roomOne.dimensions[0] >= roomTwo.dimensions[0] && roomOne.dimensions[0] >= roomThree.dimensions[0])
	{
			displacementY = roomOne.dimensions[0];		
	}
	if (roomTwo.dimensions[0] >= roomOne.dimensions[0] && roomTwo.dimensions[0] >= roomThree.dimensions[0])
	{
			displacementY = roomTwo.dimensions[0];		
	}
	if (roomThree.dimensions[0] >= roomTwo.dimensions[0] && roomThree.dimensions[0] >= roomOne.dimensions[0])
	{
			displacementY = roomThree.dimensions[0];		
	}

	clear();
	
	/*Display room 1*/
	tall	= roomOne.dimensions[0];
	wide	= roomOne.dimensions[1];
	
	for (i=0; i < wide+1; i++)
	{
		  mvaddch(0, i, '-');
	}
	
	for (i=0; i < (tall-1); i++)
	{
		mvaddch(i+1, 0, '|');
		mvaddch(i+1, wide, '|');
	}
	
	for (i=0; i < wide+1; i++)
	{
		 mvaddch(tall, i, '-');
	}
	
	drawDoors(roomOne,0,0);
	drawObjects(roomOne,0,0);
	
	/*Display room 2, 2 spaces beside room 1*/
	tall	= roomTwo.dimensions[0];
	wide	= roomTwo.dimensions[1];
	displacementX = roomOne.dimensions[1]+2;
	for (i=0; i < wide+1; i++)
	{
		  mvaddch(0, i+(displacementX), '-');
	}
	
	for (i=0; i < (tall)-1; i++)
	{
		mvaddch(i+1, 0+(displacementX), '|');
		mvaddch(i+1, wide+(displacementX), '|');
	}
	
	for (i=0; i < wide+1; i++)
	{
		 mvaddch(tall, i+(displacementX), '-');
	}	
	
	drawDoors(roomTwo,displacementX,0);
	drawObjects(roomTwo,displacementX,0);
	
	/*Display room 3, 2 spaces beside room 2*/
	tall	= roomThree.dimensions[0];
	wide	= roomThree.dimensions[1];
	displacementX = (roomOne.dimensions[1]+roomTwo.dimensions[1])+4;
	
	for (i=0; i < wide+1; i++)
	{
		  mvaddch(0, i+(displacementX), '-');
	}
	
	for (i=0; i < (tall-1); i++)
	{
		mvaddch(i+1, 0+(displacementX), '|');
		mvaddch(i+1, wide+(displacementX), '|');
	}
	
	for (i=0; i < wide+1; i++)
	{
		 mvaddch(tall, i+(displacementX), '-');
	}	
	
	drawDoors(roomThree,displacementX,0);
	drawObjects(roomThree,displacementX,0);
	
	/*Display room 4, 2 spaces below room 1*/
	tall	= roomFour.dimensions[0];
	wide	= roomFour.dimensions[1];
	displacementX = 0;
	for (i=0; i < wide+1; i++)
	{
		  mvaddch(0+displacementY+2, i, '-');
	}
	
	for (i=0; i < (tall-1); i++)
	{
		mvaddch(i+1+displacementY+2, 0, '|');
		mvaddch(i+1+displacementY+2, wide, '|');
	}
	
	for (i=0; i < wide+1; i++)
	{
		 mvaddch(tall+displacementY+2, i, '-');
	}	

	drawDoors(roomFour,displacementX,displacementY);
	drawObjects(roomFour,displacementX,displacementY);

	/*Display room 5, 2 spaces below room 2, and 2 space beside room 4*/
	tall	= roomFive.dimensions[0];
	wide	= roomFive.dimensions[1];
	displacementX = roomFive.dimensions[1]+1;
	
	for (i=0; i < wide+1; i++)
	{
		  mvaddch(0+displacementY+2, i+displacementX, '-');
	}
	
	for (i=0; i < (tall-1); i++)
	{
		mvaddch(i+1+displacementY+2, 0+displacementX, '|');
		mvaddch(i+1+displacementY+2, wide+displacementX, '|');
	}
	
	for (i=0; i < wide+1; i++)
	{
		 mvaddch(tall+displacementY+2, i+displacementX, '-');
	}	
	
	drawDoors(roomFive,displacementX,displacementY);
	drawObjects(roomFive,displacementX,displacementY);
	
	/*Display room 6, 2 spaces below room 3, and 2 space beside room 5*/
	tall	= roomSix.dimensions[0];
	wide	= roomSix.dimensions[1];
	displacementX = (roomFour.dimensions[1]+roomFive.dimensions[1])+4;
	
	for (i=0; i < wide+1; i++)
	{
		  mvaddch(0+displacementY+2, i+displacementX, '-');
	}
	
	for (i=0; i < (tall-1); i++)
	{
		mvaddch(i+1+displacementY+2, 0+displacementX, '|');
		mvaddch(i+1+displacementY+2, wide+displacementX, '|');
	}
	
	for (i=0; i < wide+1; i++)
	{
		 mvaddch(tall+displacementY+2, i+displacementX, '-');
	}	

	drawDoors(roomSix,displacementX,displacementY);
	drawObjects(roomSix,displacementX,displacementY);		

	drawPlayer(roomOne, roomTwo, roomThree, roomFour, roomFive, roomSix, displacementY+2);
	
	refresh();
	
}


/*NAME: drawPlayer
 *DESCRIPTION: Places the hero in a room
 *PARAMETERS: roominfo struct, and the X and Y displacements of the room's position relative to 0,0
 *RETURN: NONE
*/
void drawPlayer(struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix, int displacementY)
{

	if(roomOne.heroPosition[0] != 0 && roomOne.heroPosition[1] != 0)
	{
		mvaddch(roomOne.heroPosition[0], roomOne.heroPosition[1], '@');		
	}
	
	if(roomTwo.heroPosition[0] != 0 && roomTwo.heroPosition[1] != 0)
	{
		mvaddch(roomTwo.heroPosition[0], roomTwo.heroPosition[1]+roomOne.dimensions[1]+2, '@');	
	}
	if(roomThree.heroPosition[0] != 0 && roomThree.heroPosition[1] != 0)
	{
		mvaddch(roomThree.heroPosition[0], roomThree.heroPosition[1]+roomOne.dimensions[1]+roomTwo.dimensions[1]+4, '@');		
	}

	if(roomFour.heroPosition[0] != 0 && roomFour.heroPosition[1] != 0)
	{
		mvaddch(roomFour.heroPosition[0]+displacementY, roomFour.heroPosition[1], '@');		
	}

	if(roomFive.heroPosition[0] != 0 && roomFive.heroPosition[1] != 0)
	{
		mvaddch(roomFive.heroPosition[0]+displacementY, roomFive.heroPosition[1]+roomFour.dimensions[1]+2, '@');	
	}
	if(roomSix.heroPosition[0] != 0 && roomSix.heroPosition[1] != 0)
	{
		mvaddch(roomSix.heroPosition[0]+displacementY, roomSix.heroPosition[1]+roomFour.dimensions[1]+roomFive.dimensions[1]+4, '@');			
	}
	
	
}



/*NAME: drawDoors
 *DESCRIPTION: Places the doors in a room
 *PARAMETERS: roominfo struct, and the X and Y displacements of the room's position relative to 0,0
 *RETURN: NONE
*/
void drawDoors(struct roomInfo room, int displacementX, int displacementY)
{
	
	int x = 0;
	
	/*account for the 2 extra spaces*/
	if(displacementY != 0)
	{
		displacementY = displacementY+2;
	}
	
	/*print each door*/
	for (x = 0; x <= room.doorCount; x++)
	{	
		if(room.doorPositionLetter[x] == 'n')
		{
			mvaddch(displacementY, displacementX+room.doorPositionNum[x], '+');
		}
		
		if(room.doorPositionLetter[x] == 's')
		{
			mvaddch(displacementY+room.dimensions[0], displacementX+room.doorPositionNum[x], '+');
		}	
		
		if(room.doorPositionLetter[x] == 'e')
		{
			mvaddch(room.doorPositionNum[x]+displacementY, room.dimensions[1]+displacementX, '+');
		}
		
		if(room.doorPositionLetter[x] == 'w')
		{
			mvaddch(room.doorPositionNum[x]+displacementY, displacementX, '+');
		}	
	}	
}


/*NAME: drawObjects
 *DESCRIPTION: Places the objects in a room
 *PARAMETERS: roominfo struct, and the X and Y displacements of the room's position relative to 0,0
 *RETURN: NONE
*/
void drawObjects(struct roomInfo room, int displacementX, int displacementY)
{
/*
 * Potion: !
 * Weapon: )
 * Gold: *
 * Stairs: %
 * Monster: M
*/
	int x = 0;
	
	/*account for the 2 extra spaces*/
	if(displacementY != 0)
	{
		displacementY = displacementY+2;
	}
	
	if(room.potionCount != 0)
	{
		for (x = 0; x < room.potionCount; x++)
		{				
			mvaddch(displacementY+room.potionPosition[x], displacementX+room.potionPosition[x+1], '!');
		}	
	}
	
	if(room.weaponCount != 0)
	{
		for (x = 0; x < room.weaponCount; x++)
		{				
			mvaddch(displacementY+room.weaponPosition[x], displacementX+room.weaponPosition[x+1], ')');
		}		
	}
	if(room.goldCount != 0)
	{
		for (x = 0; x < room.goldCount; x++)
		{				
			mvaddch(displacementY+room.goldPosition[x], displacementX+room.goldPosition[x+1], '*');
		}		
	}
	if(room.stairCount != 0)
	{
		for (x = 0; x < room.stairCount; x++)
		{				
			mvaddch(displacementY+room.stairPosition[x], displacementX+room.stairPosition[x+1], '%');
		}		
	}
	if(room.monsterCount != 0)
	{
		for (x = 0; x < room.monsterCount; x++)
		{				
			mvaddch(displacementY+room.monsterPosition[x], displacementX+room.monsterPosition[x+1], 'M');
		}		
	}

}





/*NAME: checkRoomInfoForErrors
 *DESCRIPTION: checks and fixes error within text file (like doors not in a wall, positions of items etc)
 * 				to fix it, the code places the item that had bad coords in the centre of the room or wall
 *PARAMETERS: array of roomInfo structs (all 6 of the rooms)
 *RETURN: the repaired struct if it found an error, otherwise just the passed in struct array
*/
struct roomInfo * checkRoomInfoForErrors(struct roomInfo *RoomsForGame)
{
	int x = 0;
	int y = 0;
			
	/*x iterates through the room struct pointer*/
	for (x = 0; x <= 5; x++)
	{
		/*y iterates through the door number*/
		for(y = 0; y <= (RoomsForGame[x].doorCount-1); y++)
		{
			/*check east and west door number to be less than rows number, if its not in the wall, place it in the middle of the wall*/			
			if (RoomsForGame[x].doorPositionLetter[y] == 'e' || RoomsForGame[x].doorPositionLetter[y] == 'w')
			{	
				if (RoomsForGame[x].doorPositionNum[y] >= RoomsForGame[x].dimensions[0])
				{
					RoomsForGame[x].doorPositionNum[y] = (RoomsForGame[x].dimensions[0]/2);
				}			
			}
			
			/*check north and south door number to be less than column number, if its not in the wall, place it in the middle of the wall*/	
			if (RoomsForGame[x].doorPositionLetter[y] == 'n' || RoomsForGame[x].doorPositionLetter[y] == 's')
			{	
				if (RoomsForGame[x].doorPositionNum[y] >= RoomsForGame[x].dimensions[1])
				{
					RoomsForGame[x].doorPositionNum[y] = (RoomsForGame[x].dimensions[1]/2);
				}
			}
			
		}	
		
		/*check if hero appears in a wall, if so place it in centre of room*/
		if (RoomsForGame[x].heroPosition[0] >= RoomsForGame[x].dimensions[0] || RoomsForGame[x].heroPosition[1] >= RoomsForGame[x].dimensions[1])
		{
			RoomsForGame[x].heroPosition[0] = (RoomsForGame[x].dimensions[0]/2);
			RoomsForGame[x].heroPosition[1] = (RoomsForGame[x].dimensions[1]/2);
		}
		
		/*check if any gold appears in a wall, if so place it in centre of room*/
		for(y = 0; y <= (RoomsForGame[x].goldCount-1); y++)
		{
			if (RoomsForGame[x].goldPosition[y] >= RoomsForGame[x].dimensions[0] || RoomsForGame[x].goldPosition[y+1] >= RoomsForGame[x].dimensions[1])
			{
				RoomsForGame[x].goldPosition[y] = (RoomsForGame[x].dimensions[0]/2);
				RoomsForGame[x].goldPosition[y+1] = (RoomsForGame[x].dimensions[1]/2);				
			}
		}
		
		/*check if any potions appears in a wall, if so place it in centre of room*/
		for(y = 0; y <= (RoomsForGame[x].potionCount-1); y++)
		{
			if (RoomsForGame[x].potionPosition[y] >= RoomsForGame[x].dimensions[0] || RoomsForGame[x].potionPosition[y+1] >= RoomsForGame[x].dimensions[1])
			{
				RoomsForGame[x].potionPosition[y] = (RoomsForGame[x].dimensions[0]/2);
				RoomsForGame[x].potionPosition[y+1] = (RoomsForGame[x].dimensions[1]/2);					
			}
		}
		
		/*check if any monsters appears in a wall, if so place it in centre of room*/
		for(y = 0; y <= (RoomsForGame[x].monsterCount-1); y++)
		{
			if (RoomsForGame[x].monsterPosition[y] >= RoomsForGame[x].dimensions[0] || RoomsForGame[x].monsterPosition[y+1] >= RoomsForGame[x].dimensions[1])
			{
				RoomsForGame[x].monsterPosition[y] = (RoomsForGame[x].dimensions[0]/2);
				RoomsForGame[x].monsterPosition[y+1] = (RoomsForGame[x].dimensions[1]/2);				
			}
		}
		
		/*check if any stairs appears in a wall, if so place it in centre of room*/
		for(y = 0; y <= (RoomsForGame[x].stairCount-1); y++)
		{
			if (RoomsForGame[x].stairPosition[y] >= RoomsForGame[x].dimensions[0] || RoomsForGame[x].stairPosition[y+1] >= RoomsForGame[x].dimensions[1])
			{
				RoomsForGame[x].stairPosition[y] = (RoomsForGame[x].dimensions[0]/2);
				RoomsForGame[x].stairPosition[y+1] = (RoomsForGame[x].dimensions[1]/2);					
			}
		}
		
		/*check if any weapon appears in a wall*/
		for(y = 0; y <= (RoomsForGame[x].weaponCount-1); y++)
		{
			if (RoomsForGame[x].weaponPosition[y] >= RoomsForGame[x].dimensions[0] || RoomsForGame[x].weaponPosition[y+1] >= RoomsForGame[x].dimensions[1])
			{
				RoomsForGame[x].weaponPosition[y] = (RoomsForGame[x].dimensions[0]/2);
				RoomsForGame[x].weaponPosition[y+1] = (RoomsForGame[x].dimensions[1]/2);				
			}
		}
	}
			
	/*return the fixed pointer to the adjusted structs*/
	return RoomsForGame;
}	
	
/*NAME: printRoomStruct2
 *DESCRIPTION: serves no purpose other than to print a room's information of the position of objects for testing
 *PARAMETERS: roomInfo struct, and the counts of all the objects in the room
 *RETURN: NONE
*/


void printRoomStruct2(struct roomInfo theRoom)
{
	int x = 0;
	
	printw(">>> ROOMINFO: \n");
	printw(">ROWS: %i\n", theRoom.dimensions[0]);
	printw(">COLS: %i\n", theRoom.dimensions[1]);
	printw(">HEROX: %i\n", theRoom.heroPosition[0]);
	printw(">HEROY: %i\n", theRoom.heroPosition[1]);
	
	for (x = 0; x <= (theRoom.doorCount-1); x++)
	{
		printw(">DOOR: letter-%c   num-%i\n", theRoom.doorPositionLetter[x], theRoom.doorPositionNum[x]);		
	}

	for (x = 0; x <= (theRoom.stairCount-1); x++)
	{
		printw(">STAIRS: x-%i   y-%i\n", theRoom.stairPosition[x], theRoom.stairPosition[x+1]);
	}

	for (x = 0; x <= (theRoom.potionCount-1); x++)
	{
		printw(">POTION: x-%i   y-%i\n", theRoom.potionPosition[x], theRoom.potionPosition[x+1]);
	}
	
	for (x = 0; x <= (theRoom.monsterCount-1); x++)
	{
		printw(">MONSTER: x-%i   y-%i\n", theRoom.monsterPosition[x], theRoom.monsterPosition[x+1]);
	}	
	
	for (x = 0; x <= (theRoom.weaponCount-1); x++)
	{
		printw(">WEAPON: x-%i   y-%i\n", theRoom.weaponPosition[x], theRoom.weaponPosition[x+1]);
	}

	for (x = 0; x <= (theRoom.goldCount-1); x++)
	{
		printw(" >GOLD: x-%i   y-%i\n", theRoom.goldPosition[x], theRoom.goldPosition[x+1]);
	}			
}	

