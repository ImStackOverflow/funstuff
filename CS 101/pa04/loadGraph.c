#include "loadGraph.h"
#include "utilities.h"

AdjWgtVec *create(int nodes){
	IntVec *clit = (AdjWgtVec*) calloc(nodes+1, sizeof(AdjWgtVec));//allocate pointers to pointers
	if(!clit) error("couldn't allocate memory", __func__);
	for(int i = 1; i <= nodes; i++){
		clit[i] =  adjWgtMakeEmptyVec(); //make empty vector list
	}
	return clit;
}


void addVert(AdjWgtVec *ass, int v1, int v2, int weight, int n){
	if(!ass) error("passed in uninitialized array", __func__);
	if(v1 > n || v2 > n) error("addVert the referenced vertex doesnt exist", __func__);
		AdjWgt booty;
		booty.to = v2;
		booty.wgt = weight;
		adjWgtVecPush(*ass[v1], booty);
	}
}


AdjWgtVec* parseFile(FILE *in, Flag flag){
	nt v1, v2, args, n, m = 0;
	double weight = 0;
	char what[2000], ass;
	AdjWgtVec *shit;

	while(fgets(what, 2000, in) != NULL){
	args = sscanf(what, "%d %d %lf %c", &v1, &v2, &weight, &ass);

	switch (args){
		case -1: //no input
			break;
			
		case 1://first line
		n = v1;
		shit = create(v1);
			break;
			
		case 3://2 verticies with weight
		addVert(shit, v1, v2, weight, n);
		if(flag == Prims){
			addVert(shit, v2, v1, weight, n);
		}
		m++;
			break;
			
		default:
			error("the input file has formating errors fix it", __func__);
			break;
		
	}
	}
	fclose(in);
	procede(shit, m, n);//print all the shit out and stuff
	
}
