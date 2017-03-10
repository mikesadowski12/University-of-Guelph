
/* Frustum culling source code from:
        http://www.crownandcutlass.com/features/technicaldetails/frustum.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graphics.h"

#define OCTREE_LEVEL 1

extern void gradphicsInit(int *, char **);
extern void setLightPosition(GLfloat, GLfloat, GLfloat);
extern GLfloat* getLightPosition();

extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void getViewOrientation(float *, float *, float *);

extern int addDisplayList(int, int, int);

extern void createMob(int, float, float, float, float);
extern void setMobPosition(int, float, float, float, float);
extern void hideMob(int);
extern void showMob(int);

extern void createPlayer(int, float, float, float, float);
extern void setPlayerPosition(int, float, float, float, float);
extern void hidePlayer(int);
extern void showPlayer(int);

	/* flag which is set to 1 when flying behaviour is desired */
extern int flycontrol;
	/* flag used to indicate that the test world should be used */
extern int testWorld;
	/* list and count of polygons to be displayed, set during culling */
extern int displayList[MAX_DISPLAY_LIST][3];
extern int displayCount;
	/* flag to print out frames per second */
extern int fps;
	/* flag indicates the program is a client when set = 1 */
extern int netClient;
	/* flag indicates the program is a server when set = 1 */
extern int netServer; 

	/* frustum corner coordinates */
float corners[4][3];

/***********************/

float lengthTwoPoints(float x1, float y1, float z1, float x2, float y2, float z2) {
float result;
   result = sqrtf( powf((x1 - x2), 2.0) + powf((y1 - y2), 2.0) 
      + powf((z1 - z2), 2.0) );
   return(result);
}

float lengthVector(float x1, float y1, float z1) {
float result;
   result = sqrtf( powf(x1, 2.0) + powf(y1, 2.0) + powf(z1, 2.0) );
   return(result);
}

void cross(float x1, float y1, float z1, float x2, float y2, float z2,
	float *x, float *y, float *z) {
   *x = (y1*z2) - (z1*y2);
   *y = (x1*z2) - (z1*x2);
   *z = (x1*y2) - (y1*x2);
}

	/* returns radians */
void dot (float x1, float y1, float z1, float x2, float y2, float z2) {
float result;
   result = (x1 * x2) + (y1 * y2) + (z1 * z2);
   result /= (lengthVector(x1, y1, z1) * lengthVector(x2, y2, z2));
   result = acosf(result);
}

	/* the next two function use Cramer's rule to find the intersection */
	/* of three planes */
	/* used to find outer points of frustum */
	/* http://www.dreamincode.net/code/snippet530.htm */
double finddet(double a1,double a2, double a3,double b1, double b2,double b3, double c1, double c2, double c3)
{
	/*expansion of a 3x3 determinant*/
   return ((a1*b2*c3)-(a1*b3*c2)-(a2*b1*c3)+(a3*b1*c2)+(a2*b3*c1)-(a3*b2*c1)); 
}

void intersect(float a1, float b1, float c1, float d1, 
   float a2, float b2, float c2, float d2, 
   float a3, float b3, float c3, float d3,
   float *x, float *y, float *z) {
float det, detx, dety, detz;

   det=finddet(a1,a2,a3,b1,b2,b3,c1,c2,c3);   /*Find determinants*/
   detx=finddet(d1,d2,d3,b1,b2,b3,c1,c2,c3);
   dety=finddet(a1,a2,a3,d1,d2,d3,c1,c2,c3);
   detz=finddet(a1,a2,a3,b1,b2,b3,d1,d2,d3);
     
	/*Print Answers depending on various conditions*/
   if(d1==0 && d2==0 && d3==0 && det==0) {
      printf("\n Infinite Solutions\n ");
   } else if(d1==0 && d2==0 && d3==0 && det!=0) {
      *x = 0;
      *y = 0;
      *z = 0;
   } else if(det!=0) {
      *x = (detx/det);
      *y = (dety/det);
      *z = (detz/det);
//printf("x=%lf y=%lf z=%lf\n", (detx/det), (dety/det), (detz/det));
   } else if(det==0 && detx==0 && dety==0 && detz==0)
      printf("\n Infinite Solutions\n ");
   else
      printf("No Solution\n ");
} 

/***********************/

/* calculate the viewing frustum and test if cubes fall inside it */
/* code from */
/* http://www.crownandcutlass.com/features/technicaldetails/frustum.html */
float frustum[6][4];
int true = 1;
int false = 0;

void ExtractFrustum()
{
   float   proj[16];
   float   modl[16];
   float   clip[16];
   float   t;

   /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Combine the two matrices (multiply projection by modelview) */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

   /* Extract the numbers for the RIGHT plane */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Normalize the result */
   t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Extract the numbers for the LEFT plane */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Normalize the result */
   t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Extract the BOTTOM plane */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Normalize the result */
   t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* Extract the TOP plane */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Normalize the result */
   t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* Extract the FAR plane */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Normalize the result */
   t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* Extract the NEAR plane */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Normalize the result */
   t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;
}

int PointInFrustum( float x, float y, float z )
{
   int p;

   for( p = 0; p < 6; p++ )
      if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2] * z + frustum[p][3] <= 0 )
         return false;
   return true;
}

