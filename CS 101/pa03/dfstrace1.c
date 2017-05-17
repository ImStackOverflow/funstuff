#include <stdlib.h>
#include <stdio.h>
#include "loadGraph.h"
#include "dfstrace1.h"
#include "intVec.h"



typedef struct Penis{//struct to hold data to pass around data (accessed by pointer)
	IntVec* graph;//array of adj matricies
	int** info;//array that holds verticie info
	//[0] = color, [1] = disc time, [2] = fin time, [3] = predecesor vertex
	IntVec stack; //finishing time stack
	int n;//number of verticies
	
}Penis;

typedef enum {WHITE, GRAY, BLACK} Vcolor;//vertex color

//choice: make white, gray, black, store disc time, store finish time
typedef enum {mW, mG, mB, dT, fT, P} Choice;



//makes 2D array to hold data about verticies,
//[i][0] = color (initialized to white), [i][1] = dTime, [i][2] = fTime
//input: number of verticies
//output: 2D array pointer
int** makeArray(int n){
	int** dick = calloc(n,sizeof(int*));
	if (!dick){
		error(__func__);
	}
	for(int i = 0; i < n; i++){
		dick[i] = calloc(4, sizeof(int));
	}
	return dick;
}



//initializes graph
Graph makeGraph(IntVec* poop, int vert){
	Graph penis = (Graph) malloc(sizeof(Penis));
	if(!penis){
		error(__func__);	
	}
	penis->graph = poop;
	penis->info = makeArray(vert);
	penis->stack = intMakeEmptyVecN(vert);//use intVec datatype as stack, functions already written
	penis->n = vert;//# of verticies
	return penis;
}



//prints shit
void printInfo(Graph G){
	printf("Vertex  Color  dTime  fTime  Parent\n");
	printf("-------------------------------------------\n");	
	int parent = 1;
	int* info;//data array
	char color;//for printing
	Vcolor GeriatricFuck;//also for printing 
	for(int i = 0; i < G->n; i++){
	info = G->info[i];//dereference pointer to data array
	GeriatricFuck = G->info[i][1];
	switch(GeriatricFuck){ //choose printing color leter 
		case WHITE:
			color = 'W';
			break;
		case GRAY:
			color = 'G';
			break;
		case BLACK:
			color = 'B';
			break;
		default:
			color = 'E';
			break;
}
		printf("%d       %c       %d       %d      %d\n", i+1, color, info[0], info[2], parent);
}
}


//sets all color data for nodes to white
void makeWhite(Graph G){
	int n = G->n;
	Vcolor color = WHITE;
	for(int i = 0; i < n; i++){
	G->info[i][0] = color;
	}
}


void DFSsweep(Graph G){
	int time = 0;
	Vcolor color = WHITE;
	makeWhite(G);//set all nodes to white
	for(int i = 0; i < G->n; i++){
		if (G->info[i][0] == color){ //if node is white (undiscovered)
		DFStrace(G, i, time);
		}
	}
}



//manipulates data array, sets color or time varriable
//input: 1D data array, choice, time
//output: none
void fuckit(int* info, Choice choice, int time){
	Vcolor color;
	switch(choice) {
		case mW://set node color to white
			color = WHITE;
			info[0] = color;
			break;
		case mG://set to gray
			color = GRAY;
			info[0] = color;
			break;
		case mB://set to black
			color = BLACK;
			info[0] = color;
			break;
		case dT://store disc time
			info[1] = time;
			break;
		case fT://store finishing time
			info[2] = time;
			break;
	}
}


	
void DFStrace(Graph G, int vertex, int time){
	time++;
	//set to gray and define discovery time
	Choice choice = mG;
	fuckit(G->info[vertex], choice, time);
	choice = dT;
	fuckit(G->info[vertex], choice, time);
	IntVec node = G->graph[vertex];
	int adj, edge = intSize(node)
	for(int i = 0; i < edge; i++){
		
		
}



















