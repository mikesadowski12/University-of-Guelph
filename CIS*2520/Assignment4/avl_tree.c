/*
#NAME: Mike Sadowski
#DATE: November 22nd, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 4
*/

#include "avl_tree.h"

/*insert a new node into the tree, start from top of the tree, and work down until a position if found to insert the node*/
avlNode* insertNode(avlNode *n, char *data)
{

	/*check if node is empty, insert here if it is*/
	if(n == NULL)
	{
		n = (avlNode*)malloc(sizeof(avlNode));
		if (n == NULL)
		{
			printf("\nMEMORY ERROR\n");
			return NULL;
		}
		n->key = (char*)malloc(1000*sizeof(char));
		if (n->key == NULL)
		{
			printf("\nMEMORY ERROR\n");
			return NULL;
		}
		/*Initialize first node in the tree*/
		strcpy(n->key,data);
		n->height = 0;	
		n->frequency = 1;	
		n->left = NULL;		
		n->right = NULL;		
	}
	else if(strcmp(data,n->key) < 0)/*data is less than key, insert left*/
	{
		n->left = insertNode(n->left,data);
		if (height(n->left) - height(n->right) == 2)/*height is > 1, perform rotate*/
		{
			if(strcmp(data,n->left->key) < 0)/*data is less than key, rotate left*/
			{
				n = singleRotateLeft(n);
			}
			else
			{
				n = doubleRotateLeft(n);
			}
			
		}		
	}
	else if(strcmp(data,n->key) > 0)/*data is greater than key, insert right*/
	{
		n->right = insertNode(n->right,data);
		if (height(n->right) - height(n->left) == 2)/*height is < -1, perform rotate right*/
		{
			if(strcmp(data,n->right->key) > 0)/*data is greater than key, rotate right*/
			{
				n = singleRotateRight(n);
			}
			else
			{
				n = doubleRotateRight(n);
			}
		}
		
	}
	else/*key exists, increment the frequency*/
	{
		n->frequency++;
	} 

	n->height = (findMax(height(n->left),height(n->right)))+1;

	
	return n;
}

void freeTree(avlNode* n)
{
	if(n != NULL)
	{
		freeTree(n->left);
		freeTree(n->right);
		free(n->key);
		free(n);
	}
	
}


int findMax(int num1,int num2)
{
	if(num1 > num2){return num1;}
	else{return num2;}
}

/*rotate a node with it's right child*/
avlNode* singleRotateRight(avlNode *n)
{
	avlNode *temp = NULL;

	temp = n->right;
	n->right = temp->left;
	temp->left = n;

	/*restore the correct heights*/
	n->height = (findMax(height(n->left),height(n->right)))+1;

	temp->height = (findMax(height(temp->left),height(temp->right)))+1;

	return temp;	
}
/*rotate a node with it's left child*/
avlNode* singleRotateLeft(avlNode *n)
{
	avlNode *temp = NULL;

	temp = n->left;
	n->left = temp->right;
	temp->right = n;

	/*restore the correct heights*/
	n->height = (findMax(height(n->left),height(n->right)))+1;

	temp->height = (findMax(height(temp->left),height(temp->right)))+1;

	return temp;

}
avlNode* doubleRotateRight(avlNode *n)
{
	n = singleRotateLeft(n->right);
	return singleRotateRight(n);
}
avlNode* doubleRotateLeft(avlNode *n)
{
	n = singleRotateRight(n->left);
	return singleRotateLeft(n);
}
avlNode* find(avlNode* n, char *key)
{
	if(n == NULL){return NULL;}
	
	if(strcmp(key,n->key) < 0)/*data is less than key*/
	{
		return find(n->left,key);/*search the left child since its less than the key*/
	}
	else if(strcmp(key,n->key) > 0)/*data is greater than key*/
	{
		return find(n->right,key);/*search right child since data is greater than key*/
	}
	else
	{
		return n; /*return the matched node*/
	}
	return NULL;
}


int height(avlNode *n)
{
	if(n == NULL)
	{
		return -1;
	}
	else
	{
		return n->height;
	}
}


/*print the avl tree, just for debugging purposes*/
void printAvlTree(avlNode* n)
{
	if(n == NULL)
	{
		return;
	}
	printf("%s\n",n->key);

	if(n->left !=NULL){printf("(L:%s)",n->left->key);}
	if(n->right !=NULL){printf("(R:%s)",n->right->key);}
	printf("\n");
	printAvlTree(n->left);
	printAvlTree(n->right);
}



