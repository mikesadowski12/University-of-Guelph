/*
#NAME: Mike Sadowski
#DATE: October 28th, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 3
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createHeap(int rows, int cols, int array[rows][cols]);
void readFile(int rows, int cols, int heapContents[rows][cols]);
void makeKey(int rows, int cols, int heapContents[rows][cols]);
void switchArrays(int line1[12], int line2[12]);


/* reads the text file data in, creates a 20 by 10 array of integers, adds a key calculated by first 3 elements added together, creates a heap based on the keys, and sorts the heap in a down-heap, prints the result as well as the pre-sorted text file contents*/
int main()
{
	int m = 20;
	int n = 12;
	int heapContents[m][n];/*create room for 1 more element, which will be the key*/
	int i,j;

	system("clear");
	readFile(m, n, heapContents);/*read arrays from text file*/
	makeKey(m, n, heapContents);/*resize the array, make a key*/
	printf("Printing the textfile contents with keys: \n");
	getchar();
	for (j = 0; j < m; j++)
	{
		for (i = 1; i < n; i++)/*do not print first element or key*/
		{
			printf("%d ",heapContents[j][i]);
		}
		printf("\n");	
	}	
	createHeap(m,n,heapContents);
	printf("\n\nPrinting the now-sorted-heap: \n");
	getchar();
	for (j = 0; j < m; j++)
	{
		for (i = 2; i < n; i++)/*do not print first element or key*/
		{
			printf("%d ",heapContents[j][i]);
		}
		printf("\n");	
	}
	return 1;
}

/*create the key by adding the first 3 elements, put key at front of array*/
void makeKey(int rows, int cols, int heapContents[rows][cols])
{
	int row = 0;

	for (row = 0; row < rows; row++)
	{
		heapContents[row][0] = row;
		heapContents[row][1] = heapContents[row][2] + heapContents[row][3] + heapContents[row][4];
	}

}
/*switches all elements of 2 arrays size 12*/
void switchArrays(int line1[12], int line2[12])
{
	int i = 0;
	int temp = 0;

	for(i=0; i < 12; i++)
	{
		temp = line1[i];
		line1[i] = line2[i];
		line2[i] = temp;
	}

}
/*create the heap*/
void createHeap(int rows, int cols, int array[rows][cols])
{
	int ParentsPos, childIndex, flag;
	
	for(ParentsPos = 0; ParentsPos < rows; ParentsPos++)
	{
		flag = 0;
		childIndex = (ParentsPos*2)+1;/*calculate leaf positions*/
		if(childIndex >= rows){return;}

		/*if the left leaf is greater than the parent, switch them*/
		if(array[ParentsPos][1] > array[childIndex][1])
		{
			switchArrays(array[ParentsPos], array[childIndex]);
			flag = 1;/*if a switch was made, start at the top of the tree to re-order everything*/		
		}
		if(childIndex+1 >= rows){return;}/*if the index to the leaves exceeds the array size, finished sorting*/
		/*if the right leaf is greater than the parent, switch them*/		
		if(array[ParentsPos][1] > array[childIndex+1][1])
		{
			switchArrays(array[ParentsPos], array[childIndex+1]);
			flag = 1;/*if a switch was made, start at the top of the tree to re-order everything*/		
		}	
		if (flag == 1){ParentsPos = -1;}/*if a switch was made, start at the top of the tree to re-order everything*/		
	}				
}
/*read file f.dat, store all lines into an array[20][12], 2 extra elements for the key and because the first one is not used*/
void readFile(int rows, int cols, int heapContents[rows][cols])
{
	FILE *fp = fopen("f.dat", "r");
	char buffer[1000] = {0};
	char *tokens;
	int row = 0;
	int column = 2;

	while(fgets(buffer, 1000, fp) != NULL)
	{	
		printf("\n");
		column = 2;		
		tokens = strtok(buffer, " ");
		while(tokens != NULL)/*loop through the tokens, place each one in the appropriate variable*/
		{
			if(strlen(tokens) > 1)/*ignore the \0 at the end since they are 2 digits*/
			{
				heapContents[row][column] = atoi(tokens);
			}

			column++;
			tokens = strtok(NULL, " ");
		}
		row++;
	}
	fclose(fp);
}





