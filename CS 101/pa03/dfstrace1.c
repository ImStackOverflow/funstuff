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
	if(!penis || !poop){
		error(__func__);	
	}
	penis->graph = poop;
	penis->info = makeArray(vert);
	penis->stack = intMakeEmptyVecN(vert);//use intVec datatype as stack, functions already written
	penis->n = vert;//# of verticies
	return penis;
}



//makes transposed Graph data type, keeps finishing stack
//input: graph to make transpose of
//output: transposed graph with finishing time stack
Graph hugePenis(Graph foreSkin){
	if(!foreSkin) error(__func__);


	IntVec* transposed = transposeGraph(foreSkin->graph, foreSkin->n, foreSkin->stack);
	Graph vag = makeGraph(transposed , foreSkin->n);//make graph with transposed adj list
	int dick = intSize(foreSkin->stack)-1;
	for(int i = dick; i >= 0; i--){
		intVecPush(vag->stack, intData(foreSkin->stack, i));//copy finishing time stack
	}
	return vag;
}

void printDis(Graph G){
	IntVec shit = G->stack;
	int dick = intSize(shit)-1;
	for(int i = dick; i >= 0; i--){
		printf("%d   ", intData(shit,i));
	}
	printf("\n");
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
		parent = 1;
		info = G->info[i];//dereference pointer to data array
		GeriatricFuck = info[0];
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
		if(!info[3]) parent = -1;
			printf("%5d %5c %5d %5d %5d\n", i+1, color, info[1], info[2], parent);
	}
	printf("\nthe stack shit looks like: ");
	printDis(G);
}	




//sets all color data for nodes to white
void makeWhite(Graph G){
	int n = G->n;
	Vcolor color = WHITE;
	for(int i = 0; i < n; i++){
	G->info[i][0] = color;
	}
}





//manipulates data array, sets color, time varriable, or predecesor for certain vertex
//input: 1D data array, choice, data(time or predecesor)
//output: none
void fuckit(Graph G, int vertex, Choice choice, int data){
	vertex--;//convert so passed vertex matches with data indicie 
	int* info = G->info[vertex];	
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
			info[1] = data;
			break;
		case fT://store finishing time
			info[2] = data;
			break;
		case P://store predecesor
			info[3] = data;
			break;
	}
}


	
int DFStrace(Graph G, int vertex, int time){
	time++;
	//set to gray and define discovery time
	fuckit(G, vertex, mG, 0);//make gray
	fuckit(G, vertex, dT, time);


	IntVec node = G->graph[vertex];//get vertex (starts at 1)
	int adjV, end = intSize(node)-1;//number of elements
	Vcolor white = WHITE;
	for(int i = end; i >= 0; i--){
		adjV = intData(node, i);//get adjacent vertex
		if(G->info[adjV-1][0] == white){//if vertex is undicovered
			fuckit(G, adjV, P, vertex);//add vertex as parent to adj vertex
			time = DFStrace(G, adjV, time);//go discover
		}
	}
	//gone through all adjacent verticies
	fuckit(G, vertex, mB, 0);//make vertex black
	time++; //making black is a move
	fuckit(G, vertex, fT, time);
	intVecPush(G->stack, vertex);//add to finishing time stack
	return time;
}




void DFSsweep(Graph G){
	int time = 0;
	Vcolor color = WHITE;
	makeWhite(G);//set all nodes to white
	for(int i = 0; i < G->n; i++){
		if (G->info[i][0] == color){ //if node is white (undiscovered)
		time = DFStrace(G, i+1, time);
		}
	}
}


int DFStrace2(Graph G, int vertex, int time, int parent){
	time++;
	fuckit(G, vertex, P, parent);
	//set to gray and define discovery time
	fuckit(G, vertex, mG, 0);//make gray
	fuckit(G, vertex, dT, time);


	IntVec node = G->graph[vertex];//get vertex (starts at 1)
	int adjV, end = intSize(node)-1;//number of elements
	for(int i = end; i >= 0; i--){
		adjV = intData(node, i);//get adjacent vertex
		if(G->info[adjV-1][0] == WHITE){//if vertex is undicovered
			fuckit(G, adjV, P, parent);//add top vertex as root to adj vertex
			time = DFStrace2(G, adjV, time, parent);//go discover
		}
	}
	//gone through all adjacent verticies
	fuckit(G, vertex, mB, 0);//make vertex black
	time++; //making black is a move
	fuckit(G, vertex, fT, time);

	return time;
}


Graph DFSPhase2(Graph G){
	Graph imTrans = hugePenis(G);//make transposed graph
	int time = 0;
	makeWhite(imTrans);//set all nodes to white
	int pein, dick = intSize(imTrans->stack);
	for(int i = dick; i >= 0; i--){
		intVecPop(imTrans->stack);
		pein = intTop(imTrans->stack);
		if (imTrans->info[pein-1][0] == WHITE){ //if node is white (undiscovered)
		time = DFStrace2(imTrans, pein, time, pein);
		}
	}
	return imTrans;
}


void printInfo2(Graph scrotum){
	printf("Vertex  Color2  dTime2  fTime2  Parent2 dfstRoot2\n");
	printf("--------------------------------------------------\n");	
	int parent = 1;
	int* info;//data array
	char color;//for printing
	Vcolor GeriatricFuck;//also for printing 
	for(int i = 0; i < scrotum->n; i++){
		parent = 1;
		info = scrotum->info[i];//dereference pointer to data array
		GeriatricFuck = info[0];
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
		if(info[3] == i+1) parent = -1;//if parent/root is itself then its a root
			printf("%6d %6c %6d %6d %6d %6d\n", i+1, color, info[1], info[2], parent, info[3]);
	}
}	
	













