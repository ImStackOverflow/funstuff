/************************************************************************
Gavin Chen ghchen@ucsc.edu 1492980
CS101 spring 2017
pa02
************************************************************************/
#ifndef loadGraph
#define loadGraph
#include "intVec.h"


//creates 2d adjacentcy matrix
//input: graph
//output: 2d int array, 1 = path, 0 = what the fuck u think it means
int** makeAdjMatrix(IntVec* og, int n);


//makes transposed graph given input graph
//input: origional graph, number of nodes
//output: pointer array of intVecs with transposed data
IntVec* transposeGraph(IntVec* og, int n);


//prints adj matrix 
//input: adj matrix
//output: nothang
void printAdjMatrix(int** matrix, int n);


//creates intvec array of length nodes
//input: length of array
//output: pointer array of intVec's
IntVec *create(int nodes);


//free function, frees all intVec pointers
//input: intVec pointer array
//output: none
void freeAll(IntVec* shit, int n);


//prints data verticies and edges
//input: array of intVec's, number of edges, number of nodes (respectivly)
//output: none, just prints
void printShit(IntVec *shit, int m, int n);


//adds edge to node, eg adds v2 into v1 data
//input: array of vectors, vertex 1, vertex 2, weight of edge, number of vertecies
//output: nothing, just adds in data
void addVert(IntVec *ass, int v1, int v2, int weight, int n);

//standard error out function, prints passed in message and exits program
//input: message to output
//output: nothing
void error(const char message[]);

#endif