#include "minPQ.h"
#include "utilities.h"
#include "math.h"
#include <stdlib.h>


struct MinPQNode{
int numVerticies;
int numPQ;
int minVertex;
float infinity;
int* status;
int* parent;
double* fringeWgt;
};

//returns 1 (true) if empty 0 otherwise
int isEmptyPQ(MinPQ pq){
	if(!pq) error("uninitialized priority queue", __func__);
	if(pq->numPQ == 0) return 1;
	else return 0;
}

void findMin(MinPQ pq){
	float weight;
	weight = pq->infinity;
	for(int vertex = 1; vertex <= pq->numVerticies; vertex++){//go through all verticies
		if(pq->status[vertex] == FRINGE){//if is a fringe verticie
			if(pq->fringeWgt[vertex] <= weight){//if found new min vertex
				pq->minVertex = vertex;//set new minimum vertex
				weight = pq->fringeWgt[vertex];//update weight
			}
		}
	}
}


//either find new min vertex or return previously calculated one
int getMin(MinPQ pq){
	if(!pq) error ("uninitialized priority queue", __func__);
	if(pq->minVertex == -1)	findMin(pq);//find min only if current min vertex is reset
	return pq->minVertex;//otherwise return current min vertex
}

//get tree status of node
int getStatus(MinPQ pq, int id){
	//error checking
	if(!pq) error("uninitialized priority queue", __func__);
	if(id > pq->numVerticies || id <= 0) error("passed in out of bounds vertex", __func__);
	return pq->status[id];
}

//get parent of node
int getParent(MinPQ pq, int id){
	//error checking
	if(!pq) error("uninitialized priority queue", __func__);
	if(id > pq->numVerticies || id <= 0) error("passed in out of bounds vertex", __func__);
	return pq->parent[id];
}


//get fringe weight of node
double getPriority(MinPQ pq, int id){
	//error checking
	if(!pq) error("uninitialized priority queue", __func__);
	if(id > pq->numVerticies || id <= 0) error("passed in out of bounds vertex", __func__);
	return pq->fringeWgt[id];
}


void delMin(MinPQ pq){
	//error checking
	if(!pq) error("uninitialized priority queue", __func__);
	int minV = getMin(pq);
	if(minV != -1){
		pq->status[minV] = INTREE;//set min to in tree
		pq->minVertex = -1;//reset min vertex
		pq->numPQ--;//decrease queue
	}
}

void insertPQ(MinPQ pq, int id, double priority, int par){
	//error checking
	if(!pq) error("uninitialized priority queue", __func__);
	if(id > pq->numVerticies || id <= 0)error("passed in out of bounds vertex", __func__);
	
	//set data
	pq->parent[id] = par;//change parent
	pq->fringeWgt[id] = priority;//set fringe weight
	pq->status[id] = FRINGE; //change status to fringe
	pq->minVertex = -1;//reset min vertex
	pq->numPQ++;//incriment queue counter
}

void decreaseKey(MinPQ pq, int id, double priority, int par){
	//error checking
	if(!pq) error("uninitialized priority queue", __func__);
	if(id > pq->numVerticies || id <= 0)error("passed in out of bounds vertex", __func__);
	
	
	pq->parent[id] = par;//set new parent
	pq->fringeWgt[id] = priority;//set new fringe wgt
	pq->minVertex = -1;//reset min vertex
}

MinPQ createPQ(int n, int status[], double priority[], int parent[]){
	MinPQ newNode = malloc(sizeof(struct MinPQNode));
	if(!newNode){
		//error checking
		error("couldnt allocate memory", __func__);
	}
	
	//populate struct
	newNode->numVerticies = n;//set number of verticies
	newNode->numPQ = 0; //initialze queue to empty
	newNode->minVertex = -1;//reset min vertex
	newNode->infinity = INFINITY;//hold infinity value
	newNode->status = status;//set status array to passed allocated array
	for(int i = 0; i <= n; i++){
		//reset status array to unseen
		newNode->status[i] = UNSEEN;
	}
	newNode->parent = parent;//set parent array to new parent array
	newNode->fringeWgt = priority;//set fringe array to passed array
	return newNode;
}















