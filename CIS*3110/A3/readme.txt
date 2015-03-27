------IMPORTANT-------------
1. Max 5 philosophers or program endlessly simulates for some reason. 
2. For part 2, all the methods are completing as intended, just the print statements get messed up on the last 3. Simulation is working though. Had no time to fix it.
--------------------------------------------------------------
--PART 1:

I used global variables to keep track of my philosophers. I used a state variable that shows the state of the current philosopher, so that he can eat
eat/think accordingly. A global counter is used to track the amount of times every philosopher has eaten, and when they have eaten the correct
amount of times the program stops.

To simulate the problem, i used pthread and semaphores to signal if the current forks are being used or not, so that the philosophers can act
properly to what is happening. To simulate the grabbing and putting down of the forks, i created functions that handle each action
for the philosophers. Relatively simple. 

--PART 2:

My solution reads the text file in, and places all of the processes into a ready-queue (which is just a linked list). Next, the simulation begins.
The processes are loaded into memory (which is another linked list) in order until the next process cannot fit due to the max size of the memory (128mb).
So now the first swap has to occur for the current process to be swapped into memory (a struct for the memory keeps track of how many processes are in the list,
and how much "memory" they consume).  
The solution iterates between all 4 methods of swapping because it was not clear how the methods were to be implemented, so this solution
just iterates through each one, doing all of them within the same simulation, in order first fit, next fit, best-fit, worst fit. To do this,
I created a function that keeps track of the order of the swapping methods, and is called before the next process is examined so that the
simulation knows which swapping method it is supposed to do, and swaps the processes out/in.
Once complete (when a process was swapped 3 times), the process is placed into a done queue (a 3rd linked list) to not be swapped in anymore. 
If all of the processes that have not finished yet can fit inside of the memory, or all the processes have been swapped 3 times, 
the simulation finishes, and prints the result of the simulation. 
