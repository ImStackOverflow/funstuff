#include "logic.h"


void updateFringePrimm(data poof, int v){
	int size = adjWgtSize(poof->vect[v]);
	double wgt;
	AdjWgt poop;
	for(int i = 0; i < size; i++){
		poop = adjWgtData(poof->vect[v], i);
		//v = current vertex
		//poop = adj vertex to v
		if(getStatus(poof->PQ, poop.to) == UNSEEN){
			//if the current adj vertex is unseen then add it into the queue
			insertPQ(poof->PQ, poop.to, poop.wgt ,v);
		}
		//otherwise the current adj vertex is already in the queue
		else if(poop.wgt < getPriority(poof->PQ, poop.to)){
			//if the new weight is lower then the previous weight for the adj vertex
			//then update its weight in the pq
			decreaseKey(poof->PQ, poop.to, wgt, v);
		}
	}
}



void algorithm(data poof, int start, Flag flag){
	if(!poof) error("uninitialized data", __func__);
	insertPQ(poof->PQ, start, 0, -1);//set the start node to weight 0 and parent -1
	int vertex;
	while(!isEmptyPQ(poof->PQ)){
		vertex = getMin(poof->PQ);
		delMin(poof->PQ);
		if (flag != Dyke) updateFringePrimm(poof, vertex);
		else error("havent done dykes yet", __func__);
	}
}