int CubeInFrustum( float x, float y, float z, float size )
{
   int p;
   int c;
   int c2 = 0;

   for( p = 0; p < 6; p++ )
   {
      c = 0;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y - size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y - size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y + size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y + size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y - size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y - size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y + size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y + size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         c++;
      if( c == 0 )
         return 0;
      if( c == 8 )
         c2++;
   }
   return (c2 == 6) ? 2 : 1;
}


int CubeInFrustum2( float x, float y, float z, float size )
{
   int p;

//ZZZ
   for( p = 0; p < 6; p++ )
   {
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y - size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y - size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y + size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y + size) + frustum[p][2] * (z - size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y - size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y - size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x - size) + frustum[p][1] * (y + size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      if( frustum[p][0] * (x + size) + frustum[p][1] * (y + size) + frustum[p][2] * (z + size) + frustum[p][3] > 0 )
         continue;
      return false;
   }
   return true;
}



/*****/



// if frustum test shows box in view
//    if level == max level then draw contents of cube
//    else call 8 subdivisions, increment level
// assumes all t[xyz] are larger than b[xyz] respectively

void tree(float bx, float by, float bz, float tx, float ty, float tz,
   int level) {
float length;
float newCentrex, newCentrey, newCentrez;
int i, j, k;

	/* find length of cube edge */
   length = (tx - bx) / 2.0;
   if (length < 0) length *= -1;

	/* if the octree cube is in the frustum then */
	/* if the bottom octree level is reached then */
	/* if the visible cube is not empty and is not surrounded then */
	/* add to the display list */ 
   if (CubeInFrustum(bx + ((tx-bx)/2), by + ((ty-by)/2), bz + ((tz-bz)/2), length )) {
      if (level == OCTREE_LEVEL) {
		/* draw cubes */
        for(i=bx; i<tx+1; i++)
           for(j=by; j<ty+1; j++)
              for(k=bz; k<tz+1; k++) {
                 if ((i<WORLDX) && (j<WORLDY) && (k<WORLDZ) && (i>-1) && (j>-1) && (k>-1))
                    if ( (world[i][j][k] != 0) &&
                        (CubeInFrustum(i+0.5, j+0.5, k+0.5, 0.5))  ) {
				/* check for six neighbours */
				/* if cube is not on the outer edge and is not*/
				/*   surrounded by 6 neighbours then draw it */
				/* else if the cube is an outside cube then */
				/*    always draw it */
                       if ( (i > 0) && (i < WORLDX-1) &&
                            (j > 0) && (j < WORLDY-1) &&
                            (k > 0) && (k < WORLDZ-1) && 
                         ((world[i+1][j][k] == 0) || (world[i-1][j][k] == 0) 
                         || (world[i][j+1][k] == 0) || (world[i][j-1][k] == 0) 
                         || (world[i][j][k+1] == 0) || (world[i][j][k-1] == 0)))
                             addDisplayList(i, j, k);
                       else if ( (i == 0) || (i == WORLDX-1) ||
                                 (j == 0) || (j == WORLDY-1) ||
                                 (k == 0) || (k == WORLDZ-1) ) 
                               addDisplayList(i, j, k);
                 }
              }
   } else {
		/* calculate centre of new cube */
         newCentrex = bx + ((tx - bx) / 2.0);
         newCentrey = by + ((ty - by) / 2.0);
         newCentrez = bz + ((tz - bz) / 2.0);
		/* call recursive tree functions, increment level */
         level++;
         tree(bx, by, bz, newCentrex, newCentrey, newCentrez, level);
         tree(newCentrex, by, bz, tx, newCentrey, newCentrez, level);
         tree(bx, by, newCentrez, newCentrex, newCentrey, tz, level);
         tree(newCentrex, by, newCentrez, tx, newCentrey, tz, level);
         tree(bx, newCentrey, bz, newCentrex, ty, newCentrez, level);
         tree(newCentrex, newCentrey, bz, tx, ty, newCentrez, level);
         tree(bx, newCentrey, newCentrez, newCentrex, ty, tz, level);
         tree(newCentrex, newCentrey, newCentrez, tx, ty, tz, level);
      }
   }

}


        /* determines which cubes are to be drawn and puts them into */
        /* the displayList  */
        /* write your cube culling code here */
void buildDisplayList() {
int i, j, k;
float newx, newy, newz;
        /* used to calculate frames per second */
static int frame=0, time, timebase=0;

   getViewPosition(&newx, &newy, &newz);


        /* calculate frustum for current viewpoint, store in frustum[][] */
   ExtractFrustum();

        /* octree, used to determine if regions are visible */
        /* stores visible cubes in a display list */
   displayCount = 0;
   tree(0.0, 0.0, 0.0, (float) WORLDX, (float) WORLDY, (float) WORLDZ, 0);


        /* frame per second calculation */
        /* don't change the following routine */
        /* Code taken from : */
        /* http://www.lighthouse3d.com/opengl/glut/index.php?fps */
   if (fps == 1) {
      frame++;
      time=glutGet(GLUT_ELAPSED_TIME);
      if (time - timebase > 1000) {
         printf("FPS:%4.2f\n", frame*1000.0/(time-timebase));
         timebase = time;
         frame = 0;
       }
   }

        /* redraw the screen at the end of the update */
   glutPostRedisplay();
}

