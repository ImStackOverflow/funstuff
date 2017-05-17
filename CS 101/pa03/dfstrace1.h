#ifndef fukingfukfuk
#define fukingfukfuk
/* data held by pointer:
	IntVec* graph;
	int** info;
	int n;
*/
typedef struct Penis* Graph;



//makes datatype that holds IntVec array, empty data array, and number of edges
//input: IntVec array, number of verticies
//output: pointer to struct that holds datas
Graph makeGraph(IntVec* poop, int vert);




//prints out info about verticies
//outputs color, discovery time, finishing time, and parent status of each vertex
//input: data array, size of array (number of nodes)
//output: none
void printInfo(Graph dick);




//first stage of dfs, calls DFSsweep for all undiscovered verticies
//input: graph data
//output: none
void DFSsweep(Graph G);



//second stage of DFS, goes down each node to discover all edges
//input: graph, vertex
//output: none
void DFStrace(Graph G, int vertex , int time);

#endif
