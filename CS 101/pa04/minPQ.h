/* minPQ.h (what is the purpose of this file? Replace this question with your comment.)
*/

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */

/** isEmpty 
preconditions: the priority queue is initialized and exists
input: the priority queue
output: 1 if the queue is empty 0 otherwise
*/
int isEmptyPQ(MinPQ pq);

/** getMin
preconditions: the priority queue is initialized and exists
input: the priority queue
output: the fringe vertex with the minimum fringe weight
*/
int getMin(MinPQ pq);

/** getStatus
preconditions: the pq exists and the vertex (id) is within the bounds 0 < id < n
input: the pq and the node want status of
return: status of the given node
*/
int getStatus(MinPQ pq, int id);

/** getParent 
preconditions: the pq exists and the vertex (id) is within the bounds 0 < id < n
input: the pq and the node want parent of
return: parent of the given node
*/
int getParent(MinPQ pq, int id);

/** getPriority
preconditions: the pq exists and the vertex (id) is within the bounds 0 < id < n
input: the pq and the node want priority of
return: priority of the given node
*/
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/** delMin
preconditions: pq exists and has minimum vertex
input: pq
output: none, sets current min vertex to intree status, resets min vertex, decreases queue number
	if no min vertex then does nothing
*/
void delMin(MinPQ pq);

/** insertPQ 
preconditions: pq exists and id is a valid vertex
input: pq, vertex want to modify, priority of vertex, parent of vertex
output: none, changes priority and parent of vertex (id), setes status[id] to fringe
	resets minVertex, incriments pq counter
*/
void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey
preconditions: pq is initialized and id is a valid vertex
input: pq, vertex want to modify, fringe weight, parent vertex
output: none, changes priority[id] and parent[id], resets min vertex
*/
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/** createPQ 
preconditions: status, priority, and parent arrays are allocated propery
input: number of verticies, status array, priority array, parent array all of size n+1
output: pointer to priority queue, sets all elements in status array to unseen
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif

