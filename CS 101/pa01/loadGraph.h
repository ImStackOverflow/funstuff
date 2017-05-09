//creates 2d adjacentcy matrix
//input: graph
//output: 2d int array, 1 = path, 0 = what the fuck u think it means
int[][] makeAdjMatrix(IntVec* og);


//makes transposed graph given input graph
//input: origional graph, number of nodes
//output: pointer array of intVecs with transposed data
IntVec* transposeGraph(IntVec* og, int n);


//prints adj matrix 
//input: adj matrix
//output: nothang
void printAdjMatrix(int[][] matrix);
