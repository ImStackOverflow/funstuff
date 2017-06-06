/********************************************************
Gavin Chen ghchen 1492980
cs101 pa01
4/20/17
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "intVec.h"

//static const int intInitCap = 2;

static void error(const char message[]);

typedef struct IntVecNode{
	int *data;
	int sz;//size always 1 greater than number of numbers (b/c of array manipulation shit)
	int capacity;
}IntVecNode;

int intTop(IntVec myVec){
	if (!myVec)
	{
		error(__func__);
	}
	int *penis = myVec->data;
	penis += myVec->sz;
	return *penis;
	
}

int intData(IntVec myVec, int i){
	if (!(myVec && i >= 0 && i < myVec->sz))
	{
		error(__func__);
	}
	int *penis = myVec->data;
	penis += i;
	return *penis;
}

int intSize(IntVec myVec){
	if (!myVec)
	{
		error(__func__);
		
	}
	return myVec->sz;
}
int intCapacity(IntVec myVec){
	if (myVec)
	{
		error(__func__);
	}
	return myVec->capacity;
}

IntVec intMakeEmptyVec(void){
	IntVec ass = (IntVec) calloc(1,sizeof(IntVecNode));
	if(!ass){
		error(__func__);	
	}
	ass->capacity = intInitCap;
	ass->sz = 0;
	ass->data = calloc(intInitCap, sizeof(int));
	return ass;
}

IntVec intMakeEmptyVecN(int np1){
	IntVec ass = (IntVec) calloc(1,sizeof(IntVecNode));
	if(!ass){
		error(__func__);	
	}
	ass->capacity = np1;
	ass->sz = 0;
	ass->data = calloc(np1, sizeof(int));
	return ass;
}

void intVecPush(IntVec myVec, int newE){
	if(!myVec){//if node doesnt exist
		error(__func__);
	}
	if(myVec->sz == myVec->capacity){ //if no more space left in data array
			myVec->capacity *= 2; //double capacity
			myVec->data = realloc(myVec->data, myVec->capacity * sizeof(int));//reallocate memory for data
		}

	myVec->data[myVec->sz++] = newE;	
}

void intVecPop(IntVec myVec){
	if(myVec){//if node exists
	if (myVec->sz > 0){
		myVec->sz--;//remove size by one
	}
	}
	else error(__func__);
}

static void error(const char message[]){
	printf("there was an error in %s\n", message);
	exit(1);
}
