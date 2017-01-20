/*
#NAME: Mike Sadowski
#DATE: January 19th, 2017
#STUDENT ID: 0864810
#ASSIGNEMNT: 1
*/

/* Derived from scene.c in the The OpenGL Programming Guide */
/* Keyboard and mouse rotation taken from Swiftless Tutorials #23 Part 2 */
/* http://www.swiftless.com/tutorials/opengl/camera2.html */

/* Frames per second code taken from : */
/* http://www.lighthouse3d.com/opengl/glut/index.php?fps */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graphics.h"

	/* mouse function called by GLUT when a button is pressed or released */
void mouse(int, int, int, int);
void drawFloor();
void drawBorder();
void drawPillars();
void applyGravity();
void drawTestBlocks();

void draw_wall_3high(int x, int z, int cubeStyle);
void remove_surrounding_walls(int x, int z);

void draw_internal_wall(int x, int z, char direction, int cubeStyle);
void animateInternalWalls();
void remove_wall(int x1, int z1);

void test_wall1();
void test_wall2();

	/* initialize graphics library */
extern void graphicsInit(int *, char **);

	/* lighting control */
extern void setLightPosition(GLfloat, GLfloat, GLfloat);
extern GLfloat* getLightPosition();

	/* viewpoint control */
extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setViewOrientation(float, float, float);
extern void getViewOrientation(float *, float *, float *);

	/* add cube to display list so it will be drawn */
extern int addDisplayList(int, int, int);

	/* mob controls */
extern void createMob(int, float, float, float, float);
extern void setMobPosition(int, float, float, float, float);
extern void hideMob(int);
extern void showMob(int);

	/* player controls */
extern void createPlayer(int, float, float, float, float);
extern void setPlayerPosition(int, float, float, float, float);
extern void hidePlayer(int);
extern void showPlayer(int);

	/* 2D drawing functions */
extern void  draw2Dline(int, int, int, int, int);
extern void  draw2Dbox(int, int, int, int);
extern void  draw2Dtriangle(int, int, int, int, int, int);
extern void  set2Dcolour(float []);

	/* flag which is set to 1 when flying behaviour is desired */
extern int flycontrol;
	/* flag used to indicate that the test world should be used */
extern int testWorld;
	/* flag to print out frames per second */
extern int fps;
	/* flag to indicate the space bar has been pressed */
extern int space;
	/* flag indicates the program is a client when set = 1 */
extern int netClient;
	/* flag indicates the program is a server when set = 1 */
extern int netServer; 
	/* size of the window in pixels */
extern int screenWidth, screenHeight;
	/* flag indicates if map is to be printed */
extern int displayMap;

	/* frustum corner coordinates, used for visibility determination  */
extern float corners[4][3];

	/* determine which cubes are visible e.g. in view frustum */
extern void ExtractFrustum();
extern void tree(float, float, float, float, float, float, int);

/********* end of extern variable declarations **************/


	/*** collisionResponse() ***/
	/* -performs collision detection and response */
	/*  sets new xyz  to position of the viewpoint after collision */
	/* -can also be used to implement gravity by updating y position of vp*/
	/* note that the world coordinates returned from getViewPosition()
	   will be the negative value of the array indices */
void collisionResponse() {
   float x, y, z;

   /* Get the next position of the ViewPoint */
   getViewPosition(&x, &y, &z);

   /* Keep the viewpoint in bounds of the entire world, determined by the WORLDX, WORLDY, WORLDZ variables in graphics.h */
   /* This is to keep viewpoint on the platform of the world at all times */
   if ((((x * -1) < 0) || (x * -1) >= WORLDX) || ((y * -1) < 0 || (y * -1) >= WORLDY) 
         || (((z * -1) < 0) || (z * -1) >= WORLDZ)) {
      getOldViewPosition(&x,&y,&z);
      setViewPosition(x,y,z);
   }

   /* Allow viewpoint to climb a single block */
   if ((world[(int)(x * -1)][(int)(y * -1)][(int)(z * -1)] != 0)
         && (world[(int)(x * -1)][(int)((y * -1) + 1)][(int)(z * -1)] == 0)) {
      setViewPosition(x,((int)y-1),z);
   }
   /* If the next position is a block, do not allow the ViewPoint to update to that position */
   else if (world[(int)x * -1][(int)y * -1][(int)z * -1] != 0) {
      getOldViewPosition(&x, &y, &z);
      setViewPosition(x, y, z);
   }

   /* If the viewpoint position is a block, put the viewpoint back to its last position */
   getOldViewPosition(&x, &y, &z);
   if (world[(int)x * -1][(int)y * -1][(int)z * -1] != 0) {
      getViewPosition(&x, &y, &z);
      setViewPosition(x-1, -25, z-1);
   }
}



	/******* draw2D() *******/
	/* draws 2D shapes on screen */
	/* use the following functions: 			*/
	/*	draw2Dline(int, int, int, int, int);		*/
	/*	draw2Dbox(int, int, int, int);			*/
	/*	draw2Dtriangle(int, int, int, int, int, int);	*/
	/*	set2Dcolour(float []); 				*/
	/* colour must be set before other functions are called	*/
