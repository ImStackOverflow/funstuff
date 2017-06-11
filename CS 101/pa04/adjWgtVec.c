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
	//error checking
	if(!myVec) error("null pointer", __func__);
	
	AdjWgt balls;//create instance and populate
	balls.to = myVec->data[myVec->sz];
	balls.wgt = myVec->wgt[myVec->sz];
	return balls;
}

AdjWgt adjWgtData(AdjWgtVec myVec, int i){
	//error checking
	if(!myVec) error("null pointer", __func__);
	
	//create instance and populate
	AdjWgt balls;
	balls.to = myVec->data[i];
	balls.wgt = myVec->wgt[i];
	return balls;
}

int adjWgtSize(AdjWgtVec myVec){
	//error checking
	if(!myVec) error("null pointer", __func__);
	//return field
	return myVec->sz;
}

int adjWgtCapacity(AdjWgtVec myVec){
	//error checking
	if(!myVec) error("null pointer", __func__);
	//return field
	return myVec->capacity;
}

AdjWgtVec adjWgtMakeEmptyVec(void){
	//allocate memory
	AdjWgtVec ass = (AdjWgtVec) calloc(1,sizeof(AdjWgtVecNode));
	//error checking
	if (!ass)  error("null pointer", __func__);
	
	//populate
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
	myVec->data[myVec->sz] = newE.to;//set vertex
	myVec->wgt[myVec->sz++] = newE.wgt;//set weight
}

void adjWgtVecPop(AdjWgtVec myVec){
	if(!myVec) error("null pointer in", __func__);
	if (myVec->sz > 0) myVec->sz--;//remove size by one
}









