/*
#NAME: Mike Sadowski
#DATE: November 22nd, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct avlNode
{
	int height;
	char* key;/*the entire string*/
	int frequency;/*the number of times that string was inserted*/
	struct avlNode *left;
	struct avlNode *right;
}avlNode;

/*IN avl_tree.c*/
avlNode* insertNode(avlNode *n, char *data);
avlNode* singleRotateRight(avlNode *n);
avlNode* singleRotateLeft(avlNode *n);
avlNode* doubleRotateRight(avlNode *n);
avlNode* doubleRotateLeft(avlNode *n);
avlNode* find(avlNode* n, char *key);

int height(avlNode *n);
void printAvlTree(avlNode* n);
int findMax(int num1,int num2);
void freeTree(avlNode* n);

/*IN a4_1.c*/
char printMenu(void);

avlNode* initialization(void);
avlNode* readFile(char *fileName,avlNode *tree);
void printHeightAndSize(avlNode* n, int *count);
void findNode(avlNode* tree);
avlNode* insertNodeToTree(avlNode* tree);
avlNode* removeNode(avlNode* tree);
void aboveAFrequency(avlNode *n, int freq);
