/*
#NAME: Mike Sadowski
#DATE: November 22nd, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 4
*/
#include "avl_tree.h"

avlNode* insertNode(avlNode *n, char *data);

int main()
{
	char userInput = 0;
	char freq[1000] = {0};
	avlNode *tree = NULL;
	int sizeCount = 0;
	system("clear");
	printf("WELCOME TO THE AVL TREE PROGRAM\n");
	printf("Name: Mike Sadowski\n");
	printf("ID: 0864810\n");
	while(userInput != '7')
	{
		userInput = printMenu();/*menu loops until user chooses to exit*/
		switch(userInput)
		{
			case '1':
				tree = initialization();
				break;
			case '2':
				findNode(tree);
				break;
			case '3':
				tree = insertNodeToTree(tree);
				break;
			case '4':
				tree = removeNode(tree);
				break;
			case '5':
				printHeightAndSize(tree,&sizeCount);
				printf("Height: %d, Size: %d",height(tree), sizeCount);
				break;
			case '6':
				printf("frequency: ");
				scanf("%s", freq);
				aboveAFrequency(tree,atoi(freq));
				break;

		}
		getchar();
	}
	freeTree(tree);
	return 1;		
}

avlNode* initialization(void)
{
	avlNode *tree = NULL;
	char fileName[1000] = {0};

	printf("filename: ");
	scanf("%s", fileName);

	tree = readFile(fileName, tree);

	return tree;
}
/*read file, store all data into an avl tree, return tree root*/
avlNode* readFile(char *fileName,avlNode *tree)
{
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		return NULL;
	}
	char buffer[1000] = {0};
	char *tokens;

	while(fgets(buffer, 1000, fp) != NULL)
	{		
		tokens = strtok(buffer, " ");
		while(tokens != NULL)/*loop through the tokens, place each token into an array*/
		{
			if(tokens[strlen(tokens)-1] < 33)/*remove new line from token*/
			{
				tokens[strlen(tokens)-1] = 0;
			}
			/*create node with the data,insert to list, ignore blank lines*/
			if(strlen(tokens) > 1)
			{
				tree = insertNode(tree, tokens);
				/*printf("%s\n",tokens);*/
			}
			tokens = strtok(NULL, " ");
		}
	}
	fclose(fp);
	return tree;
}


void findNode(avlNode* tree)
{
	char key[1000] = {0};
	avlNode* n = NULL;

	printf("find key: ");
	scanf("%s", key);	

	n = find(tree,key);
	if(n == NULL){printf("no_such_key");}
	else{printf("key: %s, frequency: %d",key,n->frequency);}
}

avlNode* insertNodeToTree(avlNode* tree)
{
	char key[1000] = {0};
	avlNode* n = NULL;

	printf("insert key: ");
	scanf("%s", key);

	tree = insertNode(tree, key);
	n = find(tree, key);
	printf("key: %s, frequency: %d",key,n->frequency);
	return tree;
}

avlNode* removeNode(avlNode* tree)
{
	char key[1000] = {0};
	avlNode* n = NULL;

	printf("remove key: ");
	scanf("%s", key);	

	n = find(tree,key);
	if(n == NULL){printf("no_such_key");}
	else{printf("key: %s, frequency: %d",key,n->frequency);}

	return tree;

}

void printHeightAndSize(avlNode* n, int *count)
{	
	if(n == NULL)
	{
		return;
	}

	if(n->left != NULL && n->right != NULL){*count = *count + 1;}

	printHeightAndSize(n->left,count);
	printHeightAndSize(n->right,count);
}

/*Print the menu and grab the choice*/
char printMenu(void)
{
	printf("\n\n1. Initialization\n");
	printf("2. Find\n");
	printf("3. Insert\n");
	printf("4. Remove\n");
	printf("5. Check Height and Size\n");
	printf("6. Find All (above a given frequency)\n");
	printf("7. Exit\n");
	printf("avl/> ");

	return(getchar());
}

void aboveAFrequency(avlNode *n, int freq)
{
	if(n == NULL)
	{
		return;
	}

	if(n->frequency >= freq){printf("key: %s, frequency: %d\n",n->key,n->frequency);}

	aboveAFrequency(n->left,freq);
	aboveAFrequency(n->right,freq);

}



