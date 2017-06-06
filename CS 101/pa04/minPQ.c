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
			if(pq->fringeWgt[vertex] < weight){//if found new min vertex
				pq->minVertex = vertex;//set new minimum vertex
				weight = pq->fringeWgt[vertex];//update weight
			}
		}
	}
}

int getMin(MinPQ pq){
	if(!pq) error ("uninitialized priority queue", __func__);
	if(pq->minVertex == -1)	findMin(pq);
	return pq->minVertex;
}

int getStatus(MinPQ pq, int id){
	if(!pq) error("uninitialized priority queue", __func__);
	if(id >= pq->numVerticies || id < 0) error("passed in out of bounds vertex", __func__);
	return pq->status[id];
}

int getParent(MinPQ pq, int id){
	if(!pq) error("uninitialized priority queue", __func__);
	if(id >= pq->numVerticies || id < 0) error("passed in out of bounds vertex", __func__);
	return pq->parent[id];
}

double getPriority(MinPQ pq, int id){
	if(!pq) error("uninitialized priority queue", __func__);
	if(id >= pq->numVerticies || id < 0) error("passed in out of bounds vertex", __func__);
	return pq->parent[id];
}


void delMin(MinPQ pq){
	if(!pq) error("uninitialized priority queue", __func__);
	int minV = getMin(pq);
	if(minV != -1){
		pq->status[minV] = INTREE;//set min to in tree
		pq->minVertex = -1;//reset min vertex
		pq->numPQ--;//decrease queue
	}
}

void insertPQ(MinPQ pq, int id, double priority, int par){
	if(!pq) error("uninitialized priority queue", __func__);
	if(id >= pq->numVerticies || id < 0)error("passed in out of bounds vertex", __func__);
	
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->status[id] = FRINGE;
	pq->minVertex = -1;
	pq->numPQ++;
}

void decreaseKey(MinPQ pq, int id, double priority, int par){
	if(!pq) error("uninitialized priority queue", __func__);
	if(id >= pq->numVerticies || id < 0)error("passed in out of bounds vertex", __func__);
	pq->parent[id] = par;//set new parent
	pq->fringeWgt[id] = priority;//set new fringe wgt
	pq->minVertex = -1;//reset min vertex
}

MinPQ createPQ(int n, int status[], double priority[], int parent[]){
	MinPQ newNode = malloc(sizeof(struct MinPQNode));
	if(!newNode){
		error("couldnt allocate memory", __func__);
	}
	newNode->numVerticies = n;
	newNode->numPQ = 0;
	newNode->minVertex = -1;
	newNode->infinity = -INFINITY;
	newNode->status = status;
	newNode->parent = parent;
	newNode->fringeWgt = priority;
	return newNode;
}















