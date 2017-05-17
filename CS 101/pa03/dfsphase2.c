#ifndef penisbitch
#define penisbitch
#include "dfstrace1.h"
#include "intVec.h"

void DFSPhase2(Graph G, IntVec stack){
	int time = 0;
	makeWhite(G);//set all nodes to white
	int pein, dick = intSize(stack);
	for(int i = 0; i < dick; i++){
		intVecPop(stack);
		pein = intTop(stack);
		if (G->info[pein][0] == WHITE){ //if node is white (undiscovered)
		time = DFStrace(G, pein+1, time);
		}
	}
}