void draw2D() {

   if (testWorld) {
		/* draw some sample 2d shapes */
      GLfloat green[] = {0.0, 0.5, 0.0, 0.5};
      set2Dcolour(green);
      draw2Dline(0, 0, 500, 500, 15);
      draw2Dtriangle(0, 0, 200, 200, 0, 200);

      GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
      set2Dcolour(black);
      draw2Dbox(500, 380, 524, 388);
   } else {

	/* your code goes here */

   }

}



	/*** update() ***/
	/* background process, it is called when there are no other events */
	/* -used to control animations and perform calculations while the  */
	/*  system is running */
	/* -gravity must also implemented here, duplicate collisionResponse */
void update() {
int i, j, k, probability;
float *la;

   probability = 0;
   srand(time(NULL));

	/* sample animation for the test world, don't remove this code */
	/* -demo of animating mobs */
   if (testWorld) {

	/* sample of rotation and positioning of mob */
	/* coordinates for mob 0 */
      static float mob0x = 50.0, mob0y = 25.0, mob0z = 52.0;
      static float mob0ry = 0.0;
      static int increasingmob0 = 1;
	/* coordinates for mob 1 */
      static float mob1x = 50.0, mob1y = 25.0, mob1z = 52.0;
      static float mob1ry = 0.0;
      static int increasingmob1 = 1;

	/* move mob 0 and rotate */
	/* set mob 0 position */
      setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);

	/* move mob 0 in the x axis */
      if (increasingmob0 == 1)
         mob0x += 0.2;
      else 
         mob0x -= 0.2;
      if (mob0x > 50) increasingmob0 = 0;
      if (mob0x < 30) increasingmob0 = 1;

	/* rotate mob 0 around the y axis */
      mob0ry += 1.0;
      if (mob0ry > 360.0) mob0ry -= 360.0;

	/* move mob 1 and rotate */
      setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);

	/* move mob 1 in the z axis */
	/* when mob is moving away it is visible, when moving back it */
	/* is hidden */
      if (increasingmob1 == 1) {
         mob1z += 0.2;
         showMob(1);
      } else {
         mob1z -= 0.2;
         hideMob(1);
      }
      if (mob1z > 72) increasingmob1 = 0;
      if (mob1z < 52) increasingmob1 = 1;

	/* rotate mob 1 around the y axis */
      mob1ry += 1.0;
      if (mob1ry > 360.0) mob1ry -= 360.0;
    /* end testworld animation */

   } else {
      /* if not in fly mode, gravity will be applied to the viewpoint */
      //if(!flycontrol) applyGravity();
      
      /* Apply gravity at all times */
      applyGravity();

      /* give a 25% chance to switch a wall */   
      probability = rand() % 4;
      if(probability == 1){
         animateInternalWalls();
      }
   }
}



	/* called by GLUT when a mouse button is pressed or released */
	/* -button indicates which button was pressed or released */
	/* -state indicates a button down or button up event */
	/* -x,y are the screen coordinates when the mouse is pressed or */
	/*  released */ 
void mouse(int button, int state, int x, int y) {

   if (button == GLUT_LEFT_BUTTON)
      printf("left button - ");
   else if (button == GLUT_MIDDLE_BUTTON)
      printf("middle button - ");
   else
      printf("right button - ");

   if (state == GLUT_UP)
      printf("up - ");
   else
      printf("down - ");

   printf("%d %d\n", x, y);
}



