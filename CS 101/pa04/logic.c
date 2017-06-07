#include "logic.h"


void updateFringe(data poof, int v){
	int size =  adjWgtSize(poof->vect[v]);
	double wgt;
	AdjWgt poop;
	for(int i = 0; i < size; i++){
		poop = adjWgtData(poof->vect[v], i);
	
}
