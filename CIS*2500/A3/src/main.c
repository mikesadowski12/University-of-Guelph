/*************************main.c****************************
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

	
int main(int argc, char* argv[]) 
{
	
	struct roomInfo *RoomsForGame = 0;
	int x = 0;
	char keyPress = 0;
	int roomNum = 0;
	struct roomInfo roomOne;
	struct roomInfo roomTwo;
	struct roomInfo roomThree;
	struct roomInfo roomFour;
	struct roomInfo roomFive;
	struct roomInfo roomSix;
	struct roomInfo herosRoom;
	
	/*read the text file contents and save all the info for each room in a struct pointer*/	
	RoomsForGame = readContentsOfTextFile(argv[1], RoomsForGame);

	/*check the positions of everything in the room to make sure it's in side, adjust if need be*/
	RoomsForGame = checkRoomInfoForErrors(RoomsForGame);
	
	printDisclaimer();
	
	
	/*initialize the inventories to 0*/
	for (x = 0; x <= 5; x++)
	{
		RoomsForGame[x].inventory[0] = 0;
		RoomsForGame[x].inventory[1] = 0;
		RoomsForGame[x].inventory[2] = 0;
	}
	
	
	
	/*Save each room to their own var since ncurses doesn't like pointers.... */
	roomOne = RoomsForGame[0];
	roomTwo = RoomsForGame[1];
	roomThree = RoomsForGame[2];
	roomFour = RoomsForGame[3];
	roomFive = RoomsForGame[4];
	roomSix = RoomsForGame[5];
	
	do
	{
		
		/*Print the rooms and play*/
		initCurses();
		
		drawRooms(roomOne, roomTwo, roomThree, roomFour, roomFive, roomSix);		
		keyPress = getchar();
		if(keyPress == 'i')
		{
			printInventory(roomOne, roomTwo, roomThree, roomFour, roomFive, roomSix);
		}
		
		/*Dtermine which room the hero is in*/
		if(roomOne.heroPosition[0] != 0 && roomOne.heroPosition[1] != 0)
		{
			herosRoom = roomOne;
			roomNum = 1;
			
		}
		if(roomTwo.heroPosition[0] != 0 && roomTwo.heroPosition[1] != 0)
		{
			herosRoom = roomTwo;
			roomNum = 2;
			
		}
		if(roomThree.heroPosition[0] != 0 && roomThree.heroPosition[1] != 0)
		{
			herosRoom = roomThree;
			roomNum = 3;
			
		}
		if(roomFour.heroPosition[0] != 0 && roomFour.heroPosition[1] != 0)
		{
			herosRoom = roomFour;
			roomNum = 4;
			
		}
		if(roomFive.heroPosition[0] != 0 && roomFive.heroPosition[1] != 0)
		{
			herosRoom = roomFive;
			roomNum = 5;
			
		}
		if(roomSix.heroPosition[0] != 0 && roomSix.heroPosition[1] != 0)
		{
			herosRoom = roomSix;
			roomNum = 6;			
		}
		/*if he entered a door, the new room info will be in herosROom, and the room number will be update to signal which room he is in*/
		herosRoom = moveTheHero(herosRoom, keyPress, roomOne, roomTwo, roomThree, roomFour, roomFive, roomSix, &roomNum);
		
		/*update the appropriate room's information*/
		if(roomNum == 1)
		{
			roomOne = herosRoom;
		}
		if(roomNum == 2)
		{
			roomTwo = herosRoom;
		}
		if(roomNum == 3)
		{
			roomThree = herosRoom;
		}		
		if(roomNum == 4)
		{
			roomFour = herosRoom;
		}
		if(roomNum == 5)
		{
			roomFive = herosRoom;
		}
		if(roomNum == 6)
		{
			roomSix = herosRoom;
		}		
			
							
	}while(keyPress != 'q');	
	
	printInventory(roomOne, roomTwo, roomThree, roomFour, roomFive, roomSix);
	
	
	endwin();
	return 0;
}

/*NAME: printDisclaimer 
 *DESCRIPTION: prints how to play the game
 *PARAMETERS: none
 *RETURN: none
*/
void printDisclaimer(void)
{
	system("clear");

	printf("**********************************************\n");
	printf("*Known Limitations/Things not working:       *\n");
	printf("*   1. Doors do not work.                    *\n");
	printf("*   2. Stairs do not work.                   *\n");
	printf("**********************************************\n");
	printf("**********************************************\n");
	printf("*Notes to consider:                          *\n");
	printf("* No matter what room hero is placed in      *\n");
	printf("* originally he can still walk around,       *\n");
	printf("* limited to the room dimensions, pick       *\n");
	printf("* up the items and have them in the inventory*\n");
	printf("* as well as can't walk over monsters.       *\n");
	printf("**********************************************\n");
	getchar();
	printf("Rogue Game\n");
	printf("Controls: w-UP  a-LEFT  s-DOWN  d-RIGHT  i-INVENTORY  q-QUIT\n");
	
	printf("**Please make sure your window is resized before continuing...**");
	getchar();	
}
