#include "utilities.h"


//error function
void error(char message[], const char function[]){
	printf("%s in %s\n", message, function);
	exit(1);
}


void printData(AdjWgtVec shit){
if(adjWgtSize(shit) == 0){ //check if node has data 
	printf("null\n");
}
else{ //print data
	AdjWgt butt;
	printf("[");
	butt = adjWgtData(shit,0);
	printf("%d", butt.to);
	int stop = adjWgtSize(shit);
	for(int j = 1; j < stop; j++){ //print upto second to last data (last ones a 0)
		butt = adjWgtData(shit,j);
		printf(", %d", butt.to, butt.wgt);
	}
	printf("]\n");
}
}
	
void printAdjVec(AdjWgtVec *shit, int n, int m){
printf("n = %d\n m = %d\n", n, m);
for(int i = 1; i <= n; i++){
	printf("%d      ", i);
	printData(*(shit+i));//print data for each node
}
}

void printPQ(MinPQ dick, int n){
	/******************* header ********************/
	for (int i = 0; i < n; i++)
	{
		printf("----------------");
	}
	printf("\n           ");

	for (int i = 1; i <= n; i++)
	{
		printf("%8d", i);
	}
	printf("\n");
	
	for (int i = 0; i < n; i++)
	{
		printf("----------------");
	}
	printf("\n priority:  ");

	/*******************fringe weight********************/
	for (int i = 1; i <= n; i++){
		printf("%8.3f", getPriority(dick,i));
	}
	printf("\n parent:  ");

	/******************* parent ********************/
	for (int i = 1; i <= n; i++){
		printf("%8d", getParent(dick, i));
	}
	printf("\n status:  ");

	/******************* status ********************/
	for (int i = 1; i <= n; i++){
		char penis[10];
		switch (getStatus(dick,i)){
			case 'u':
				strcpy(penis, "unseen");
				break;

			case 'f':
				strcpy(penis, "fringe");
				break;

			case 't':
				strcpy(penis, "tree");
				break;

			default:
				break;
		}
		printf("%8s", penis);
	}
	
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("----------------");
	}
	printf("\n");
}
