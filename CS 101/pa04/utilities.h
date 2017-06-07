#ifndef penispenispenis
#define penispenispenis

#include "minPQ.h"
#include "adjWgtVec.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//standard error function, outputs error message and exits program
//input: error message and __func__
//output: none, just prints message and exits function
void error(char message[], const char function[]);

//prints data verticies and edges of adjacency array
//input: array of intVec's, number of edges, number of nodes (respectivly)
//output: none, just prints
void printAdjVec(AdjWgtVec *shit, int n, int m);

//prints out info about verticies from PQ
//outputs fringe weight, parent, and status of each vertex
//input: MinPQ pointer with data
//output: none
//it prints all the data coresponding to each verticie 
void printPQ(MinPQ dick, int n);

#endif
