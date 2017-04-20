/********************************************************
Gavin Chen ghchen 1492980
cs101 pa01
4/20/17
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"intVec.h"

//static const int intInitCap = 4;

static void error(const char message[]);

typedef struct IntVecNode{
	int *data;
	int sz;
	int capacity;
}IntVecNode;

int intTop(IntVec myVec){
	if (myVec)
	{
	int *penis = myVec->data;
	penis += myVec->sz;
	return *penis;
	}
	else error(__func__);
	
}

int intData(IntVec myVec, int i){
	if (myVec && i >= 0 && i < myVec->sz)
	{
	int *penis = myVec->data;
	penis += i;
	return *penis;
	}
	else error(__func__);
	
}

int intSize(IntVec myVec){
	if (myVec)
	{
		return myVec->sz;
	}
	else error(__func__);
	
}
int intCapacity(IntVec myVec){
	if (myVec)
	{
		return myVec->capacity;
	}
	else error(__func__);
	
}

IntVec intMakeEmptyVec(void){
	IntVec ass = (IntVec) calloc(1,sizeof(IntVecNode));
	if(ass){
		ass->capacity = intInitCap;
		
	ass->data = calloc(intInitCap, sizeof(int));
		return ass;
	}
	else error(__func__);	
}

void intVecPush(IntVec myVec, int newE){
	if(myVec){//if node exists
		if(myVec->sz == myVec->capacity){ //if no more space left in data array
			myVec->capacity *= 2; //double capacity
			myVec->data = realloc(myVec->data, myVec->capacity * sizeof(int));//reallocate memory for data
		}
		int *shit = myVec->data; //get address of data array
			shit += ++myVec->sz;//get to next open spot
			*shit = newE; //place data
	}
	else error(__func__);
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
