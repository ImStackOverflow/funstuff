/********************************************************
Gavin Chen ghchen 1492980
cs101 pa01
4/20/17
*********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loadGraph.h"

#define DEBUG 1

#ifdef DEBUG
#define DPRINT(x) printf x
#else
#define DPRINT(x) do{} while(0)
#endif


	
int main(int argc, char*argv[]){
	if (argc < 2){
		printf("the correct usage is ./scc03 -<options> <inputfile>\n");
		exit(0);
	}
	Flag flag = none;
	FILE *in;
	if(argv[1][0] == '-'){
		if(argv[1][1] == 'U'){
			flag = U;
			in = fopen(argv[2], "r");
		}
		else error("flag has to be -U retard");
		
	}
	else{
		in = fopen(argv[1], "r");
	}
	
	//process
	if(in){
		doShit(in, flag);
	}
	else printf("file %s doesnt exist\n", argv[1]);
	return(0);
}


