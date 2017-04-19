#include <stdlib.h>
#include"intVec.h"

//static const int intInitCap = 4;

typedef struct IntVecNode * IntVec{
	int *data;
	int sz;
	int capacity;
};

int intTop(IntVec myVec){
	if (myVec)
	{
		int *penis = myVec->data;
	penis += myVec->sz;
	return *penis;
	}
	else error("there was a null pointer in intTop");
	
}

int intData(IntVec myVec, int i){
	if (myVec)
	{
			int *penis = myVec->data;
	penis += i;
	return *penis;
	}
	else error("there was a null pointer in intData");

}

int intSize(IntVec myVec){
	if (myVec)
	{
		return *myVec->sz;
	}
	else error("there was a null pointer in intSize");
	
}
int intCapacity(IntVec myVec){
	if (myVec)
	{
		return *myVec->capacity;
	}
	else error("there was a null pointer in intCapacity");
	
}

IntVec intMakeEmptyVec(void){
	if(IntVec ass = calloc(1,sizeof(IntVecNode))){
		ass->capacity = intInitCap;
	if (ass->data = calloc(intInitCap, sizeof(int))){
		return ass;
	}
	}
	else error("couldnt allocate memory for new vector");	
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
	else error("there was a null pointer in intVecPush");
}

void intVecPop(IntVec myVec){
	if(myVec){//if node exists
		return *(myVec->data + myVec->sz--);//return topmost data
	}
	else error("there was a null pointer in intVecPop");
}

void error(string n){
	printf("%s\n",n);
	exit(1);
}