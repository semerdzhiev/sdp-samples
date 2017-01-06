// fsm.cpp.cpp : simple example of running an FSM
// by G.Penkov / FMI 2016

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

typedef unsigned int nodeid;

// STL's pair is also a nice candidate for 
// the transition structure...

struct transition { char c; nodeid dest; };

const unsigned int MAXNODES = 5;
nodeid SNODE = 0;
nodeid ENODE = MAXNODES - 1;

// transitions source
char *INPUT = 
"0 a 1 \n" 
"0 b 2 \n"
"1 c 1 \n"
"1 b 3 \n"
"2 c 4 \n"
"3 c 4 \n"
"4 0 4 \n";

char buf[16];

// transitions will be stored here
vector<list<transition>> t(MAXNODES);

void readFSM(istream &istr) {
	while (istr) {
		nodeid n; char c; nodeid dest;
		istr >> n >> c >> dest;
		t[n].push_back({ c, dest });
	}
}


// follow through states iteratively
bool match(istream& istr) {
	nodeid cur = SNODE;
	char c;

	while ((c = istr.get()) != -1) {
		bool transit = false;
	
		std::for_each(t[cur].begin(), t[cur].end(), [&](transition& t) {
			if (t.c == c) {
				cur = t.dest;
				transit = true;
			}});

		if (!transit) return false;
	}

	if (cur != ENODE) return false;
	return true;
}

int main() {	
	istringstream istr(INPUT);
	readFSM(istr);

	istringstream mstr("acccbc0");

	if (match(mstr)) {
		cout << "MATCHED";
	} else {
		cout << "COULD NOT MATCH";
	};

	return 0;
}
