/* SOURCES:
 * http://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread.h.html
 * http://stackoverflow.com/questions/23529773/dining-philosopher-program-c
 * Old conestoga college project
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MemorySim
{
	char name;
	int size;
	int swap_count;
	
	struct MemorySim *next;	
}MemorySim;

typedef struct RAM
{
	int totalSize;
	int processCount;	
}RAM;



MemorySim *get_processes(MemorySim *head, char *fileName);
MemorySim *create_node(char name, int size, int count);
MemorySim *addToList(MemorySim *head, MemorySim *newNode);
MemorySim* freeList(MemorySim *head);
void print_list(MemorySim *head);
MemorySim* popProcess(void);
MemorySim* popRAM(void);
MemorySim* removeNode(MemorySim* node);
MemorySim* removeRAMNode(void);

void simulation(void);
void load_process(MemorySim *node);
void swap_process(void);
void remove_process(RAM *head, int headRoom);


RAM *simulationRAM = NULL;
MemorySim *RAMhead = NULL;
MemorySim *processhead = NULL;
MemorySim *done = NULL;
MemorySim *previousNode = NULL;

int number_of_processes = 0;
int number_of_processes_finished = 0;

int total_loads = 0;
double average_holes = 0;
double cumumemusage = 0;
double average_processes = 0;
void main(int argc, char *argv[])
{
	
	char *fileName = argv[1];
	
	processhead = get_processes(processhead, fileName);
	processhead = processhead->next;
	printf("========FIRST FIT========\n");
	simulation();
	processhead = done->next;
	//processhead = processhead->next;
	printf("========NEXT FIT========\n");
	simulation();
	processhead = done->next;
	//processhead = processhead->next;	
	printf("========BEST FIT========\n");
	simulation();
	processhead = done->next;
	//processhead = processhead->next;	
	printf("========WORST FIT========\n");
	simulation();				
	//RAMhead = RAMhead->next;
	//printf("RAM: \n");
	//print_list(RAMhead);
	//printf("swap: \n");
	//print_list(processhead);
	//printf("done: \n");
	//print_list(done);	
	freeList(RAMhead);
	freeList(processhead);
	freeList(done);	
	return;
}

void simulation(void)
{
	simulationRAM = (RAM*) malloc(sizeof(RAM));
	MemorySim *current = processhead;
	MemorySim *newnode = NULL;
	RAMhead = (MemorySim*) malloc(sizeof(MemorySim));
	done = (MemorySim*) malloc(sizeof(MemorySim));
	
	RAMhead = create_node('0',0,0);
	done = create_node('0',0,0);
	
	simulationRAM->totalSize = 0;
	simulationRAM->processCount = 0;
	previousNode = processhead;
	double memusage = 0;
	
	while(current != NULL)
	{	
		//printf("ram size: %d   processsize: %d\n", simulationRAM->totalSize, current->size);
		if(current->swap_count >= 3)
		{
			newnode = removeNode(processhead);
			addToList(done, newnode);
			number_of_processes_finished++;
		}
		else
		{
			if(simulationRAM->totalSize + current->size <= 128)
			{
				simulationRAM->processCount++;
				simulationRAM->totalSize += current->size;
				memusage = (float)simulationRAM->totalSize/128*100;
				cumumemusage += memusage;
				printf("%c loaded, #processes = %d, holes = %dMB, %%memusage = %.00f, cumulative %%mem = %.0f\n", current->name, simulationRAM->processCount, 128-simulationRAM->totalSize, memusage,cumumemusage/total_loads);							
				average_holes += 128-simulationRAM->totalSize;	
				average_processes += simulationRAM->processCount; 			
				newnode = removeNode(current);
				addToList(RAMhead, newnode);
				total_loads++;
			}
			else
			{	
				while(128-simulationRAM->totalSize < current->size)/*make room for new process*/
				{
					newnode = removeRAMNode();
					if(newnode != NULL)
					{
						simulationRAM->totalSize -= newnode->size;
						simulationRAM->processCount--;
						addToList(processhead, newnode);
						newnode->swap_count++;
						//printf("popped [%c] off ram with count of [%d] %d\n", newnode->name,newnode->swap_count,newnode->size );				
					}
				
				}						
				simulationRAM->processCount++;
				simulationRAM->totalSize += current->size;
				memusage = (float)simulationRAM->totalSize/128*100;
				cumumemusage += memusage;
				average_processes += simulationRAM->processCount; 
				printf("%c loaded, #processes = %d, holes = %dMB, %%memusage = %.0f, cumulative %%mem = %.0f\n", current->name, simulationRAM->processCount, 128-simulationRAM->totalSize, memusage, cumumemusage/total_loads);							
				average_holes += 128-simulationRAM->totalSize;	
				newnode = removeNode(current);
				addToList(RAMhead, newnode);
				total_loads++;																		
			}
		}				
		current = current->next;
							
	}	
	//RAMhead = RAMhead->next;
	newnode = removeRAMNode();
	while(newnode != NULL)
	{
		addToList(done,newnode);
		newnode = removeRAMNode();
	}
	
	printf("\nTotal loads = %d, average #processes = %.0f, average holes = %.0fMB, cumulative %%mem = %.0f\n",total_loads, average_processes/total_loads, average_holes/total_loads, cumumemusage/total_loads);
}
MemorySim* removeRAMNode(void)
{
	MemorySim *theNewNode = NULL;
	MemorySim *temp = NULL;
	
	if(RAMhead->next != NULL)
	{
		temp = RAMhead->next;
		theNewNode = create_node(temp->name,temp->size,temp->swap_count);
		RAMhead->next = temp->next;
		free(temp);
	}	
	return theNewNode;	
}
MemorySim* removeNode(MemorySim* node)
{
	MemorySim *theNewNode = create_node(node->name,node->size,node->swap_count);
	MemorySim *temp = processhead;
	MemorySim *temp2 = NULL;
	
	if(node->name == processhead->name)
	{
		processhead = processhead->next;
		free(temp);
	}
	else
	{
		while(node->name != temp->next->name)
		{			
			temp = temp->next;
		}
		temp2 = temp->next;
		temp->next = temp2->next;
		free(temp2);	
	}		
	return theNewNode;	
}


