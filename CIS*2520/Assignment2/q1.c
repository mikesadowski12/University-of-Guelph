/*
#NAME: Mike Sadowski
#DATE: October 14th, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 2
*/

#include "carStructs.h"

int main()
{
	char userInput = '0';
	CarStructure* availableListHead = NULL;
	CarStructure* rentedListHead = NULL;
	CarStructure* repairListHead = NULL;
	double finalCharge = 0.00;
	
	/*Load all the lists from the text files*/
	availableListHead = LoadList(availableListHead, "available.txt", MILEAGESORT);
	rentedListHead = LoadList(rentedListHead, "rented.txt", RETURNDATESORT);
	repairListHead = LoadList(repairListHead, "repair.txt", MILEAGESORT);

	/*handle menu cases*/
	while(userInput != '7')
	{
		userInput = printMenu();/*menu loops until user chooses to exit*/
		switch(userInput)
		{
			case '1':
				availableListHead = addNewCarToAvailableForRentList(availableListHead);
				getchar();
				getchar();
				break;
			case '2':
				returnCar(&availableListHead, &rentedListHead, 0); 
				getchar();
				getchar();
				break;
			case '3':
				putCarInRepair(&rentedListHead, &repairListHead);
				getchar();	
				getchar();
				break;
			case '4':
				putRepairedCarIntoAvailable(&availableListHead, &repairListHead);	
				getchar();
				getchar();
				break;
			case '5':
				rentFirstAvailableCar(&availableListHead, &rentedListHead);
				getchar();
				getchar();
				break;
			case '6':
				printf("\nAVAILABLE LIST");
				printList(availableListHead);
				printf("\nRENTED LIST");
				printList(rentedListHead);
				printf("\nIN REPAIR LIST");
				printList(repairListHead);
				break;
			case '7':
				finalCharge += calculateTotalCharge(availableListHead);
				finalCharge += calculateTotalCharge(rentedListHead);
				finalCharge += calculateTotalCharge(repairListHead);
				printf("\n\n>>> The final charge for all cars is: %0.2lf\n", finalCharge);
				getchar();
				break;
		}
	}
	saveList(availableListHead, "available.txt");
	saveList(rentedListHead, "rented.txt");
	saveList(repairListHead, "repair.txt");
	getchar();
	return 1;
}

/*Print the menu and return the user's choice*/
char printMenu(void)
{
	system("clear");
	printf("1.Add a new car to the available-for-rent list\n");
	printf("2.Add a returned car to the available-for-rent list\n");
	printf("3.Add a returned car to the repair list\n");
	printf("4.Transfer a car from the repair list to the available-for-Rent list\n");
	printf("5.Rent first avaiable car\n");
	printf("6.Print all the lists\n");
	printf("7.Quit\n");
	printf(">>>>Choice: ");
	return (getchar());
}

/* MENU OPTION 1
Get user input for adding a new car to the available for rent linked list, and add new node to the list
*/
CarStructure* addNewCarToAvailableForRentList(CarStructure* availableHead)
{
	int mileage = 0;
	char plateNumber[100];

	printf("Please enter the mileage: ");
	scanf("%d", &mileage);
	getchar();/*clear keyboard buffer*/
	printf("Please enter the plate-number: ");
	scanf("%s", plateNumber);
	getchar();/*clear keyboard buffer*/
	
	/*create the node and add it to the list*/
	availableHead = addNodeToList(availableHead, createCarStructureNode(mileage,0,0.00, plateNumber), MILEAGESORT);
	printf("\n>>>New car has been added to the available list!\n");

	return availableHead;
}
/* MENU OPTION 2
Return a rented car back into the available to rent list
*/
void returnCar(CarStructure** ToList, CarStructure** FromList, int printMessageCode)
{
	char plateNumber[100];
	int mileage = 0;
	double charge = 0;
	CarStructure* pNode = NULL;

	printf("Please enter the plate number: ");
	scanf("%s", plateNumber);
	printf("Please enter the new mileage: ");
	scanf("%d", &mileage);

	pNode = delete_node(FromList, plateNumber);
	if(pNode == NULL)
	{
		printf(">>>> Car was not found\n");
		return;
	}
	charge = calculateCharge(pNode->mileage, mileage);/*calculate the new charge based on the miles put on the car*/
	
	/*update all the car information*/
	pNode = update_node_returnDate(pNode, 0);
	pNode = update_node_charge(pNode, charge);
	pNode = update_node_mileage(pNode, mileage);
		
	*ToList = addNodeToList(*ToList, pNode, MILEAGESORT);

	/*since function returns for 2 different lists, 2 different print messages are needed*/
	if(printMessageCode == 0)
	{
		printf("\n>>>Returned car has been added to the available list!\n");
	}
	else
	{
		printf("\n>>>Returned car has been added to the repair list!\n");
	}

}
/* MENU OPTION 3
Put a rented car into the repair list
*/
void putCarInRepair(CarStructure** rentedHead, CarStructure** repairHead)
{
	returnCar(repairHead, rentedHead, 1);/*send 1 to print the repair list message*/
						
}
/* MENU OPTION 4
Put a repaired car into the available list
*/
void putRepairedCarIntoAvailable(CarStructure** availableHead, CarStructure** repairHead)
{
	char plateNumber[100];
	CarStructure* pNode = NULL;

	printf("Please enter the plate number: ");
	scanf("%s", plateNumber);

	pNode = delete_node(repairHead, plateNumber);
	if(pNode == NULL)
	{
		printf(">>>> Car was not found\n");
		return;
	}
	
	*availableHead = addNodeToList(*availableHead, pNode, MILEAGESORT);
	printf("\n>>>Repaired car has been added to the available list!\n");

}

/* MENU OPTION 5
Rent the car that's the first position in the Available list, add it to the rented list
*/
void rentFirstAvailableCar(CarStructure** availableHead, CarStructure** rentedHead)
{
	int returnDate = 0;
	CarStructure* pNode = NULL;

	printf("Please enter the return date (integer: YYYYMMDD): ");
	scanf("%d", &returnDate);

	pNode = delete_node(availableHead, (*availableHead)->plateNumber);
	if(pNode == NULL)
	{
		printf(">>>> Car was not found\n");
		return;
	}	
	pNode = update_node_returnDate(pNode, returnDate);
	*rentedHead = addNodeToList(*rentedHead, pNode, RETURNDATESORT);
	printf("\n>>>First available car has been added to the rented list!\n"); 

}

/*calculate the charge, 40$ for first 100km, .15cents for every additional km*/
double calculateCharge(double prevMiles, double newMiles)
{
	double milesOver = newMiles - prevMiles;	

	if(milesOver <= 100.0)
	{
		return 40.0;
	}
	else
	{
		return (40.0 + ((milesOver-100.0)*0.15));
	}

	return 0;
}

/*calculate the total charge from a list*/
double calculateTotalCharge(CarStructure* Head)
{
	CarStructure *current = Head;
	double charge = 0.00;

	/*Check if list is empty*/
	if (current != NULL)
	{
		do
		{	
			charge += current->charge;
			current = current->next;
		}while(current != NULL);/*keep going until end of list*/
	}	
	return charge;
}
