// msort.llist.cpp : Defines the entry point for the console application.
// by Georghi Penkov

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

template <typename T> 
class llist {
	struct node {
		node *next;
		T data;
		node() : next(NULL) {};
		node(T& val) : data(val), next(NULL) {};
		size_t dynlen();
	};

	node *root;

public:
	void add(T&);
	llist() : root(NULL) {};
	void sort(node*);
	node* merge(node*, node*);
	node* msort(node*);
	void print();
};

template <typename T>
void llist<T>::print() {
	node *t = root;
	while (t->next) {
		cout << t->data << ',';
		t = t->next;
	}
	cout << t->data;
}

template <typename T>
size_t llist<T>::node::dynlen() {
	// a corner case. should not happen
	if (!this) return 0;
	node* t = this;
	size_t len = 1;
	while (t->next) {
		len++;
		t = t->next;
	}
	return len;
}

template <typename T>
void llist<T>::add(T& val) {
	// if list is empty
	if (!root) {
		root = new node(val);
		return;
	}
	// figure last
	node *last = root;
	while (last->next) {
		last = last->next;
	}
	last->next = new node(val);
}

// returns the merge of the two lists
template <typename T> 
typename llist<T>::node* llist<T>::merge(
	typename llist<T>::node* lp, 
	typename llist<T>::node* rp) {

//	node *lp = left;		// left part
//	node *rp = right;	// right part
	node *mp = NULL;		// merged product
	node *res = NULL;

	// handle single element cases
	// avoid NULL references in trivial compare
	// should not normally happen
	if (lp == NULL) return rp;
	if (rp == NULL) return lp;

	// now merge
	while (lp || rp) {
		// landle left part empty -> right flush
		if (lp == NULL) {
			while (rp) {
				mp->next = rp;
				mp = mp->next;
				rp = rp->next;
			}
			continue;
		}

		// landle right part empty -> left flush
		if (rp == NULL) {
			while (lp) {
				mp->next = lp;
				mp = mp->next;
				lp = lp->next;
			}
			continue;
		}

		node *c;
		// trivial case
		if (lp->data > rp->data) {
			c = lp;
			lp = lp->next;
		} else {
			c = rp;
			rp = rp->next;
		}
		// the resulting part
		if (mp) {
			mp->next = c;
			mp = mp->next;
		} else {
			res = mp = c;
		}
	}

	return res;
} 

template <typename T>
typename llist<T>::node* llist<T>::msort(node* what) {
	bool init = what ? false : true;
	what = what ? what : root;
	size_t sz = what->dynlen();

	if (sz == 1) return what;

	node* left = what;
	node* right = what; // just for init...

	for (size_t i = 0; i < sz / 2; i++) {
		if (i + 1 == sz / 2) {
			node *temp = right;
			right = right->next;
			temp->next = NULL;
			continue;
		} 
		right = right->next;
	}
	
	left = msort(left);
	right = msort(right);
	node* res = merge(left, right);

	if (init) root = res;
	return res;
}

int main() {
	llist<int> myl;
	srand(time(NULL)); // randomize

	for (int i = 0; i < 8; i++) {
		int v = rand() % 1024;
		myl.add(v);
	}

	myl.msort(NULL);
	myl.print();
	return 0;
}
