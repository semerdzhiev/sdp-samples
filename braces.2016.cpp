#include "stdafx.h"
const unsigned int MAXS = 32;

#include <iostream>
#include <cstring>
using namespace std;

/// stack stuff ///////////////////////////////////////////////////////////////
// m69-031-573

char stack[MAXS];
unsigned int pos = 0;

char top() {
	if (pos > 0)
		return stack[pos - 1];
	else
		return -1;
}

char pop() {
	if (pos == 0)
		return -1;
	else
		return stack[--pos];
}

bool push(char c) {
	if (pos == MAXS) return false;
	else
		stack[pos++] = c;
}

//////////////////////////////////////////////////////////////////////////////

const char str[] = "a(a[a)a]as";
char xlat[128];

void init() {
	xlat['('] = ')';    xlat['['] = ']';
	xlat['<'] = '>';    xlat['{'] = '}';
	xlat[')'] = xlat[']'] = xlat['}'] = xlat['>'] = 1;
}

bool checkbr(const char *s) {
	pos = 0;

	cout << "checking string : " << s << endl;

	for (unsigned int i = 0; i < strlen(s); i++) {
		char curc = s[i];

		if (xlat[curc] > 1) {
			push(curc);
			continue;
		}

		// we have something in the stack
		// and the current symbol is closing brace

		if (pos && xlat[curc] == 1) {
			char sts = top(); // symbol at top of stack
			char m = xlat[sts]; // corresponding char (if any)

			if (curc == m) {
				pop();
				continue;
			}	else {
				cout << "brace type mismatch. bail out." << endl;
				return false;
			}
		}

		// we have a closing brace, but stack is empty        
		if ((pos == 0) && xlat[curc] == 1) {
			cout << "match not possible, closing brace, but stack is not empty" << endl;
			return false;
		}
	}

	if (pos) {
		cout << "match is not possible. stuff left in stack" << endl;
		return false;
	}

	cout << "all KOOOL!" << endl;
	return true;
}

int main() {
	init();

    char *buf = new char[1024];

	do {
		cin.getline(buf, 1024);
		if (strcmp(buf, "exit") == 0) return -1;
		checkbr(buf);
	} while (1);
}