int main(int argc, char** argv)
{
int i, j, k;
int offset;

	/* initialize the graphics system */
   graphicsInit(&argc, argv);

	/* the first part of this if statement builds a sample */
	/* world which will be used for testing */
	/* DO NOT remove this code. */
	/* Put your code in the else statment below */
	/* The testworld is only guaranteed to work with a world of
		with dimensions of 100,50,100. */
   if (testWorld == 1) {
	/* initialize world to empty */
      for(i=0; i<WORLDX; i++)
         for(j=0; j<WORLDY; j++)
            for(k=0; k<WORLDZ; k++)
               world[i][j][k] = 0;

	/* some sample objects */
	/* build a red platform */
      for(i=0; i<WORLDX; i++) {
         for(j=0; j<WORLDZ; j++) {
            world[i][24][j] = 3;
         }
      }
	/* create some green and blue cubes */
      world[50][25][50] = 1;
      world[49][25][50] = 1;
      world[49][26][50] = 1;
      world[52][25][52] = 2;
      world[52][26][52] = 2;

	/* blue box shows xy bounds of the world */
      for(i=0; i<WORLDX-1; i++) {
         world[i][25][0] = 2;
         world[i][25][WORLDZ-1] = 2;
      }
      for(i=0; i<WORLDZ-1; i++) {
         world[0][25][i] = 2;
         world[WORLDX-1][25][i] = 2;
      }

	/* create two sample mobs */
	/* these are animated in the update() function */
      createMob(0, 50.0, 25.0, 52.0, 0.0);
      createMob(1, 50.0, 25.0, 52.0, 0.0);

	/* create sample player */
      createPlayer(0, 52.0, 27.0, 52.0, 0.0);

   } else {
      /* initialize world to empty */
      for(i=0; i<WORLDX; i++)
         for(j=0; j<WORLDY; j++)
            for(k=0; k<WORLDZ; k++)
               world[i][j][k] = 0;

      /* Draw the world, with the level on the platform */
      drawFloor();
      drawBorder();
      drawPillars();
      drawTestBlocks();

      setViewPosition(-3, -25, -1);
   }

	/* starts the graphics processing loop */
	/* code after this will not run until the program exits */
   glutMainLoop();
   return 0; 
}



/* 
 * Name: animateInternalWalls()
 * Description: Animates the internal walls by selecting a random pillar, erasing its wall, and re drawing a new one
 * Parameters: none
 * Return: none
*/
void animateInternalWalls()
{
   int i, j, probability;

   probability = 0;
   i = 0;
   srand(time(NULL));

   for(i=4; i<24; i=i+4) {
      /* randomly select a pillar */  
      probability = rand() % 500;
      if(probability < 150) {
         for(j=4; j<24; j=j+4) {

            /* Slide the wall into the chosen pillars  (erase it)*/
            remove_surrounding_walls(i,j);
            remove_surrounding_walls(j,i);
            
            /* randomly select a direction */
            probability = rand() % 4;

            /* Slide the wall out of the pillar in a different direction (draw it) */
            if(probability == 0) {
               draw_internal_wall(i,j,'L', 6);
               draw_internal_wall(j,i,'L', 6);

            } else if (probability == 1) {
               draw_internal_wall(i,j,'R', 6);
               draw_internal_wall(j,i,'R', 6);
            } else if (probability == 2) {
               draw_internal_wall(i,j,'U', 6);
               draw_internal_wall(j,i,'U', 6);
            } else if (probability == 3) {
               draw_internal_wall(i,j,'D', 6);
               draw_internal_wall(j,i,'D', 6);
            }    
         }
      }
   }
}



/* 
 * Name: applyGravity()
 * Description: Apply the effect gravity to the world, also stops viewpoint if a block is underneath
 * Parameters: none
 * Return: none
*/
void applyGravity()
{
float x, y, z;

   /* Get the position of the ViewPoint */
   getViewPosition(&x, &y, &z);

   /* if no block underneath viewpoint, move viewpoint -1 in the y direction */
   if (world[(int)(x * -1)][(int)((y * -1) - 0.5)][(int)(z * -1)] == 0) {
      setViewPosition(x, y + 0.05, z);
   }
}



