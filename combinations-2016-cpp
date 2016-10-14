// recurse-permute.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

const unsigned int SZ = 3;
const char e[] = { 'a', 'f', 'x', '0' };
bool u[sizeof(e)];	// designate usage
char c[SZ];			// current state

void print() {
	cout << "found: ";
	for (int i = 0; i < SZ; i++) {
		cout << c[i] << ' ';
	}

	cout << endl;
}

void debug() {
	cout << "crrnt: ";
	for (int i = 0; i < SZ; i++) {
		cout << ( c[i] ? c[i] : '*' ) << ' ';
	}

	cout << endl;
}

void rec(const int pos) {
	if (pos == SZ) {
		print();
		return;
	}

	debug();

	for (int i = 0; i < sizeof(e); i++) {
		if (!u[i]) {
			u[i] = true;
			c[pos] = e[i];
			rec(pos + 1);
			u[i] = false;
			c[pos] = 0;
		}
	}
}

int main()  {
	rec(0);
	return 0;
}

