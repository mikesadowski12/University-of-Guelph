/*************************playerMovement.c****************************
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


/*These functions deal with player position and everything to do with moving*/

/*NAME: moveTheHero 
 *DESCRIPTION: move the hero according to what button the user pressed
 *PARAMETERS: roomInfo struct that the hero is inside, what key was pressed
 *RETURN: the roomInfo struct with the heros new position to be re-drawn
*/
struct roomInfo moveTheHero(struct roomInfo herosRoom, char keyPress, struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix, int *roomNum)
{
	int objNum = 0;
	
	switch (keyPress)
	{
		case 'w':			
			if ((herosRoom.heroPosition[0]-1) > 0)
			{
				if(determineIfPlayerWalkedOnStairsOrMonster(herosRoom.heroPosition[0]-1, herosRoom.heroPosition[1], herosRoom) == 0)
				{
					herosRoom.heroPosition[0] = herosRoom.heroPosition[0] - 1; 
				}				
			}
			break;
			
		case 'a':
			if ((herosRoom.heroPosition[1]-1) > 0)
			{
				if(determineIfPlayerWalkedOnStairsOrMonster(herosRoom.heroPosition[0], herosRoom.heroPosition[1]-1, herosRoom) == 0)
				{								
					herosRoom.heroPosition[1] = herosRoom.heroPosition[1] - 1;
				}
			}
			break;		
		case 's':
			if ((herosRoom.heroPosition[0]+1) < herosRoom.dimensions[0])
			{
				if(determineIfPlayerWalkedOnStairsOrMonster(herosRoom.heroPosition[0]+1, herosRoom.heroPosition[1], herosRoom) == 0)
				{								
					herosRoom.heroPosition[0] = herosRoom.heroPosition[0] + 1;
				}
			}	
			break;	
				
		case 'd':
			if ((herosRoom.heroPosition[1]+1) < herosRoom.dimensions[1])
			{		
				if(determineIfPlayerWalkedOnStairsOrMonster(herosRoom.heroPosition[0], herosRoom.heroPosition[1]+1, herosRoom) == 0)
				{								
					herosRoom.heroPosition[1] = herosRoom.heroPosition[1] + 1;
				}
			}
			break;
			
		default:
			break;
		
	}


	if(determineIfPlayerWalkedOnAnObject(herosRoom, &objNum) == POTION )
	{
		herosRoom.inventory[0]++;
		herosRoom.potionPosition[objNum] = 20000;;		
	}
	
	if(determineIfPlayerWalkedOnAnObject(herosRoom, &objNum) == WEAPON )
	{		
		herosRoom.inventory[1]++;
		herosRoom.weaponPosition[objNum] = 20000;;	
	}
	
	if(determineIfPlayerWalkedOnAnObject(herosRoom, &objNum) == GOLD )
	{
		herosRoom.inventory[2]++;
		herosRoom.goldPosition[objNum] = 20000;	
	}
	return herosRoom;
	
}





/*NAME: determineIfPlayerWalkedOnAnObject 
 *DESCRIPTION: see if the player walked over an item 
 *PARAMETERS: the heros x and y coords
 *RETURN: 0 if potion was walked over, 1 if weapon, 2 if gold, 4 if nothing was walked on
*/
int determineIfPlayerWalkedOnAnObject(struct roomInfo herosRoom, int *posOfObject)
{
	int x = 0;
	
	for (x = 0; x <= herosRoom.potionCount; x++)
	{
		/*check heros coords versus the item's*/
		if(herosRoom.heroPosition[0] == herosRoom.potionPosition[x] && herosRoom.heroPosition[1] == herosRoom.potionPosition[x+1] )
		{
			*posOfObject = x;
			return POTION;
		}
	}
	
	for (x = 0; x <= herosRoom.weaponCount; x++)
	{
		/*check heros coords versus the item's*/
		if(herosRoom.heroPosition[0] == herosRoom.weaponPosition[x] &&  herosRoom.heroPosition[1] == herosRoom.weaponPosition[x+1] )
		{
			*posOfObject = x;
			return WEAPON;
		}	
	}
	
	for (x = 0; x <= herosRoom.goldCount; x++)
	{
		/*check heros coords versus the item's*/
		if(herosRoom.heroPosition[0] == herosRoom.goldPosition[x] &&  herosRoom.heroPosition[1] == herosRoom.goldPosition[x+1] )
		{
			*posOfObject = x;
			return GOLD;
		}	
	}
	
	return 4;
	
}

/*NAME: determineIfPlayerWalkedOnStairsOrMonster 
 *DESCRIPTION: see if the player walked over stairs or a monster
 *PARAMETERS: heros x and y coords
 *RETURN: 0 if nothing was walked over, 1 if yes
*/
int determineIfPlayerWalkedOnStairsOrMonster(int heroPosX, int heroPosY, struct roomInfo herosRoom)
{
	int x = 0;

	for (x = 0; x <= herosRoom.monsterCount; x++)
	{
		/*check heros coords versus the item's*/
		if(heroPosX == herosRoom.monsterPosition[x] &&  heroPosY == herosRoom.monsterPosition[x+1] )
		{
			return 1;
		}	
	}
		
	return 0;
}
