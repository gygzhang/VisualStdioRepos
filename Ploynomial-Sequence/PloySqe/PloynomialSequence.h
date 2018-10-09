#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define INIT_SIZE 100
#define OVERFLOW 2
#define OK 3
#define EMPTY_ITEM 
#define INCREMENT 20

struct item {
	double coefficient;
	double exponent;
};

typedef struct item Item;

typedef struct {
	Item *item;
	int length;
	int size;
}SqeList;
//Initialize the list 
int InitializeSqeList(SqeList* plist);

//Insert a item into list with a item
int InsertList(SqeList *list, Item item);

//Insert a item into list with coefficient and exponent
int InsertList(SqeList *plist, double coefficient, double exponent);

//Just print list with sign
void PrintList(SqeList list);

//Sort the list with ascending order
SqeList SortList(SqeList *plist);

//Find the minimun value and return it,remove it from the list
Item GetMinAndChop(SqeList *plist);

//Get the length of the list
int GetLength(SqeList list);

//Delete the item which index is the parameter index from the list
Item Remove(SqeList *plist, int index);

//Generate a empty item which coefficient and exponent both are zero
Item GenerateEmptyItem();

//Get rid of the repetitive data and empty item
void DistinguishList(SqeList* list);

//Return true if list is empty,or false 
bool ListIsEmpty(SqeList list);

//Return true if the item's coefficient is zero
bool ItemIsEmpty(Item item);

//Concatenate list b with list a ,and store the connective list in list a
void ConcatenateList(SqeList *pla, SqeList lb);

//Get rid of the empty item
void StripEmptyItem(SqeList *plist);

//Change the item's coefficient into opposite sign in the list
void ReverseSign(SqeList *plist);

//Calculate the result of a single item multiply a list,and return it
SqeList SingleItemMultiplyList(Item item, SqeList list);

//Implements the method that calculate list multiply list ,and store the result in list a
void ImplementsMultiplicationWithPMethod(SqeList *pla, SqeList lb, SqeList(*p)(Item, SqeList));

//Copy data in list lb to list* pla
void CopyList(SqeList *pla, SqeList lb);

//Implement of ploynomial addtion
void ExecuteAdd(SqeList *pla, SqeList lb);

//Implement of ploynomial substraction
void ExecuteSub(SqeList *pla, SqeList lb);

//Implement of ploynomial multiplication
void ExecuteMul(SqeList *pla, SqeList lb);

void CreatList(SqeList* plist);

void GetMenu();

void SelectMethod(SqeList *la, SqeList lb);

void yes(SqeList *plist);
void no(SqeList *plist);