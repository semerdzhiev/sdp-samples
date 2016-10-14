// mergesort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int arr[] = { 1, 5, -1, 6, 7, 4 };

void merge(const size_t from, const size_t to) {
	const size_t mid = from + (to - from) / 2;	// "middle" (pivot)
	size_t lpos = from;			// left position in old list
	size_t rpos = mid + 1;		// right position in old list
	size_t npos = 0;				// position in newly sorted list
	size_t cnt = to - from + 1;	// count

	int* buf = new int[cnt];
	
	while (lpos <= mid || rpos <= to) {
		while ((arr[lpos] < arr[rpos] || rpos > to) && lpos <= mid) {
			buf[npos++] = arr[lpos++];
		}

		while ((arr[lpos] > arr[rpos] || lpos > mid) && rpos <= to) {
			buf[npos++] = arr[rpos++];
		}

	}

	// copy in place
	memcpy(arr + from, buf, cnt * sizeof(int));
	delete buf;
}

void sort(const size_t from, const size_t to) {
	if (to == from) return;
	
	if (to - from == 1) {
		if (arr[from] > arr[to]) {
			const int temp = arr[to];
			arr[to] = arr[from];
			arr[from] = temp;
		}
		return;
	}

	const int mid = from + (to - from) / 2; 
	sort(from, mid);
	sort(mid + 1, to);
	merge(from, to);
}


int main() {
	sort(0, sizeof(arr) / 4 - 1);
	return 0;
}