/*
 * Get processes from the file, build original linked list
 */
MemorySim *get_processes(MemorySim *head, char *fileName)
{
	FILE *in = NULL;
	char buffer[128];
	char *token;
	char *newLine;
	char name = 0;
	int size = 0;
	MemorySim *newNode = NULL;
	head = create_node(0,0,0);	
	in = fopen(fileName, "r");
	if(!in)
	{
		return;
	}
	/*Add everyline of the file into the linked list*/			
	while (fgets(buffer, 128, in))
	{
		newLine = strchr(buffer, '\n');
		if(newLine)
		{
			*newLine = 0;
		}	
		token = strtok(buffer, " ");
		name = token[0];
		while(token != NULL) 
		{
			size = atoi(token);
			token = strtok(NULL, " ");				
		}
		newNode = create_node(name,size,0);		
		addToList(head, newNode);
		number_of_processes++;		
	}
	
	fclose(in);
	return head;
}
/*
 * Linked List Functions
 */ 
MemorySim *create_node(char name, int size, int count)
{
	MemorySim *newNode = (MemorySim*) malloc(sizeof(MemorySim));
			
	if(newNode == NULL)
    {
        return NULL;
    } 
	newNode->name = name;
	newNode->size = size;
	newNode->swap_count	= count;
	newNode->next = NULL;
	
	return newNode;
	
}
MemorySim *addToList(MemorySim *head, MemorySim *newNode)
{
	MemorySim *current = head;
		//printf("------------------------------------------------------\n");
    if(head == NULL)
    {
		printf("List is NULL\n");
        return NULL;
    }

    while(current->next != NULL)
    {
		current = current->next;
		
		//printf("loop4\n");
		//printf("%c %d\n",current->name, current->size);
	}
    current->next = newNode;
    newNode->next = NULL;
  
    return head;
}
MemorySim* freeList(MemorySim *head)
{
	MemorySim *current = head;	
	MemorySim *prev = head;
	
	if(head)
	{
		do
		{
			prev = current;			
			current = current->next;
			free(prev);	
		}while(current != NULL);
	}
}
void print_list(MemorySim *head)
{
	MemorySim *tempHead = head;
	
    while(tempHead != NULL)
    {	
		printf( "%c ", tempHead->name);
		printf( "%d\n", tempHead->size);
			
		tempHead = tempHead->next;	
	}
}