/* 
 * Name: draw_internal_wall()
 * Description: Draws a wall beside a specified pillar
 * Parameters: int x: x coordinate of selected pillar, int z: z coordinate of selected pillar, 
               char direction: which way to spawn the wall, int cubeStyle: color of cube
 * Return: none
*/
void draw_internal_wall(int x, int z, char direction, int cubeStyle)
{
   /* Draw Wall to left of pillar */
   if(direction == 'L') {
      draw_wall_3high(x, z-1, cubeStyle);
      draw_wall_3high(x, z-2, cubeStyle);
      draw_wall_3high(x, z-3, cubeStyle);

   /*Draw Wall to right of pillar */
   } else if (direction == 'R') {
      draw_wall_3high(x, z+1, cubeStyle);
      draw_wall_3high(x, z+2, cubeStyle);
      draw_wall_3high(x, z+3, cubeStyle);

   /*Draw Wall above pillar */   
   } else if (direction == 'U') {
      draw_wall_3high(x+1, z, cubeStyle);
      draw_wall_3high(x+2, z, cubeStyle);
      draw_wall_3high(x+3, z, cubeStyle);

   /*Draw Wall below pillar */   
   } else if (direction == 'D') {
      draw_wall_3high(x-1, z, cubeStyle);
      draw_wall_3high(x-2, z, cubeStyle);
      draw_wall_3high(x-3, z, cubeStyle);
   }
}



/* 
 * Name: draw_wall_3high()
 * Description: Draws a 3 high wall at a given position x,z with a specified cube style 
 * Parameters: int x: x coordinate of selected pillar, int z: z coordinate of selected pillar, int cubeStyle: color of cube
 * Return: none
*/
void draw_wall_3high(int x, int z, int cubeStyle)
{
   world[x][25][z] = cubeStyle;
   world[x][26][z] = cubeStyle;
   world[x][27][z] = cubeStyle;
}



/* 
 * Name: remove_surrounding_walls()
 * Description: Remove the internal walls surrounding a pillar
 * Parameters: int x: x coordinate of selected pillar, int z: z coordinate of selected pillar
 * Return: none
*/
void remove_surrounding_walls(int x, int z)
{
   draw_internal_wall(x, z, 'L', 0);
   draw_internal_wall(x, z, 'R', 0);
   draw_internal_wall(x, z, 'U', 0);
   draw_internal_wall(x, z, 'D', 0);
}



/* 
 * Name: drawFloor()
 * Description: Build a black platform that will act as the floor
 * Parameters: none
 * Return: none
*/
void drawFloor()
{
   int i, j;

   for(i=0; i<WORLDX; i++) {
         for(j=0; j<WORLDZ; j++) {
            world[i][24][j] = 4;
         }
      }
}



/* 
 * Name: drawBorder()
 * Description: Purple box shows xy bounds of the level
 * Parameters: none
 * Return: none
*/
void drawBorder()
{
   int i;

   for(i=0; i<24; i++) {
      draw_wall_3high(i,0,6);
      draw_wall_3high(i,24,6);    
   }
   for(i=0; i<24; i++) {
      draw_wall_3high(0,i,6);
      draw_wall_3high(24,i,6);
   }
}



/* 
 * Name: drawPillars()
 * Description: Build pillars for the squares for the 6x6 grid (1 square = 4x4 units)
 * Parameters: none
 * Return: none
*/
void drawPillars()
{
   int i, j;

   for(i=0; i<28; i=i+4) {  
      for(j=0; j<28; j=j+4) {
         draw_wall_3high(i,j,2);
         draw_wall_3high(j,i,2);
      }
   }
}



/* 
 * Name: drawTestBlocks()
 * Description: Draw some testing cubes for collision detection at the starting location
 * Parameters: none
 * Return: none
*/
void drawTestBlocks()
{
      /* 1 high */
      world[1][25][1] = 1;

      /* 2 high */
      world[1][25][2] = 8;
      world[1][26][2] = 8;

      /* 3 high */
      draw_wall_3high(1,3,3);
}



/* 
 * Name: test_wall1() and test_wall2()
 * Description: Draw some walls for collision detection testing 
 * Parameters: none
 * Return: none
*/
void test_wall1()
{
   draw_wall_3high(4, 3, 6);
   draw_wall_3high(4, 2, 6);
   draw_wall_3high(4, 1, 6);
}
void test_wall2()
{
   draw_wall_3high(8, 7, 6);
   draw_wall_3high(8, 6, 6);
   draw_wall_3high(8, 5, 6);
}


