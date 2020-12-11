#define SIZE 1000

int data[SIZE];
int sorted[SIZE];

/*
	Implementation of Quicksort;
		Param:
			data[]		Stores the data to be sorted.
			sorted[]	Contains the index of the n-th smallest datum, assumed to be initialized as sorted[n] = n;
		Usage:
			quicksort(0, N-1);	// Data is stored in data[0..(N-1)]
*/

void quicksort(int start, int end) {
	if (end - start < 1)
		return;
	
	int pivot = data[sorted[end]];
	
	int left, right;
	left = start - 1;
	for (right = start; right < end; ++right) {

		if (data[sorted[right]] < pivot) {
			++left;
			int temp = sorted[left];
			sorted[left] = sorted[right];
			sorted[right] = temp;
		}
	}
	++left;
	int temp = sorted[end];
	sorted[end] = sorted[left];
	sorted[left] = temp;

	quicksort(start, left - 1);
	quicksort(left + 1, end);
}