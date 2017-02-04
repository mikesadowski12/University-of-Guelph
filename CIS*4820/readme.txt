

Readme from Assignment 1
------------------------
Building and Running the Graphics System
----------------------------------------
The program consists of three .c files.  The a1.c file contains the main()
routine and the update() function. All of the changes necessary for the
assignments can be made to this file.  The graphics.c file contains all
of the code to create the 3D graphics for the assignment. The visible.c
file contains the visible surface determination code. You should not
need to change graphics.c or visible.c.

There is a makefile which will compile the code on the Macs.
The code should build by typing make.

The executable is named a1. The command line arguments for the program
are:
	-full         run in fullscreen.
	-testworld    start with a simple world to demonstrate the system
	-fps          print the frames per second being displayed
	-help         print a list of command line arguments
	-drawall      draw all cubes in the world without using visible surface
                        detection to remove none visible cubes (very slow).
			Don't use this normally. 
To quickly see the engine running you can type ./a1 -testworld.
You can run it in fullscreen using ./a1 -testworld -full.
You can exit the program by typing q.


When the program runs the view is controlled through the mouse and
keyboard. The mouse moves the viewpoint left-right and up-down.
The keyboard controls do the following:
	w  move forward
	a  strafe left
	s  move backward
	d  strafe right
	q  quit

The 1,2,3 buttons also change the rendering options.
	1 = wire frame mode
	2 = flat shading
	3 = smooth shading
	
Note: If the controls appear to be reversed then the viewpoint is upside down.
Move the mouse until you turn over.

In the sample world created using the -testworld flag there are a few
sample boxes and animations drawn in the middle of the world. There is also
a set of blue boxes which show the outer width and depth of the world.

The f key toggles fly mode but only when gravity has been implemented.


Programming Interface to the Graphics System
--------------------------------------------

1. Drawing the world
--------------------

The game world is made of cubes. The data structure which holds all of
the objects is the three dimensional array:

	GLubyte world[100][50][100]

The GLubyte is an unsigned byte defined by OpenGL.

The indices of the array correspond to the dimensions of the world.
In order from left to right they are x,y,z.  This means the world is 100 units
in the x dimension (left to right), 50 units in the y dimension (up and down),
and 100 units in z (back to front).

The cube at location world[0][0][0] is in the lower corner of the 3D world.
The cube at location world[99][49][99] is diagonally across from
world[0][0][0] in the upper corner of the world.

Each cube drawn in the world is one unit length in each dimension.

Values are stored in the array to indicate if that position in the
world is occupied or are empty. The following would mean that
position 25,25,25 is empty:
	world[25][25][25] = 0

If the following were used:
	world[25][25][25] = 1
then position 25,25,25 would contain a green cube. 

Cubes can be drawn in different colours depending on that value stored
in the world array. The current colours which can be drawn are:
	0 empty
	1 green
	2 blue
	3 red
	4 black
	5 white
	6 purple
	7 orange
	8 yellow


2. Viewpoint Manipulation Functions
-----------------------------------
These can be used to find and set the location of the viewpoint.
They are used for implementing operations such as collision detection
and gravity.  

void getViewPosition(float *x, float *y, float *z);
-Returns the position where the viewpoint will move to on the next step.
-Returns negative numbers which you may need to make positive for some
 calculations such as using them as an index into the world array.
 You will also need to make them ints if you wish to use them as array
 indices.

void setViewPosition(float x, float y, float z);
-Sets the position where the viewpoint will move to on the next step.
-Numbers taken from the world array need to be made negative before they
 are used with setViewPosition.

void getOldViewPosition(float *x, float *y, float *z);
-Returns the position where the viewpoint is currently.
-Returns negative numbers which you may need to make positive for some
 calculations such as using them as an index into the world array.

void getViewOrientation(float *xaxis, float *yaxis, float *zaxis); 
-Returns the direction the mouse is pointing. 
-The xaxis, yaxis, and zaxis values are the amount of rotation around the
 x, y, and z  axis respectively.
-The values can be larger then 360 degrees which indicates more than
 one rotation.

3. Collision Response Function
------------------------------
void collisionResponse()
-The collision detection and response code is written in this function. 
-It is located in the a1.c file.
-Note that the f key can turn off the effect of gravity. It will
 only work once you have gravity implemented. If you press f it will allow
 you to fly around the world and look at it from above. Pressing f again
 toggles gravity back on.


