#include "adjWgtVec.h"
#include "utilities.h"
#include <stdlib.h>


typedef struct AdjWgtVecNode{
	int *data;
	int sz;//size always 1 greater than number of numbers (b/c of array manipulation shit)
	int capacity;
	double *wgt; //array of weights to each vertex
}AdjWgtVecNode;

AdjWgt adjWgtTop(AdjWgtVec myVec){
	if(!myVec) error("null pointer", __func__);
	AdjWgt balls;
	balls.to = myVec->data[myVec->sz];
	balls.wgt = myVec->wgt[myVec->sz];
	return balls;
}

AdjWgt adjWgtData(AdjWgtVec myVec, int i){
	if(!myVec) error("null pointer", __func__);
	AdjWgt balls;
	balls.to = myVec->data[i];
	balls.wgt = myVec->wgt[i];
	return balls;
}

int adjWgtSize(AdjWgtVec myVec){
	if(!myVec) error("null pointer", __func__);
	return myVec->sz;
}

int adjWgtCapacity(AdjWgtVec myVec){
	if(!myVec) error("null pointer", __func__);
	return myVec->capacity;
}

AdjWgtVec adjWgtMakeEmptyVec(void){
	AdjWgtVec ass = (AdjWgtVec) calloc(1,sizeof(AdjWgtVecNode));
	if (!ass)  error("null pointer", __func__);
	ass->capacity = adjWgtInitCap;
	ass->sz = 0;
	ass->data = calloc(ass->capacity, sizeof(int));
	ass->wgt = calloc(ass->capacity, sizeof(double));
	return ass;
}

void adjWgtVecPush(AdjWgtVec myVec, AdjWgt newE){
	if(!myVec) error("null pointer in", __func__);
	if(myVec->sz == myVec->capacity){ //if no more space left in data array
			myVec->capacity *= 2; //double capacity
			myVec->data = realloc(myVec->data, myVec->capacity * sizeof(int));//reallocate memory for data
			myVec->wgt = realloc(myVec->wgt, myVec->capacity * sizeof(double));//memory for wgt
		}
	myVec->data[myVec->sz] = newE.to;
	myVec->wgt[myVec->sz++] = newE.wgt;
}

void adjWgtVecPop(AdjWgtVec myVec){
	if(!myVec) error("null pointer in", __func__);
	if (myVec->sz > 0) myVec->sz--;//remove size by one
}









