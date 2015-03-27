/*here you put the declarations for the functions you need to create the morse code translator.
you also put any constants you need in the .h file.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#define MAXCHARLIMIT 900
#define DOORPOSERROR 100 
#define HEROPOSERROR 101 
#define OBJECTPOSERROR 102 
#define POTION 0
#define WEAPON 1
#define GOLD 2

/*contained in parse.c*/
struct roomInfo *readContentsOfTextFile(char * fileName, struct roomInfo *roomsForGame);
struct roomInfo parseRoomInfoFromLine(char *line);
void extractNumbers(char *tokenOfInfo, int *posX, int *posY);
void printRoomStruct(struct roomInfo theRoom);

/*contained in drawrooms.c*/
void initCurses(void);
struct roomInfo * checkRoomInfoForErrors(struct roomInfo *RoomsForGame);
void drawRooms(struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix);
void drawDoors(struct roomInfo room, int displacementX, int displacementY);
void drawObjects(struct roomInfo room, int displacementX, int displacementY);
void drawPlayer(struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix, int displacementY);
void printRoomStruct2(struct roomInfo theRoom);
void printInventory(struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix);

/*contained in playerMovement.c*/
struct roomInfo moveTheHero(struct roomInfo herosRoom, char keyPress, struct roomInfo roomOne, struct roomInfo roomTwo, struct roomInfo roomThree, struct roomInfo roomFour, struct roomInfo roomFive, struct roomInfo roomSix, int *roomNum);
int determineIfPlayerWalkedOnAnObject(struct roomInfo herosRoom, int *posOfObject);
int determineIfPlayerWalkedOnStairsOrMonster(int heroPosX, int heroPosY, struct roomInfo herosRoom);
struct roomInfo determineIfPlayerInDoor(struct roomInfo herosRoom, struct roomInfo roomUPorDOWN, struct roomInfo roomWEST, struct roomInfo roomEAST, int heroNewX, int heroNewY, int roomNum);


/*contained in main.c*/
void printDisclaimer(void);


/* Positions (coordinates) of everything is put into arrays, the even numbered elements being X, and odd being Y. 
 * Things with only 1 number coordinate like doors are not arrays, and just contain the position of the item as an integer.
 * There are also variable to keep count of how many of each item there is
*/

struct roomInfo
{
	int dimensions[2];
	int heroPosition[2];
	
	int *doorPositionNum;
	char *doorPositionLetter;
	
	int *stairPosition;
	int *potionPosition;
	int *monsterPosition;
	int *weaponPosition;
	int *goldPosition;
	
	/*these set of variables count the number of each object in the particular room*/
	int doorCount;
	int stairCount;
	int weaponCount;
	int potionCount;
	int monsterCount;
	int goldCount;
	
	int inventory[3]; /*[0] is amount of potions picked up, [1] is amount of weapons, [2] is amount of gold*/
	
};
	
	
	
	
	
	
