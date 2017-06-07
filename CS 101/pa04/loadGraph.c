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
	if(!status || !priority || !parent) error("couldnt allocate memory", __func__);//error checking
	
	poopie = createPQ(nodes, status, priority, parent);//create array
	return poopie;
}


//create struct with actual data
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
	//error checking
	if(!ass) error("passed in uninitialized array", __func__);
	if(v1 > n || v2 > n) error("addVert the referenced vertex doesnt exist", __func__);

	//add v2 into v1
	AdjWgt booty;
	booty.to = v2;
	booty.wgt = weight;
	adjWgtVecPush(*(ass+v1), booty);
}


//parse input file and create adj array 
data parseFile(FILE *in, Flag flag){
	//data buffer varriables
	int v1, v2, args, n;
	double weight = 0;
	char what[2000], ass;
	
	
	data shit;//return varriable

	while(fgets(what, 2000, in) != NULL){
	args = sscanf(what, "%d %d %lf %c", &v1, &v2, &weight, &ass);//scan input file

	switch (args){
		case -1: //no input
			break;
			
		case 1://first line
		shit = create(v1);//create minPQ and adjV struct of size n
			break;
			
		case 3://2 verticies with weight
		addVert(shit->vect, v1, v2, weight, shit->n);
		if(flag == Prims){//make undirected for prims algorithim
			addVert(shit->vect, v2, v1, weight, shit->n);
		}
		shit->m++;//incriment edge counter
			break;
			
		default:
			error("the input file has formating errors fix it", __func__);
			break;
		
	}
	}
	fclose(in);//close input file
	return shit;
	
}
