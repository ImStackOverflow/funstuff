#include "loadGraph.h"

AdjWgtVec *vectorz(int nodes){
	AdjWgtVec *clit = (AdjWgtVec*) calloc(nodes+1, sizeof(AdjWgtVec));//allocate pointers to pointers
	if(!clit) error("couldn't allocate memory", __func__);
	for(int i = 1; i <= nodes; i++){
		clit[i] =  adjWgtMakeEmptyVec(); //make empty vector list
	}
	return clit;
}

MinPQ queue(int nodes){
	MinPQ poopie = (MinPQ) malloc(sizeof(MinPQ));
	if (!poopie) error("couldnt allocate memory", __func__);
	int *status = (int*)calloc(n,sizeof(int))
	double *priority = (double*)calloc(n,sizeof(double))
	int *parent = (int*)calloc(n,sizeof(int))
	if(!status || !priority || !parent) error("couldnt allocate memory", __func__);
	poopie = createPQ(nodes, status, priority, parent);
	return poopie;
}
data create(int nodes){
	data butt = (data) malloc(sizeof(graph));
	if (!butt) error("couldnt allocate memory", __func__);
	butt->vect = vectorz(nodes);
	butt->PQ = queue(nodes);
	butt->n = nodes;
	return butt;
}
void addAdj(AdjWgtVec *ass, int v1, int v2, double weight, int n){
	if(!ass) error("passed in uninitialized array", __func__);
	if(v1 > n || v2 > n) error("addVert the referenced vertex doesnt exist", __func__);
		AdjWgt booty;
		booty.to = v2;
		booty.wgt = weight;
		adjWgtVecPush(*(ass+v1), booty);
}

void addVert(data butt, int v1, int v2, double wgt){
	addAdj(butt->vect, v1, v2, wgt);//add vertex to adj vector
	insertPQ


data parseFile(FILE *in, Flag flag){
	int v1, v2, args, n, m = 0;
	double weight = 0;
	char what[2000], ass;
	data shit;

	while(fgets(what, 2000, in) != NULL){
	args = sscanf(what, "%d %d %lf %c", &v1, &v2, &weight, &ass);

	switch (args){
		case -1: //no input
			break;
			
		case 1://first line
		shit = create(v1);//create minPQ and adjV struct
			break;
			
		case 3://2 verticies with weight
		addVert(shit, v1, v2, weight);
		if(flag == Prims){//make undirected
			addVert(shit, v2, v1, weight);
		}
		m++;
			break;
			
		default:
			error("the input file has formating errors fix it", __func__);
			break;
		
	}
	}
	fclose(in);
	return shit;
	
}
