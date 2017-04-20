#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intVec.h"

#define DEBUG 1

#ifdef DEBUG
#define DPRINT(x) printf x
#else
#define DPRINT(x) do{} while(0)
#endif

void error(const char message[]);
void doShit(FILE *in);

int main(int argc, char*argv[]){
 
	if (argc != 2){
		printf("the correct usage is ./graph01 <inputfile>\n");
		exit(0);
	}
	FILE *in = fopen(argv[1], "r");
	if(in){
		doShit(in);
	}
	else printf("file %s doesnt exist\n", argv[1]);
	return(0);
}

IntVec *create (int nodes){
  IntVec *shit = calloc(nodes+1, sizeof(IntVec));
  for(int i = 1; i <= nodes; i++){
    shit[i] =  intMakeEmptyVec();
  }
  return shit;
}

void addVert(IntVec *penis, int v1, int v2, int weight, int n){
	
  if(penis){
  	if(v1 > n || v2 > n){
  		error("addVert the referenced vertex doesnt exist");
  	}
    penis += v1;
    intVecPush(*penis, v2);
	DPRINT(("in addVert added %d into %d\n", intTop(*penis), v1));
  }
  else{
    error(__func__);
  }
}

void printData(IntVec shit){
  if(intSize(shit) == 0){
    printf("null\n");
  }
  else{
    printf("[");
    printf("%d", intTop(shit));
    for(int j = 1; j < intSize(shit); j++){
      intVecPop(shit);  
      printf(", %d", intTop(shit));
    }
    printf("]\n");
}
}

void printShit(IntVec *shit, int m, int n){
  printf("n = %d\n m = %d\n", n, m);
  for(int i = 1; i <= n; i++){
    printf("%d      ", i);
    printData(*(shit+i));
  }
}



void doShit(FILE *in){
  int v1, v2, args, n, m = -1;
  double weight = 0;
  char what[2000], ass;
	IntVec *shit;

	while(fgets(what, 2000, in) != NULL){
	  args = sscanf(what, "%d %d %lf %c", &v1, &v2, &weight, &ass);
	    m++;
	switch (args){
		case 0: //no input
			break;
		case 1://first line
		  n = v1;
		  DPRINT(("has %d vert\n", v1));
		  shit = create(v1);
		  shit++; //incriment, [0] stores length of array
			break;
		case 2://2 vertecies
		  DPRINT(("adding %d to %d data no weight\n", v2, v1));
		  addVert(shit, v1, v2, 0, n);
			break;
		case 3://2 verticies with weight
		  DPRINT(("adding %d to %d data weight %lf\n", v2, v1, weight));
		  addVert(shit, v1, v2, weight, n);
			break;
		default:
			error("the input file");
			break;
		
	}
	  }
	printShit(shit, m, n);
}

void error(const char message[]){
	printf("there was an error in %s\n", message);
	exit(1);
}
