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
	
	//IntVec* penis = ass + v1;
	intVecPush(*(ass+v1), v2);
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
	printf("[");
	printf("%d", intTop(shit));
	int stop = intSize(shit);
	int dick;
	for(int j = 0; j < stop-1; j++){ 
		dick = intData(shit, j);
	printf(", %d", dick);
	}
fflush(stdout);
	printf("]\n");
}
}
	
void printShit(IntVec *shit, int m, int n){
printf("n = %d\nm = %d\n", n, m);
for(int i = 1; i <= n; i++){
	printf("%d      ", i);
	printData(*(shit+i));
}
}

void freeAll(IntVec* shit, int n){
	IntVec penis;
	for(int i = 0; i < n; i++){
		penis = *(shit+i);
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
	printShit(shit, m, n);
	fflush(stdout);
	fclose(in);
	freeAll(shit, n);

}

void error(const char message[]){
	printf("there was an error in %s\n", message);
	exit(1);
}
