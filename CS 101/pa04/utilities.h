#ifndef penispenispenis
#define penispenispenis



//standard error function, outputs error message and exits program
//input: error message and __func__
//output: none, just prints message and exits function
void error(char message[], const char function[]);

//prints data verticies and edges
//input: array of intVec's, number of edges, number of nodes (respectivly)
//output: none, just prints
void printShit(AdjWgtVec *shit, int m, int n);

//prints out info about verticies
//outputs fringe weight, parent, and status of each vertex
//input: MinPQ pointer with data
//output: none
//it prints all the data coresponding to each verticie 
void printInfo(MinPQ dick);

#endif
