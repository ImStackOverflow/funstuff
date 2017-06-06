/************************************************************************
Gavin Chen ghchen@ucsc.edu 1492980
CS101 spring 2017
pa02
************************************************************************/
#ifndef loadGraph
#define loadGraph
#include "intVec.h"


//creates adjintvec array of length nodes
//input: length of array
//output: pointer array of adjintVec's
AdjWgtVec *create(int nodes);


//free function, frees all intVec pointers
//input: intVec pointer array
//output: none
void freeAll(AdjWgtVec* shit, int n);


//prints data verticies and edges
//input: array of intVec's, number of edges, number of nodes (respectivly)
//output: none, just prints
void printShit(AdjWgtVec *shit, int m, int n);


//adds edge to node, eg adds v2 into v1 data
//input: array of vectors, vertex 1, vertex 2, weight of edge, number of vertecies
//output: nothing, just adds in data
void addVert(AdjWgtVec *ass, int v1, int v2, int weight, int n);



//prints contents of one single IntVec, essentially prints array
//input: intVec that has data array
//output: none
void printData(AdjWgtVec shit);

//parses input file, returns populated array for graph
//input: input file, flag for d or p
//output: array of adjvec 
AdjWgtVec* parseFile(FILE *in, Flag flag);

#endif
