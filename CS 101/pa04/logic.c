#include "logic.h"


void updateFringePrimm(data poof, int v){
	int size = adjWgtSize(poof->vect[v]);
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
		else if(getStatus(poof->PQ, poop.to) == FRINGE){
			if(poop.wgt < getPriority(poof->PQ, poop.to)){
			//if the new weight is lower then the previous weight for the adj vertex
			//then update its weight in the pq
				decreaseKey(poof->PQ, poop.to, poop.wgt, v);
			}
		}
	}
}


void updateFringeDyke(data poof, int v){
	int size = adjWgtSize(poof->vect[v]);
	AdjWgt poop;
	float wgt = getPriority(poof->PQ, v);
	for(int i = 0; i < size; i++){
		poop = adjWgtData(poof->vect[v], i);
		//finge weight is cumulitive
		//v = current vertex
		//poop = adj vertex to v
		if(getStatus(poof->PQ, poop.to) == UNSEEN){
			//if the current adj vertex is unseen then add it into the queue
			insertPQ(poof->PQ, poop.to, wgt + poop.wgt,v);
		}
		//otherwise the current adj vertex is already in the queue
		else if(getStatus(poof->PQ, poop.to) == FRINGE){
			if(wgt + poop.wgt < getPriority(poof->PQ, poop.to)){
			//if the new weight is lower then the previous weight for the adj vertex
			//then update its weight in the pq
				decreaseKey(poof->PQ, poop.to, wgt + poop.wgt, v);
			}
		}
	}
}




void algorithm(data poof, int start, Flag flag){
	if(!poof) error("uninitialized data", __func__);
	insertPQ(poof->PQ, start, 0.0, -1);//set the start node to weight 0 and parent -1
	int vertex;
	while(!isEmptyPQ(poof->PQ)){
		vertex = getMin(poof->PQ);//get the minimum vertex added into tree
		delMin(poof->PQ);
		
		//update fringe based on input flag
		if (flag != Dyke) updateFringePrimm(poof, vertex);
		else updateFringeDyke(poof, vertex);
	}
}
