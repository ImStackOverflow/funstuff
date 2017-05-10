/********************************************************
Gavin Chen ghchen 1492980
cs101 pa01
4/20/17
*********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loadGraph.h"

//#define DEBUG 1

#ifdef DEBUG
#define DPRINT(x) printf x
#else
#define DPRINT(x) do{} while(0)
#endif


typedef enum {U, none} Flag;


void procede(IntVec* shit, int m, int n){

	printShit(shit, m, n);
	//DPRINT(("penis"));
	int** adjMatrix = makeAdjMatrix(shit, n);
	printf("\nadjacency matrix of origional list:\n\n");
	printAdjMatrix(adjMatrix, n);
	for(int i = 0; i < 2; i++){
		shit = transposeGraph(shit, n);
		printf("\n\n%d transposed adjacency matrix:\n\n",i+1);
		printShit(shit, m, n);
		if(n <= 20){
			adjMatrix = makeAdjMatrix(shit, n);
			printAdjMatrix(adjMatrix, n);
		}
		else printf("more than 20 verticies, too long so I decided not to do print the matrix\n %d\n",n);
	}
	
	freeAll(shit, n);

}


void doShit(FILE *in, Flag flag){// parse file and create origional intVec array
int v1, v2, args, n, m = 0;
double weight = 0;
char what[2000], ass;
	IntVec *shit;

	while(fgets(what, 2000, in) != NULL){
	args = sscanf(what, "%d %d %lf %c", &v1, &v2, &weight, &ass);

	switch (args){
		case -1: //no input
			break;
		case 1://first line
		n = v1;
		shit = create(v1);
			break;
		case 2://2 vertecies
		addVert(shit, v1, v2, 0, n);
		//printShit(shit, m, n);
		if(flag == U){
			DPRINT(("doing bidirectional edge"));
			addVert(shit, v2, v1, 0, n);
		}
		m++;
			break;
		case 3://2 verticies with weight
		addVert(shit, v1, v2, weight, n);
		if(flag == U){
			addVert(shit, v2, v1, weight, n);
		}
		m++;
			break;
		default:
			error("the input file");
			break;
		
	}
	}
	fclose(in);
	procede(shit, m, n);//print all the shit out and stuff
	
}
	
int main(int argc, char*argv[]){
	if (argc < 2){
		printf("the correct usage is ./graph01 -<options> <inputfile>\n");
		exit(0);
	}
	
	//DPRINT(("arg 1 is %s, char 1 is %c\n", argv[1], argv[1][1]));
	//check for flags
	Flag flag = none;
	FILE *in;
	if(argv[1][0] == '-'){
		if(argv[1][1] == 'U'){
			flag = U;
			in = fopen(argv[2], "r");
		}
		else error("flag has to be -U retard");
		
	}
	else{
		in = fopen(argv[1], "r");
	}
	
	//process
	if(in){
		doShit(in, flag);
	}
	else printf("file %s doesnt exist\n", argv[1]);
	return(0);
}


