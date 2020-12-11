#define SIZE 1000
#define INVALID -1

/*
	A max-heap that allows changing the value of its elememt.
	The starting index of the heap is 1.
	
	Param:
		data				Array that stores the values to be sorted.
			data[].value	Values to be compared.
			data[].loc		Location of the datum in the heap, i.e., heap[data[*].loc] = *.
		heap				The max-heap whose elements are the indices of the data.
		heapsize			Size of the heap.
*/
struct Elem {
	int value;
	int loc;	// Location in heap;
	bool operator>(const Elem& e) const {
		return value > e.value;
	}
	void set(int _value, int _loc) {
		value = _value;
		loc = _loc;
	}
	void remove() {
		value = INVALID;
	}
};

Elem data[SIZE + 1];
int heap[SIZE + 1];
int heapsize;

void percolate_up(int start){
	int me = start;
	int parent = start / 2;
	while (parent > 0) {
		if (data[heap[me]] > data[heap[parent]]) {
			// Swap;
			data[heap[me]].loc = parent;
			data[heap[parent]].loc = me;

			int temp = heap[me];
			heap[me] = heap[parent];
			heap[parent] = temp;
			
			// Percolate up;
			me = parent;
			parent = me / 2;
		}
		else
			return;
	}
}

void percolate_down(int start){
	int me = start;
	int left, right, candid;
	left = 2 * me;
	right = left + 1;
	while (left < heapsize) {
		if (data[heap[left]] > data[heap[right]])
			candid = left;
		else
			candid = right;

		if (data[heap[candid]] > data[heap[me]]) {
			// Swap;
			data[heap[candid]].loc = me;
			data[heap[me]].loc = candid;

			int temp = heap[me];
			heap[me] = heap[candid];
			heap[candid] = temp;

			// Percolate down;
			me = candid;
			left = 2 * me;
			right = left + 1;
		}
		else
			return;
	}

	// Compare "left" & "me" if "left" == "heapsize";
	if ((left == heapsize) && (data[heap[left]] > data[heap[me]])) {
		// Swap;
		data[heap[left]].loc = me;
		data[heap[me]].loc = left;

		int temp = heap[me];
		heap[me] = heap[left];
		heap[left] = temp;
	}
	return;
}

void init() {
	heapsize = 0;
}

void clear() {
	heapsize = 0;
}

void push(int idx, char name[]) {
	data[idx].set(idx, name, ++heapsize);
	heap[heapsize] = idx;

	percolate_up(heapsize);
}

int pop() {
	int ret = heap[1];
	data[ret].remove();

	// Swap between [1] and [heapsize];
	heap[1] = heap[heapsize];
	heap[heapsize] = -1;
	data[heap[1]].loc = 1;
	--heapsize;

	percolate_down(1);
	return ret;
}

void mod(int idx, char name[]) {

	Elem elem{};
	elem.set(idx, name, -1);

	if (elem > data[idx]) {
		// Case 1: the new value is greater than the old;
		//		   then percolate up;
		int loc = data[idx].loc;
		data[idx].set(idx, name, loc);
		
		percolate_up(loc);
	}
	else {
		// Case 2: the new value is less than the old;
		//		   then percolate down;
		int loc = data[idx].loc;
		data[idx].set(idx, name, loc);

		percolate_down(loc);
	}
}
