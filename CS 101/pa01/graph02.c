/********************************************************
Gavin Chen ghchen 1492980
cs101 pa01
4/20/17
*********************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intVec.h"
#include "graph02.h"

//#define DEBUG 1

#ifdef DEBUG
#define DPRINT(x) printf x
#else
#define DPRINT(x) do{} while(0)
#endif
	
int main(int argc, char*argv[]){
	if (argc < 2){
		printf("the correct usage is ./graph01 -<options> <inputfile>\n");
		exit(0);
	}
	
	//DPRINT(("arg 1 is %s, char 1 is %c\n", argv[1], argv[1][1]));
	//check for flags
	Flag flag = null;
	FILE *in;
	if(argv[1][0] == '-'){
		if(argv[1][1] == 'U'){
			flag = U;
			in = fopen(argv[2], "r");
		}
		else printf("dont name files begining with - retard");
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

IntVec *create(int nodes){
IntVec *shit = (IntVec*)calloc(nodes, sizeof(IntVec));
for(int i = 1; i <= nodes; i++){
	shit[i] =  intMakeEmptyVec();
}
return shit;
}

void addVert(IntVec *ass, int v1, int v2, int weight, int n){
	
if(ass){
	if(v1 > n || v2 > n){
		error("addVert the referenced vertex doesnt exist");
	}
	
	IntVec* penis = ass + v1;
	intVecPush(*penis, v2);
	DPRINT(("in addVert  %d into %d\n", intTop(*penis), v1));
	DPRINT(("size is %d capacity is %d\n", intSize(*penis), intCapacity(*penis)));
}
else{
	error(__func__);
}
}

void printData(IntVec shit){
if(intSize(shit) == 0){
	printf("null\n");
}
else{
DPRINT(("size is %d\n", intSize(shit)));
	printf("[");
	printf("%d", intTop(shit));
	int stop = intSize(shit);
	for(int j = 0; j < stop-1; j++){  
	printf(", %d", intData(shit, j));
	}
fflush(stdout);
	DPRINT(("THE FUCK bro       "));
	printf("]\n");
	DPRINT(("THE FUCK DUDE"));
}
}
	
void printShit(IntVec *shit, int m, int n){
printf("n = %d\nm = %d\n", n, m);
for(int i = 1; i <= n; i++){
	printf("%d      ", i);
	printData(*(shit+i));
}
DPRINT(("THE FUCK"));
}

void freeAll(IntVec* shit, int n){
	printf("in %s",__func__);
	IntVec penis;
	for(int i = 0; i < n; i++){
		DPRINT(("freeing %d",i));
		penis = *(shit+i);
		free(dataPtr(penis));
		free(penis);
	}
}

void doShit(FILE *in, Flag flag){
int v1, v2, args, n, m = 0;
double weight = 0;
char what[2000], ass;
	IntVec *shit;

	while(fgets(what, 2000, in) != NULL){
	args = sscanf(what, "%d %d %lf %c", &v1, &v2, &weight, &ass);

		DPRINT(("scanf got %d args\n", args));
	switch (args){
		case -1: //no input
			break;
		case 1://first line
		n = v1;
		DPRINT(("has %d vert\n", v1));
		shit = create(v1);
			break;
		case 2://2 vertecies
		DPRINT(("adding %d to %d data no weight\n", v2, v1));
		addVert(shit, v1, v2, 0, n);
		if(flag == U){
			
			addVert(shit, v2, v1, 0, n);
		}
		m++;
			break;
		case 3://2 verticies with weight
		DPRINT(("adding %d to %d data weight %lf\n", v2, v1, weight));
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
	printShit(shit, m, n);
	fflush(stdout);
	printf("reached the finishline");
	fclose(in);
	printf("reached the finshline");
	freeAll(shit, n);

}

void error(const char message[]){
	printf("there was an error in %s\n", message);
	exit(1);
}