4. Timing Events
----------------
OpenGL is event driven. The events which this program will respond to 
include keyboard and mouse input. The glutMainLoop() function receives
these inputs and processes them. 

The glutMainLoop() function will loop until the program ends. This means
that all of your code to initialize the world must be run before this
function is called. It also means that changes to the world must occur
inside function called by OpenGL. The only functions which you have
access to to make these updates are update() and collisionResponse() in a1.c.

When it is not otherwise drawing the scene the system will call the
update() function. This is where you can make changes to the world
array and lighting while program is running.

If you make changes to the world or the light in the udpate()
function then you may need to call glutPostRedisplay() to refresh the screen.

The update() function is not called on a predictable schedule. You will
need to check the time during updates to control the rate at which
the world changes. 


5. World Notes
--------------
-The cubes measure one unit along each axis.
-Cubes are positioned so their centre is at 0.5 greater than their
 x,y,z coordinates. So the cube at 0,0,0 is centred at 0.5, 0.5, 0.5. 
-You may see the edges of the screen don't update quickly when the viewpoint
 moves quickly. It looks like the edge of the world stops and there is a
 blocky edge visible. This isn't something you need to fix. 


6. Important Notes
-------------------
Do not remove or modify the code which builds the sample world in a1.c
in the main() when testworld == 1. 

There are three places in a1.c where it indicates that you should
add your own code.

Don't change the starting location of the viewpoint.

You can make changes to graphics.c if you wish but you are responsible
for making them work. If you break the graphics system then you have
to fix it yourself. The graphics system may change in later assignments
so you will be need to merge your changes into the new code.



7. Mob Controls
---------------
The following functions have been added to control the creation and
movement of the mobs:

   void createMob(int number, float x, float y, float z, float roty);
        -creates mob number at position x,y,z with rotation y
   void setMobPosition(int number, float x, float y, float z, float roty);
        -move a created mob to a new position and rotation
   void hideMob(int number);
        -stops drawing mob number, it become invisible
	-making mobs invisible is equivalent to removing them from the world
   void showmob(int number);
        -start drawing mob number, make it visible again

In all of the above functions:
number  -is the identifier for each mob. There can be a maximum of 10
         mobs in the game. They are numbered from 0 to 9 and this number
         is passed to all functions to indicate which mob you are updating.
x,y,z   -are the x,y,z coordinates in the world space. They are floats.
         These are world coordinates.
roty    -is the rotation of the mob around the y axis. This allows you
         to position the mob so it is facing in the direction it is
         moving or looking. It is a float.

A small sample of the mob control is included in a1.c. 
To see this demo you need to run the sample world using:
	./a1 -testworld


8. Access to the Mouse Operations
----------------------------------
The mouse() function added to a1.c. It allows you to respond to
mouse button events.



9, Client-Server Flags
----------------------
Flags were added so the user can identify if the program is running as
a client or a server. The -client flag sets the variable netClient equal
to 1. The -server flag sets the variable netServer equal to 1. They are
initially set to 0.

10. Setting the  View Orientation
---------------------------------
The counterpart to the getViewOrientation() function has been added.
It allows you to set the viewpoint rotation. When combined with the
getViewPosition() and setViewPosition() you can now position the viewpoint
in the world and rotate it to face in the desired direction.

void setViewOrientation(float xaxis, float yaxis, float zaxis); 
-Sets the orientation of the viewpoint.
-The xaxis, yaxis, and zaxis values are the amount of rotation around the
 x, y, and z axis respectively.
-Note that the rotations are around the world axis and not around the current
 viewpoint. This means you will need to perform some calculations to
 convert from the world axis to the local viewpoint axis if you wish to
 rotate relative to the current viewpoint.
-The values can be larger then 360 degrees which indicates more than
 one rotation.

11. 2D Drawing Functions
------------------------
Several function can be used to draw two dimensional shapes on the screen.
These are useful for displaying information such as maps, health bars,
inventory.

All two dimensional drawing functions must be placed in the:
	void draw2D()
function in a1.c. This is the only place where they will execute correctly.
There is a comment which indicates where your code can be added. There is
also a sample of the 2D drawing functions which is run when the -testworld
command line argument is used.

The screen is two dimensional with the (0,0) coordinate in the lower
left corner and the maximum default screen coordinates are (1023, 767)
in the upper right corner.

Inside the draw2D() function you can call the following functions:

void  set2Dcolour(float colour[]);
-Sets the RGBA colour for the 2D images which are drawn after it.
-The colour array contains four floats which contain the red, green, blue
 and alpha values. 
-The colour stays the same until it is changed by a later call to
 set2Dcolour() with different parameters.

void  draw2Dline(int x1, int y1, int x2, int y2, int lineWidth);
-Draw a line from (x1, y1) to (x2, y2).
-The lineWidth parameter indicates the width in pixels of the line.

void  draw2Dbox(int x1, int y1, int x2, int y2);
-Draw a box with the lower left corner at (x1, y1) and the upper right
 corner at (x2, y2).

void  draw2Dtriangle(int x1, int y1, int x2, int y2, int x3, int y3);
-Draw a triangle with the coordinates of it's three vertices at (x1,y1),
 (x2,y2), and (x3,y3).


12. Display Map Flag
--------------------
A flag has been added which can be used to toggle a map on and off and
to change the size of the map.  The flag is:
	int displayMap;

It is toggled using the m key. The flag can have three values, 0, 1, and 2.
When the m key is pressed the value of displayMap is increased by 1.
When the value is greater than 2 it is reset to be equal to 0.
The flag is set to 1 on startup.

The meaning of the values stored in displayMap are:
	0   no map displayed
	1   a small map in the corner is displayed
	2   a larger map is displayed in the centre of the screen

You can use this with the draw2D() function to display a map on the
screen.


13. Screen Size Variables
-------------------------
The variables:
	int screenWidth, screenHeight;
indicate the width and height of the current display window in pixels.
They will reflect the correct values when the display window is resized.



14. Player Controls
-------------------
Players can now be drawn. This is necessary to see other players in
a networked game.  Players are gray with red eyes.

The functions to control the players are identical to the mob control
functions with the names changed to indicate they control players. 
   void createPlayer(int number, float x, float y, float z, float roty);
   void setPlayerPosition(int number, float x, float y, float z, float roty);
   void hidePlayer(int number);
   void showPlayer(int number);

There is a example of a player drawn in the sample world.


15. Space Flag Added
--------------------
A variable named space has been added to the program. It is set equal
to 1 when the space bar is pressed. You can use this to respond to
the player pushing the space bar.

Reset the variable to be equal to 0 once you have responded to the key press.




16 Setting the Light Position
-----------------------------
There is a single light in the world.  The position of the light
is controlled through two functions:

	void setLightPosition(GLfloat x, GLfloat y, GLfloat z);
	GLfloat* getLightPosition();

The setLightPosition() function moves the light source to location x,y,z in the
world. The getLightPosition() function returns a pointer to an array
of floats containing current the x,y,z location of the light source.

To see the effect of a change through setLightPosition() you will
need to call glutPostRedisplay() to update the screen. 




Appendix A - Culling Objects that Cannot Be Seen
------------------------------------------------
You probably don't need this unless you are modifying the frustum
culling code. 

Display Lists
--------------
This is only used for the visible surface determination part of the system.
Unless you are changing visible.c then you do not need to use this.
You should not create objects in the world using addDisplayList().

An array named displayList has been created which you put the cube indices
that you want to be drawn. The function addDisplayList() is used to
add cubes to the list.
        e.g. The following would set the cube at world[1][3][5] to be drawn.
            addDisplayList(1,3,5);
This is used so then entire world is not drawn with each frame.
Only the cubes which you determine are visible should be added
to the display list.

Add the cubes you derive from visibility testing to the list.
There is also a counter named displayCount which contains the
number of elements in displayList[][].  You do not need to increment
displayCount but you need to set it equal to zero when you build a new
display list.  You need to build a new displayList each time you
perform culling (each time buildDisplayList() is called).


Empty Functions
---------------
void buildDisplayList()
-This is where you perform culling and add visible cubes to the display
 list.  There is some sample code here which moves all of the cubes in
 the world to the display list. This duplicates the original behaviour of
 assignment 1.  This should be replaced with your visibility/culling code.


Culling Information
-------------------
-The web page at:
	http://www.crownandcutlass.com/features/technicaldetails/frustum.html
contains a good explanation of how to determine the viewing frustum for
a viewpoint in OpenGL. There is also some useful code there. 



Frames Per Second (FPS) Printing
--------------------------------
The FPS are no longer printed automatically. There is a -fps command
line flag which turns this functionality one.



