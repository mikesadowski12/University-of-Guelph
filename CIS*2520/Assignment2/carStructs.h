/*
#NAME: Mike Sadowski
#DATE: October 14th, 2014
#STUDENT ID: 0864810
#ASSIGNEMNT: Data Structures Assignment 2
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MILEAGESORT 600
#define RETURNDATESORT    601
#define MAXSIZE 9999
#define STACKSIZE 15

typedef struct CarStructure
{
	int mileage;
	int returnDate;
	char* plateNumber;
	double charge;

	struct CarStructure *next;
}CarStructure;

/* IN CARSTRUCTURE.C */
CarStructure *createCarStructureNode(int newMileage,int returnDate, double charge, char* newPlateNumber);
CarStructure *addNodeToList(CarStructure *Head, CarStructure *newBlock, int sortCode);
void printList(CarStructure *Head);
CarStructure* delete_node(CarStructure** Head, char* plateNumber);
CarStructure* update_node_returnDate(CarStructure* theNode, int returnDate);
CarStructure* update_node_mileage(CarStructure* theNode, int mileage);
CarStructure* update_node_charge(CarStructure* theNode, double charge);
void saveList(CarStructure *Head, char* fileName);
CarStructure* LoadList(CarStructure *Head, char* fileName, int sortCode);


/* IN Q1.C */
char printMenu(void);
CarStructure* addNewCarToAvailableForRentList(CarStructure* availableHead);
void rentFirstAvailableCar(CarStructure** availableHead, CarStructure** rentedHead);
double calculateCharge(double prevMiles, double newMiles);
void returnCar(CarStructure** ToList, CarStructure** FromList, int printMessageCode);
void putCarInRepair(CarStructure** availableHead, CarStructure** rentedHead);
void putRepairedCarIntoAvailable(CarStructure** availableHead, CarStructure** repairHead);
double calculateTotalCharge(CarStructure* Head);

