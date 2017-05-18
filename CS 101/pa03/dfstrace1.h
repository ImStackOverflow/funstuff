/*****************************************************
Gavin Chen ghchen 1492980
5/17/17
*****************************************************/


#ifndef fukingfukfuk
#define fukingfukfuk





/* data held by pointer:
	IntVec* graph;
	int** info;
	intVec stack;
	int n;
*/
typedef struct Penis* Graph;



//makes datatype that holds IntVec array, empty data array, and number of edges
//preconditions: the adj array exists
//input: IntVec array, number of verticies
//output: pointer to struct that holds datas
//all data with exception of the IntVec array and verticie number is set to zero
//data in the 2D info array is stored as [vertex][info]
//[0] = color, [1] = disc time, [2] = fin time, [3] = predecesor/root vertex
Graph makeGraph(IntVec* poop, int vert);


//prints the finishing stack
//preconditions: graph G exists
//input: graph
//output: none
//it simply iterates through the function stack and prints
void printDis(Graph G);


//prints out info about verticies
//outputs color, discovery time, finishing time, and parent status of each vertex
//input: data array, size of array (number of nodes)
//output: none
//it prints all the data coresponding to each verticie 
void printInfo(Graph dick);


//first stage of dfs, calls DFSsweep for all undiscovered verticies
//input: graph data
//output: none
//after stage is completed the finishing stack is generated and sored in graph->stack
//and each nodes finishing and discovery time is stored in the info array
void DFSsweep(Graph G);


//computes SCC, second phase. It computes the transpose of the graph and runs the DFS algorithm
//starting from the top of the finishing time stack from the previous step
//input: output of DFSsweep (DFS phase 1)
//output: new graph with SCC's computed
//after this function completes each transposed verticies discovery and finishing time is completed,
//and each parent/root of the tree is set
Graph DFSPhase2(Graph G);




//prints out info about verticies
//outputs color2, discovery time2, finishing time2, parent2, root of each vertex
//input: data array, size of array (number of nodes)
//output: none
//this function is almost identical to the printInfo with the exception that it prints the root 
//and has some some different header text
void printInfo2(Graph scrotum);

#endif
