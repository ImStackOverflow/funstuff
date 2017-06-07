#include "loadGraph.h"


//create adjVector array
AdjWgtVec *vectorz(int nodes){
	AdjWgtVec *clit = (AdjWgtVec*) calloc(nodes+1, sizeof(AdjWgtVec));//allocate pointers to pointers
	if(!clit) error("couldn't allocate memory", __func__);
	for(int i = 1; i <= nodes; i++){
		clit[i] =  adjWgtMakeEmptyVec(); //make empty vector list
	}
	return clit;
}


//create minPQ
MinPQ queue(int nodes){
	MinPQ poopie = (MinPQ) malloc(sizeof(MinPQ));//allocate minPQ
	if (!poopie) error("couldnt allocate memory", __func__);
	
	//allocate data arrays
	int *status = (int*)calloc(nodes+1,sizeof(int));
	double *priority = (double*)calloc(nodes+1,sizeof(double));
	int *parent = (int*)calloc(nodes+1,sizeof(int));
	if(!status || !priority || !parent) error("couldnt allocate memory", __func__);
	
	poopie = createPQ(nodes, status, priority, parent);
	return poopie;
}


//create struct
data create(int nodes){//create data pointer
	data butt = (data) malloc(sizeof(graph));
	if (!butt) error("couldnt allocate memory", __func__);
	butt->vect = vectorz(nodes);//populate adj vecotr array
	butt->PQ = queue(nodes);//populate minPQ 
	butt->n = nodes;//set n
	butt->m = 0; //inintialize m
	return butt;
}


//addvertex to adj array
void addVert(AdjWgtVec *ass, int v1, int v2, double weight, int n){
	if(!ass) error("passed in uninitialized array", __func__);
	if(v1 > n || v2 > n) error("addVert the referenced vertex doesnt exist", __func__);
		AdjWgt booty;
		booty.to = v2;
		booty.wgt = weight;
		adjWgtVecPush(*(ass+v1), booty);
}



data parseFile(FILE *in, Flag flag){
	int v1, v2, args, n;
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
		addVert(shit->vect, v1, v2, weight, shit->n);
		if(flag == Prims){//make undirected
			addVert(shit->vect, v2, v1, weight, shit->n);
		}
		shit->m++;
			break;
			
		default:
			error("the input file has formating errors fix it", __func__);
			break;
		
	}
	}
	fclose(in);
	return shit;
	
}
