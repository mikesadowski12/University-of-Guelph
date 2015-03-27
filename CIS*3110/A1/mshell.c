#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <time.h>


extern char **getln();
void executeCommand(char **args, int block, int input, int output, char *inFile, char *outFile); 
int blockCheck(char **args);
int redirectInputCheck(char **args, char **inFile);
int redirectOutputCheck(char **args, char **outFile); 
int pipeCheck(char **args, char **args1, char **args2);
int execPiping(char **args1,char **args2);
int partTwoDriver(char **args);
void addCommand(char **args);
void argCommand(char **args);
void customCommand(char **args);
void partOneDriver(char **args);
int partTwoDriver(char **args);

/*
 * Handle exit signals from child processes
 * 
 * Copied this from the example provided by the TA's
 * 
 */
void sig_handler(int signal) {
  int status;
  int result = wait(&status);
}

/*
 * The main shell function
 */ 
main() 
{
		char **args;
		char **args1 = NULL;
		char **args2 = NULL; 
		int result = 0;
		int x = 0;
		
		/*
		args1 = (char*)malloc(sizeof(char) * 1024);
		args2 = (char*)malloc(sizeof(char) * 1024);	
		*/
		
		while(1)
		{
			printf("Command: ");
			args = getln();
			
			result = pipeCheck(args,args1,args2);/*check for a pipe, execute it if it was found*/
			if(result == 0){result = partTwoDriver(args);}/*check for the part 2 commands, and execute*/
			if(result == 0){partOneDriver(args);}/*if the part two commands were not found, execvp the arguments*/			
		}
} 

/*
 * Check and execute part 1 commands
 *
 */ 
void partOneDriver(char **args)
{
	int block = 0;
	int output = 0;
	int input = 0;
	char *inFile = NULL;
	char *outFile = NULL;
		
	/*fixes segfault if args was NULL (nothing typed in)*/
	if(args[0] == NULL)
		return;
				
	/*Check for exit*/
	if(strcmp(args[0], "exit") == 0) {
		exit(0);
	}
					
	block = blockCheck(args);/*if ampersand present, do not block*/
	input = redirectInputCheck(args, &inFile);/*redirect to stdin from the file if '<' was present*/	
	output = redirectOutputCheck(args, &outFile);/*redirect to stout from the file if '>' was present*/
	printf("----------------------------------------------------\n");
	executeCommand(args, block, input, output, inFile, outFile);/*execute the command arg[0]*/
	printf("----------------------------------------------------\n");	
}

/*
 * Check and execute part 2 commands (add, arg and custom)
 *
 */ 
