/********************************************************
Gavin Chen ghchen 1492980
cs101 pa01
4/20/17
*********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loadGraph.h"
#include "utilities.h"
#include "logic.h"

//#define DEBUG 1

#ifdef DEBUG
#define DPRINT(x) printf x
#else
#define DPRINT(x) do{} while(0)
#endif


/*****************
 * actual main
 * processes data and outputs result
 * ****************/
void process(FILE *in, Flag flag, int start){
	data woah = parseFile(in, flag);//set up adj array and minPQ
	printAdjVec(woah->vect, woah->n, woah->m);//print raw input
	
	algorithm(woah, start, flag);//run the actual algorithim
	
	if(flag == Dyke) printf("\n\nRunning Djikrstras algorithim:  \n --------------------------");
	else printf("\n\nRunning Prims algorithim:  \n --------------------------");
	
	printPQ(woah->PQ, woah->n);//print output of algorithim



}
	
	
int main(int argc, char*argv[]){
	if (argc < 4){
		printf("the correct usage is ./greedy04 -<options> <start vertex> <inputfile>\n");
		exit(0);
	}
	Flag flag;//denotes options (dijikstras or prims)
	FILE *in;
	
	//check flag
	if(argv[1][0] != '-') error("specify algorithm retard", __func__);
	if(argv[1][1] == 'D' || argv[1][1] == 'd') flag = Dyke;
	else if(argv[1][1] == 'P' || argv[1][1] == 'p') flag = Prims;
	else error("not a valid flag", __func__);
	in = fopen(argv[3], "r");
		
	//process
	if(!in){
		//make sure input file exists
		printf("file %s doesnt exist\n", argv[3]);
		return(0);
		
	}
	process(in, flag, atoi(argv[2]));//do everyting
}


