#define NUMBER_NODES 1000
#define NUMBER_EDGES 1000
#define LARGE_NUMBER 99999999

/*
	Implementation of Dijkstra algorithm.
	Param:
		nList			Memory for nodes; nodes of IDs 1 ~ N is stored;
						also stores the "cost" for Dijkstra algorithm.
		eList			Memory for edges; this array replaces malloc() or new();
						all edges starting from / pointing to a given node is represented as a linked list.
		heap			A min-heap whose element can be modified;
						sorts nodes according to their costs.
			heapsize	The size of the heap.
*/

typedef struct _edge {
	int start, dest;
	int cost;
	struct _edge* sNext, * dNext;
} edge;

typedef struct _node {
	edge* asStart;
	edge* asDest;
	int cost;	// Cost of reaching this from the specific start.
	int loc;	// Location of this node in the heap.
} node;

int N, M;

node nList[NUMBER_NODES+1];
edge eList[NUMBER_EDGES];
int heap[NUMBER_NODES+1];	// A min-heap of indices of nList;
int heapsize;

void init(){
	// Initialize nList;
	for (int n = NUMBER_NODES; n; --n) {
		nList[n].asDest = 0;
		nList[n].asStart = 0;
	}
}

void readEdge(int start, int dest, int cost){
	// Store the given information in the memory.
	eList[t].start = start;
	eList[t].dest = dest;
	eList[t].cost = cost;

	// Add the edge information in the start/dest nodes.
	eList[t].sNext = nList[start].asStart;
	nList[start].asStart = &eList[t];
	eList[t].dNext = nList[dest].asDest;
	nList[dest].asDest = &eList[t];	
}

void percolate_up(int start) {
	int me = start;
	int parent = start / 2;
	while (parent > 0) {
		if (nList[heap[me]].cost < nList[heap[parent]].cost) {
			// Swap;
			nList[heap[parent]].loc = me;
			nList[heap[me]].loc = parent;

			int temp = heap[parent];
			heap[parent] = heap[me];
			heap[me] = temp;

			// Percolate up;
			me = parent;
			parent = me / 2;
		}
		else
			return;
	}
}

void percolate_down(int start) {
	int me = start;
	int left, right, candid;
	left = 2 * me;
	right = left + 1;
	while (left < heapsize) {
		if (nList[heap[left]].cost < nList[heap[right]].cost)
			candid = left;
		else
			candid = right;

		if (nList[heap[candid]].cost < nList[heap[me]].cost) {
			// Swap;
			nList[heap[candid]].loc = me;
			nList[heap[me]].loc = candid;

			int temp = heap[candid];
			heap[candid] = heap[me];
			heap[me] = temp;

			// Percolate down;
			me = candid;
			left = 2 * me;
			right = left + 1;
		}
		else
			return;
	}

	// Compare "left" & "me" if "left" == "heapsize";
	if ((left == heapsize) && (nList[heap[left]].cost < nList[heap[me]].cost)) {
		// Swap;
		nList[heap[left]].loc = me;
		nList[heap[me]].loc = left;

		int temp = heap[left];
		heap[left] = heap[me];
		heap[me] = temp;
	}
}

int pop() {
	// Return the cost & save the node index in "v."
	int ret = heap[1];
	nList[heap[1]].loc = -1;

	// Swap between [1] and [heapsize];
	heap[1] = heap[heapsize];
	nList[heap[1]].loc = 1;
	--heapsize;

	percolate_down(1);
	return ret;
}

void mod(int n, int nCost) {
	// Change the cost of heap[v].
	int oCost = nList[heap[n]].cost;
	nList[heap[n]].cost = nCost;

	if (nCost < oCost) {
		// Case 1: the new value is lesser than the old;
		percolate_up(n);
	}
	else {
		// Case 2: the new value is greater than the old;
		percolate_down(n);
	}
}

void dijkstra(int v) {
	// Note: heap_push is trivial in here, so initialize heap directly.
	for (int n = 1; n <= N; ++n) {
		heap[n] = n;
		nList[n].loc = n;
		nList[n].cost = LARGE_NUMBER;
	}
	heap[1] = v;
	nList[1].loc = v;
	heap[v] = 1;
	nList[v].loc = 1;

	nList[v].cost = 0;
	heapsize = N;

	int costCandid;
	while (heapsize) {
		// Get the node with the minimum cost.
		v = pop();
		totalCost[v] = nList[v].cost;

		// For each edge of the chosen node,
		// update the cost of the adjacent node if it is less costly. 
		edge* start = nList[v].asStart;
		while (start != 0) {
			costCandid = start->cost + nList[v].cost;
			if (costCandid < nList[start->dest].cost) {
				mod(nList[start->dest].loc, costCandid);
			}
			start = start->sNext;
		}

		nList[v].asStart = 0;	// Clear the node;
	}
}
