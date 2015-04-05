#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1

--------GENERAL------------
-I made the mistake of coding way too soon, so after talking to a few people I was set on an idea
	that I didn't even know would work, so therefore I had to re-write the files a bunch of times
	and now there is about 3 or 4 ideas mashed into one that is my assignment.
-How it works: in general I use a HashTable object, to store a struct ParameterValue that contains the parameter name, it's
	value, and a flag for if it was initialized. The node is placed into the Table with a key based on it's parameter name.
	A List object is used to create a List of all required parameters so that I can run the list against all the HashTable
	nodes and check the initialized flags for each one against the list. ParameterList contains a List* to make it as simple
	as possible.

--------IMPORTANT----------
1. All sources are cited with the links to the forum/websites that
	were used at the top of every file, and any copied functions are noted that they are copied.
2. A lot of the code for the ADT's HashTable and List were semi-copied from the internet, I used the general idea of all the function
	logic, and re-wrote them, and made them fit into the assignment. All sources are cited.
3. Collaborated with a few students for ideas only: Fraser Seymour and Kamil Machnik were the main ones, there were a few more but
	I do not know their names, and haven't seen them in a while to ask.
4. When parsing lists, both quotations are included in the value once parsed from the list (eg {"60"} = "60"). Also, lists
	are not allowed to have any extra { or } characters in them, no matter what. These 2 characters must be in position [0] 
	and the last position or it is a parse error.
5. Error messages occur based on the type of error, printed to the console.
6. Parameters cannot have more than 1 semi colon, or it is a parse error.
7. Boolean can be all capitals, or lower case.

-------COMPILATION------------
1. Locate the a1 directory
2. Type "make" on the command line
3. Library created is called "libpm.a" as specified in the assignment page
4. To get the test file to compile, type "make test", and "./test" to run.

**All .o files are placed in the "objects" directory, while the 
	actual library is placed in the current directory.

-------BUGS------------
1. The HashTable will segfault if an element with the same hash key is
	inserted into the table (2 equals parameter names) since the hash
	function I used was very simple, and did not account for collisions since this should
	never even happen because the parameter manager checks if the same
	key is in the hash table before it tries to insert anyways, so the
	Parameter Manager works fine.
2. REAL_TYPE numbers can be specified as 5. even though it is incorrect, it will interpret it as 5.0.