int partTwoDriver(char **args)
{
	if (strcmp(args[0],"add") == 0)
	{
		addCommand(args);
		return 1;
	}
	else if(strcmp(args[0],"arg") == 0)
	{
		argCommand(args);
		return 1;
	}
	else if(strcmp(args[0],"thetime") == 0)
	{
		customCommand(args);
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * 		add all arguments together, print total
 */ 
void addCommand(char **args)
{
	int i = 0;
	int total = 0;
	
	for(i = 1; args[i] != NULL; i++)
	{
		total += (int)strtol(args[i],NULL,0);
	}
	printf("----------------------------------------------------\n");	
	printf("The total is: %d\n",total);
	printf("----------------------------------------------------\n");
}

/*
 * 		count total arguments, print total
 */ 
void argCommand(char **args)
{
	int i = 0;
	int total = 0;
	for(i = 1; args[i] != NULL; i++)
	{
		total++;
	}
	printf("----------------------------------------------------\n");	
	printf("The total is: %d\n",total);
	printf("----------------------------------------------------\n");
	
}

/*
 * 		print the date and time
 */ 
void customCommand(char **args)
{
	time_t t;
	t = time(NULL);
	
	printf("----------------------------------------------------\n");
	printf("Current time and date: %s", ctime(&t));
	printf("----------------------------------------------------\n");
	
}

/*
 * Execute the command, with all arguments
 *
 */  
void executeCommand(char **args, int block, int input, int output, char *inFile, char *outFile) 
{
	pid_t child_id;
	int status = 0;

	/*Fork the child process*/
	child_id = fork();
	sigset(child_id, sig_handler);/*initialize the signal handler*/

	if(child_id == 0) 
	{
			/* Set up redirection*/
			if(input == 1){freopen(inFile, "r", stdin);}
			if(output == 1){freopen(outFile, "w+", stdout);}
			
			execvp(args[0], args);
			exit(-1);
	}

	/*Block child process if necessary*/
	if(block == 1) 
	{
			waitpid(child_id, &status, 0);
	}
}

/*
 * Check for ampersand as the last argument
 */
int blockCheck(char **args) 
{
	int i = 0;

	/*traverse to the last token in the argument command*/
	for(i = 1; args[i] != NULL; i++);

	/*if an '&' was found, free the last token, and delete the ampersand*/
	if(args[i-1][0] == '&') 
	{
		free(args[i-1]);
		args[i-1] = NULL;
		return 0;/*0 to signify that an ampersand was found, no blocking*/
	} 

	return 1;/*1 to signify that an ampersand was not found, keep blocking*/
}

/*
 * Check for input redirection
 */
int redirectInputCheck(char **args, char **inFile) 
{
	int i = 0;
	int j = 0;
	
	/*traverse to the last token in the argument command*/
	for(i = 0; args[i] != NULL; i++) 
	{

		/*if an '<' was found, free the token, and save filename*/
		if(args[i][0] == '<') 
		{
			free(args[i]);

			if(args[i+1] != NULL) 
			{
				*inFile = args[i+1];/*save the input file name token*/
			} 
			else 
			{
				return -1;
			}

			/*Re-Adjust the rest of the tokens*/
			for(j = i; args[j-1] != NULL; j++) 
			{
				args[j] = args[j+2];
			}
			return 1;
		}
	}
	return 0;
}

/*
 * Check for output redirection
 */
int redirectOutputCheck(char **args, char **outFile) 
{
	int i = 0;
	int j = 0;
	
	/*traverse to the last token in the argument command*/
	for(i = 0; args[i] != NULL; i++) 
	{

		/*if an '>' was found, free the token, and save filename*/
		if(args[i][0] == '>') 
		{
			free(args[i]);

			if(args[i+1] != NULL) 
			{
				*outFile = args[i+1];/*save the output filename token*/
			} 
			else 
			{
				return -1;
			}

			/*Re-position the rest of the tokens*/
			for(j = i; args[j-1] != NULL; j++) 
			{
				args[j] = args[j+2];
			}
			return 1;
		}
	}
	return 0;
}

int pipeCheck(char **args, char **args1, char **args2)
{
	int i = 0;
	int totalTokens = 0;
	int pipeFound = 0;
	int x = 0;
	int y = 0;
	
	for(totalTokens = 1; args[totalTokens] != NULL; totalTokens++);
	
	/*traverse the tokens to find the pipe*/
	for(i = 1; args[i] != NULL; i++)
	{
		if(strcmp(args[i],"|") == 0)/*if found, save all tokens to the left in args1, and to the right in args2*/
		{
			pipeFound = 1;
			break; /*position of the pipe is found*/
		}
	}
	
	
	if(pipeFound == 1)
	{
		args1 = (char**)malloc(sizeof(char*) * totalTokens);
		args2 = (char**)malloc(sizeof(char*) * totalTokens);
		for(y = 0; y < i; y++)
		{
			args1[y] = (char*)malloc(sizeof(char) * 1024);
			strcpy(args1[y], args[y]);
		}
		for(y = i+1,x=0; y < totalTokens; y++,x++)
		{	
			args2[x] = (char*)malloc(sizeof(char) * 1024);
			strcpy(args2[x], args[y]);			
		}
		execPiping(args1,args2);
		
	}
		
	return pipeFound;
}


int execPiping(char **args1,char **args2)
{
        int fildes[2];
        
        if(pipe(fildes) == -1) {
          perror("Pipe failed");
          exit(1);
        }

        if(fork() == 0)        //first fork
        {
            close(1);          //closing stdout
            dup(fildes[1]);     //replacing stdout with pipe write 
            close(fildes[0]);   //closing pipe read
            close(fildes[1]);

            execvp(args1[0], args1);
            exit(1);
        }

        if(fork() == 0)        //creating 2nd child
        {
            close(0);          //closing stdin
            dup(fildes[0]);     //replacing stdin with pipe read
            close(fildes[1]);   //closing pipe write
            close(fildes[0]);

            execvp(args2[0], args2);
            exit(1);
        }

        close(fildes[0]);
        close(fildes[1]);
        wait(0);
        wait(0);
        return 0;
}

