// ms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

const int MSIZE = 32;
typedef int stype;

stype nums[MSIZE];

template <typename T>
void init (T* arr, size_t sz) { 
	for (auto i=0; i < sz; i++) {
		arr[i] = (rand() * ( rand() & 1 ? 1 : -1 )) % 1024 ;
	}
}

template <typename T>
void ms (T* arr, size_t sz) {
	// trivial cases. end of recursion
	if (sz == 1) return;
	if (sz == 2) { // trivial swap
		if ( arr[0] > arr[1]) {
			T temp = arr[0];
			arr[0] = arr[1];
			arr[1] = temp;
		}
		return;
	}

	ms(arr, sz/2); 
	ms(arr + sz/2, sz - (int)(sz/2));

	// merge 
	T* merged = new T[sz];					// allocate buffer
	size_t lp = 0, rp = sz/2, mp = 0;		// left ptr, right ptr, merged ptr

	while (lp < sz/2 || rp < sz ) {
		if ( lp == sz/2 ) {
			while ( rp < sz ) {
				merged[mp++] = arr[rp++];
			}
			continue;
		}
		if ( rp == sz ) {
			while ( lp < sz/2 ) {
				merged[mp++] = arr[lp++];
			}
			continue;
		}
		if ( arr[lp] - arr[rp] < 0 ) { // can be arbitrary comparator
			merged[mp++] = arr[lp++];
		} else {
			merged[mp++] = arr[rp++];
		}
	}

	memcpy(arr, merged, sz * sizeof(T));

	delete merged;
}

#include <time.h>

int _tmain(int argc, _TCHAR* argv[]) {
	srand(time(NULL));
	init<stype>(nums, MSIZE);	
	ms<stype>(nums, MSIZE);

	return 0;
}

