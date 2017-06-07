/************************************************************************
Gavin Chen ghchen@ucsc.edu 1492980
CS101 spring 2017
pa02
************************************************************************/
#ifndef loadGraph
#define loadGraph
#include "minPQ.h"
#include "adjWgtVec.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>


typedef enum {Prims, Dyke} Flag; //flag for prims or dijkirstras 

typedef struct graph{
	AdjWgtVec* vect;//vector array
	MinPQ PQ;//priority queue
	int n; //number of verticies
	int m; //number of edges
} graph;

typedef graph* data; //pointer to struct 
	
	

//creates struct with properly allocated adjvec array and empty PQ
//input: number of nodes
//output: pointer to allocated struct
data create(int nodes);


//adds edge to node, eg adds v2 into v1 data
//input: array of vectors, vertex 1, vertex 2, weight of edge, number of vertecies
//output: nothing, just adds in data
void addVert(AdjWgtVec *ass, int v1, int v2, double weight, int n);

//parses input file and populates adjVec array, makes empty PQ
//input: input file, flag for d or p
//output: pointer to graph struct
data parseFile(FILE *in, Flag flag);

#endif
