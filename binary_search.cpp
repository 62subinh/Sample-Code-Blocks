#define SIZE 1000

int data [SIZE];
int sorted [SIZE];

/*
	Implementation of Quicksort;
		Param:
			data[]		Stores the data to be sorted.
			sorted[]	Contains the index of the n-th smallest datum, assumed to be initialized as sorted[n] = n;
		Usage:
			quicksort(0, N-1);	// Data is stored in data[0..(N-1)]
*/

int binary_search(int query){
    // Find the location of the datum whose value is the maximum
    // 	among the data less than (or equal to) the given query.
    // Note: The query is assumed to be no less than the value of the first datum.
    int left, right, mid;
    left = -1;
    right = N;
    while(right - left > 1){
        mid = (left + right) / 2;
        
        if(query < jobs[sorted[mid]].e)
            right = mid;
        else
            left = mid;
    }
    return left;
}
