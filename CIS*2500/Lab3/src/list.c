#include "list.h"

struct Student *addToFront(struct Student *oldHead, struct Student *newElement)
{
	newElement->next = oldHead;
	
	return newElement;
	
}
