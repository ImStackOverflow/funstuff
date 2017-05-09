#include "loadGraph.h"
#include "intVec.h"
#include <stdio.h>

int[][] makeAdjMatrix(IntVec* og, int n){
	if(og){//check that data exists
		int **dick = calloc(n, sizeof(int*));//make empty 2d array
		for(int i = 0; i < n; i++){
			dick[i] = calloc(n, sizeof(int));
		}
	
		int size;//size of current node data
		IntVec current;//derefrence current node
		for(int i = 0; i < n; i++){//for each node
			current = *(og + i);
			size = intSize(current);
			for(int j = 0; j < size; j++){
				dick[i][intData(current,j)] = 1;
				}
		}
		return dick;
	}
	else error(__func__);
	return 1;
}

void printAdjMatrix(int[][] matrix, int n){
		//print top header
	for(int i = 1; i <= n; i++){
		printf("%d  ", i);
	}
	printf("\n");
	for(int i = 1; i <= n; i++){
		printf("----");
	}
	printf("\n");
	
	//print matrix
	for(int i = 1; i <= n; i++){
		printf("%d: ", i);
		for(int j = 0; j < n; j++){
			printf("%d ", matrix[i][j]);
		}
	}
}

IntVec* transposeGraph(IntVec* og, int n){
	IntVec* transposed = create(n);
	IntVec penis;
	int size;
	for(int i = 0; i < n; i++){//itterate through IntVec array
		penis = *(og + i); //derefrence pointer
		size = intSize(penis); //get size of data
		for(int j = 0; j < size; j++){
			addVert(transposed, intData(penis, j), i, 0, n);//add vertex to data of data
		}
	}
	return transposed;
}

IntVec *create(int nodes){
IntVec *shit = (IntVec*)calloc(nodes, sizeof(IntVec));
for(int i = 1; i <= nodes; i++){
	shit[i] =  intMakeEmptyVec();
}
return shit;
}

void freeAll(IntVec* shit, int n){
	IntVec penis;
	for(int i = 0; i < n; i++){
		penis = *(shit+i);
		free(penis);
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


void error(const char message[]){
	printf("there was an error in %s\n", message);
	exit(1);
}