------IMPORTANT-------------
1. For some reason, when using the 'thetime' command before piping, the piping does not work. But if piping is used without having used that command, it works just fine and executes as normal. I could not figure out why.
2. The custom command is 'thetime'
--------------------------------------------------------------
My solution first initializes a signal handler, and enters an inifinite loop. Once in the loop,
the commands are parsed using the "flex.c" functions that were provided by the TA's. 

Once the command is typed in and enter is pressed, the program check the arguments for a pipe symbol. If it is there, it splits the arguments up (left side - right side) and executed the pipe. Next, the part 2 commands are checked (add,arg, and thetime) and executes them if necessary. If neither a pipe or any part 2 commands were found, the program executes the arguments using execvp, forking the child process, and blocking if a '&' was not found as the last argument.

