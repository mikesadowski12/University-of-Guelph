
/*sources:
 * http://stackoverflow.com/questions/10113028/how-should-i-start-making-a-fcfs-scheduling-program-in-c-or-c
 * 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int detailed_mode = 0;
int verbose_mode = 0;
int roundrobin_mode = 0;
int quantum = 0;

int number_of_processes = 0;
int thread_switch = 0;
int process_switch = 0;

int total_time = 0;
int turnaround_time = 0;
float cpu_utilization = 0;
float avg_turnaround_time = 0;

typedef struct CPU_Burst
{
	int cpu_time;
	int io_time;
}CPU_Burst;

typedef struct thread
{
	int arrival_time;
	int number_of_CPU;
	CPU_Burst cpuBursts[50];		
}thread;

typedef struct process
{
	int process_id;
	int number_of_threads;
	thread threads[50];
		
	struct process *next;	
}process;

void checkCMDLineArgs(int argc, char **argv);
void read_sim(process *theHead, FILE *fp);
void readLine(int *result, FILE *fp);

void read_process(process *node, FILE *fp);
void read_thread(thread *thrd, FILE *fp);
void read_CPU(CPU_Burst *cpub, FILE *fp);

void run_sim(process *theHead);
void burster(CPU_Burst *runMe, char flag);
void delete_sim(process *theHead);

void printSim(process *theHead);
int Q_isEmpty(process *theHead);
process *Q_pop(process *theHead);

int main(int argc, char *argv[])
{	
	process *theHead = NULL;
	process *next = NULL;
	int total_threads = 0;
	int total_cpu = 0;
	int x = 0;
	int y = 0;
	
	theHead = (process*)malloc(sizeof(process));
			
	if (argc != 0) /* if there are arguments, check them */
	{
		checkCMDLineArgs(argc, argv);					
	}
	    	
	read_sim(theHead,stdin);
	next = theHead;
	while(next != NULL)
	{
		total_threads += next->number_of_threads;
		
		for(x = 0; x < next->number_of_threads; x++)
		{
			for(y = 0; y < next->threads[x].number_of_CPU; y++)
			{
				total_cpu += next->threads[x].cpuBursts[y].cpu_time;
			}
		}
			
		next = next->next;
	}	
	run_sim(theHead);
	
	avg_turnaround_time = (float)turnaround_time/total_threads;
	cpu_utilization = (float)total_cpu/total_time * 100;
	if(!verbose_mode)
	{
		if(roundrobin_mode)
		{
			printf("\n\nRound Robin (quantum = %d time units):\n", quantum); 
		}
		else
		{
			printf("\n\nFCFS:\n"); 
		}
		
		printf("\nTotal Time required is %d time units\n", total_time);
		printf("Average Turnaround Time is %0.1f time units\n", avg_turnaround_time);
		printf("CPU Utilization is %0.1f%%\n\n", cpu_utilization);						
	}	
	
	delete_sim(theHead);
					
	return 1;
}

void delete_sim(process *theHead)
{
	process *temp = theHead;
	
	while(theHead != NULL)
	{
		temp = theHead;		
		theHead = theHead->next;
		free(temp);
	}
}

/*run the simulation using the linked list head*/
void run_sim(process *theHead)
{
	process *readyQ = theHead->next;
	int x = 0;
	int y = 0;
	int process_count = 1;
	int cpu_count = 0;
	int io_count = 0;
	int turnaround = 0;
	int time = 0;

	while(readyQ != NULL)
	{
		if(!Q_isEmpty(readyQ))
		{
			for(x = 0; x < readyQ->number_of_threads; x++)
			{	
				cpu_count = 0;
				io_count = 0;
				turnaround = 0;
				time = total_time + 7;
												
				//Run cpu bursts in the thread
				for(y = 0; y < readyQ->threads[x].number_of_CPU; y++)
				{
					cpu_count += readyQ->threads[x].cpuBursts[y].cpu_time;
					burster(&(readyQ->threads[x].cpuBursts[y]), 'c');
				}
				
				//Run io bursts in the thread
				for(y = 0; y < readyQ->threads[x].number_of_CPU; y++)
				{	
					io_count += readyQ->threads[x].cpuBursts[y].io_time;		
					burster(&(readyQ->threads[x].cpuBursts[y]), 'i');										
				}
				
				if(verbose_mode == 1)
				{				
					printf("\nAt time %d: Thread %d of Process %d moves from new to ready\n", time,x+1,process_count);
					printf("\nAt time %d: Thread %d of Process %d moves from ready to running\n", time+7,x+1,process_count);
					printf("\nAt time %d: Thread %d of Process %d moves from running to terminated\n", total_time,x+1,process_count);
					
				}				
				if(detailed_mode == 1)
				{
					turnaround = total_time - readyQ->threads[x].arrival_time;
					turnaround = turnaround/readyQ->threads[x].number_of_CPU;
					
					printf("\n\nThread %d of Process %d:\n", x+1, process_count);
					printf("\narrival time: %d", time);
					printf("\nservice time: %d units", cpu_count); 
					printf("\nI/O time: %d units", io_count); 
					printf("\nturnaround time: %d units", turnaround); 
					printf("\nfinish time: %d units", total_time); 				
				}	
				
				turnaround_time += total_time - readyQ->threads[x].arrival_time;					
			}		
		}
		process_count++;
		readyQ = readyQ->next;		
	}	
}
/*"run" the cpu burst or io burst, aka just adding the ints to a total*/
void burster(CPU_Burst *runMe, char flag)
{
	if(flag == 'i')
	{
		total_time += runMe->io_time;
		runMe->io_time = 0;
	}
	else if(flag == 'c')
	{
		total_time += runMe->cpu_time;
		runMe->cpu_time = 0;		
	}	
}
int Q_isEmpty(process *theHead)
{
	if(theHead == NULL)
	{
		return 1;
	}
	return 0;
}
process *Q_pop(process *theHead)
{
	process *pop = theHead->next;
	theHead = theHead->next;
	return pop;
}
/*for debugging*/
void printSim(process *theHead)
{
	process *next = theHead->next;
	int x = 0;
	int y = 0;
	
	while(next != NULL)
	{
		printf("ID: %d\n", next->process_id );
		printf("#THREADS: %d\n", next->number_of_threads);
		for(x = 0; x < next->number_of_threads; x++)
		{
			printf("--THREAD #: %d\n", x+1);
			printf("--ARRIVAL: %d\n",next->threads[x].arrival_time);
			printf("--#CPU: %d\n", next->threads[x].number_of_CPU);						
			for(y = 0; y < next->threads[x].number_of_CPU; y++)
			{			
				printf("----CPU #: %d\n", y+1);
				printf("----#CPU T: %d\n", next->threads[x].cpuBursts[y].cpu_time);
				printf("----#IO T: %d\n", next->threads[x].cpuBursts[y].io_time);
			}
		}
		printf("---------------------------------------\n");
		next = next->next;
	}
		
}
/*parse the text file, save the process information in a queue*/
void read_sim(process *theHead, FILE *fp)
{
	int x = 0;
	process *lastNode = theHead;
	process *node = NULL;
	int line_result[3] = {0,0,0};

	if (!fp)
	{
		printf("PARSE ERROR: Input-Stream is NULL\n");
		return;
	}		
			
	readLine(line_result, fp);
			
	number_of_processes = line_result[0];
	thread_switch = line_result[1];
	process_switch = line_result[2];
	
	for(x = 0; x < number_of_processes; x++)
	{		
		node = (process*)malloc(sizeof(process));	
		lastNode->next = node;
		read_process(node, fp);
		lastNode = node;	
	}		
}	
void read_process(process *node, FILE *fp)
{
	int line_result[3] = {0,0,0};
	int x = 0;
		
	readLine(line_result, fp);
	
	node->process_id = line_result[0];
	node->number_of_threads = line_result[1];
		
	for(x = 0; x < node->number_of_threads; x++)
	{		
		read_thread(&(node->threads[x]),fp);		
	}
}
void read_thread(thread *thrd, FILE *fp)
{
	int line_result[3] = {0,0,0};
	int x = 0;
	
	readLine(line_result, fp);
	
	thrd->arrival_time = line_result[1];
	thrd->number_of_CPU = line_result[2];
		
	for(x = 0; x < thrd->number_of_CPU; x++)
	{		
		read_CPU(&(thrd->cpuBursts[x]),fp);		
	}	
}
void read_CPU(CPU_Burst *cpub, FILE *fp)
{
	int line_result[3] = {0,0,0};

	readLine(line_result, fp);
	
	cpub->cpu_time = line_result[1];
	cpub->io_time = line_result[2];
}
/*tokenize each line, return the line in tokens in a 2d array*/
void readLine(int *result, FILE *fp)
{
	char buffer[1024] = {0};	
	char *token = NULL;
	char *newline = NULL;
	char **theLine = NULL;	
	int x = 0;

	theLine = (char**)malloc(sizeof(char*) * 3);
	for(x = 0; x < 3; x++)
	{
		theLine[x] = (char*)malloc(sizeof(char) * 1024);	
	}	
		
	fgets(buffer, 1024, fp);
		
	token = strtok(buffer, " ");			
	while(token != NULL) 
	{
		newline = strchr(token, '\n');
		if(newline)
		{
			*newline = 0;
		}					
		*result = atoi(token);
		result++;
		token = strtok(NULL, " ");
	}
}
/*check all the command line arguments for the flags, and set them*/
void checkCMDLineArgs(int argc, char **argv)
{
	int x = 0;
	
	for(x = 0; x < argc; x++)
	{
		if(strcmp(argv[x],"-d") == 0)
		{
			detailed_mode = 1;
		}
		else if(strcmp(argv[x],"-v") == 0)
		{
			verbose_mode = 1;
		}		
		else if(strcmp(argv[x],"-r") == 0)
		{
			roundrobin_mode = 1;
		}
		else
		{
			quantum = atoi(argv[x]);
		}			
	} 	
}
