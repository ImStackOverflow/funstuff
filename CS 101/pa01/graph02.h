#ifndef graph02
#define graph02


typedef enum {U, null} Flag;
	
	
//makes a pointer array w/ "nodes" entries
//input: number of entries
//output: intVec pointer array (pointer to pointer)
IntVec *create(int nodes);


//adds vertex v2 into v1.data
//input: intvec array, 1st node, 2nd node, weight, number of nodes
//output: none
void addVert(IntVec *ass, int v1, int v2, int weight, int n);
	

//standard error exit function
//input: exit message
//output: none just ends program
void error(const char message[]);

//text parse function, does everything
//input: none
//output: none
//creates array of intvec's from data and prints it out
void doShit(FILE *in, Flag flag);


#endif