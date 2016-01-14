#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stack>
#include <vector>
#include <list>
#include <queue>
using namespace std;


const auto MAXV = 16;
const auto MAXW = 15;
const auto INF = -1;

typedef unsigned int node;
typedef unsigned int weight;
typedef pair<node, weight> nwpair;

auto comparator = [](const nwpair a, const nwpair b) -> bool {
	return a.second > b.second;
};

int main() {
	srand(time(NULL));

	priority_queue<
		nwpair,
		vector<nwpair>,
		decltype(comparator)
	> pq;

	vector<										// vector for number of vertices
		list<									// list of incident vertices
			pair<node, weight>		// which is incident, what weight
		>
	> G(MAXV);

	// init graph
	for (auto i = 0; i < MAXV; i++) {
		cout << i << ':';
		for (auto j = 0; j < MAXV; j++) {
			if (i != j && rand() % 10 > 5) {
				auto inci = make_pair(j, 1 + rand() % MAXW);
				G[i].push_back(inci);
				cout << '(' << inci.first << ',' << inci.second << ')';
			}
		}

		cout << endl;
	}

	// init dijkstra
	vector<node> best(MAXV), via(MAXV);
	vector<bool> visited(MAXV);

	for (auto i = 0; i < MAXV; i++){
		best[i] = via[i] = INF;
		visited[i] = false;
	}

	node s = 0;			// source
	node t = MAXV - 1;	// target
	
	pq.push(make_pair(s, 0));
	best[0] = 0; via[0] = 0;

	do {
		auto curr = pq.top(); 	pq.pop();
		cout << "visiting " << curr.first << " current weight " << curr.second << " via " << via[curr.first] << endl;

		if (curr.first == t) break;

		weight cpath = best[curr.first];

		for (auto &inci : G[curr.first]) {
			if (!visited[inci.first] && cpath + inci.second < best[inci.first]) {
				best[inci.first] = cpath + inci.second;
				via[inci.first] = curr.first;
				pq.push(make_pair(inci.first, cpath + inci.second));
			}
		}		
	} while (pq.size());

	stack <decltype(s)> rew;

	for (auto n = t; n != s; n = via[n]) {
		rew.push(n);
	}

	cout << "shortest: ";
	
	for (rew.push(s); rew.size(); rew.pop()) {
		cout << rew.top() << ' ';
	}

	cout << ", length is " << best[t] << endl;
}
