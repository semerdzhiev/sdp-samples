// dynamic-string-example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <cstring>

struct dynstr {
	struct Node {
		char* payload;
		size_t size;
		Node* next;
		Node(char*);
	};

	Node* head;
		
	dynstr();
	size_t size();
	void print();
	dynstr& concat(char*);
	dynstr& cut(size_t, size_t);

	size_t size_rec(Node*);
};

dynstr::Node::Node(char* newstr) {
	size = strlen(newstr);
	payload = new char[size + 1];
	strcpy_s(payload, size+1, newstr);
	next = NULL;
}

dynstr::dynstr() {
	head = NULL;
}

// calc the size in symbols

size_t dynstr::size() {
	if (!head) return 0;
	
	Node* curr = head;
	size_t res = 0;

	do {
		res += curr->size;
	} while (curr = curr->next);

	return res;
}

size_t dynstr::size_rec(Node *n) {
	if (!n) 
		return 0;
	else 
		return n->size + size_rec(n->next);
}

void dynstr::print() {
	if (!head) {
		printf("N/A content \n");
		return;
	};

	Node* curr = head;
	size_t res = 0;

	do {
		printf("%s", curr->payload);
	} while (curr = curr->next);

	printf("\n");
}

dynstr& dynstr::concat(char* newstr) {
	if (!head) {
		head = new Node(newstr);
	} else {
		Node* curr = head;
		while (curr->next) {
			curr = curr->next;
		}

		curr->next = new Node(newstr);
	};

	return *this;
}

dynstr& dynstr::cut(size_t fro, size_t to) {
	if (!head) {
		return *this;
	}

	if (fro > to) {
		printf("warning: no cutting due to error in range \n");
		return *this;
	}

	size_t sz = size();
	size_t cstart = 0;

	if (fro > sz || to > sz) {
		printf("warning: no cutting due to error in range \n");
		return *this;
	}

	Node* prev = NULL;
	Node* n = head;

	do {
		char *tmp = NULL;
		size_t cend = cstart + n->size;

		// cstart                                     cend
		// |             (fro) x x x x x x x (to)                  |   
		// | << bsz  >>                             << asz >>
		if (fro > cstart && to < cstart + n->size) {
			size_t bsz = fro - cstart;					// before cut-chunk size
			size_t asz = (cend) - to;		// aftercut-chunk  size
			tmp = new char[bsz + asz + 1];

			memcpy_s(tmp, bsz, n->payload, bsz);
			memcpy_s(tmp + bsz, asz, n->payload + to - cstart, asz);
			
			tmp[bsz + asz] = 0;
		} 

		// cstart                                    cend
		// |             (fro) x x x x x x x x x x x x x x x x x  |   
		// | << bsz  >>                      
		if (to > cend && fro > cstart && fro < cend) {
				size_t bsz = fro - cstart;					// before cut-chunk size
				tmp = new char[bsz + 1];		// + 1 for terminating zero
				memcpy_s(tmp, bsz, n->payload, bsz);
				tmp[bsz] = 0;
			}
		
		// cstart                                    cend
		// | x x x x x x x x x x x x x x x (to)                   |   
		// |                                       << asz >>                      
		if (fro < cstart && to > cstart && to < cend) {
			size_t asz = (cend) - to;
			tmp = new char[asz + 1];		// +1 for the terminating zero
			memcpy_s(tmp, asz, n->payload + to - cstart, asz);
			tmp[asz] = 0;
		}
	
		// cstart                                    cend
		// | x x x x x x x x x x x x x x x x x x x x x x x x x x x|   
		// |                                         

		if (fro <= cstart && to >= cend) {
			delete n->payload;
			if (prev) {
				prev->next = n->next;
			}
			Node *t = n;
			n = n->next;
			cstart = cend;
			delete t;
			continue;
		}

		// if we changed something in the current chunk, then 
		// tmp is expected to be different than NULL and assumed
		// to hold the contents of the newly formed chunk

		if (tmp) {
			delete n->payload;
			n->payload = tmp;
		}
	
		// iteration step
		cstart = cend;
		prev = n;
		n = n->next;
	} while (n);

	// handle the case where we delete exactly the whole string
	if (prev == n == NULL) {
		head = NULL;
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	dynstr ds;
	ds.print();
	ds.concat("Baba").concat(" cooks delicious ").concat("soup").concat(" today!");
	ds.print();


	dynstr h;
	h.concat("TTTTT");
	h.cut(0, 5);

	// |  ||               ||  ||     | 
	// Baba cooks delicious soup today!
	// 01234567890123456789012345678901
	// 0         1         2         3
	//

	//                     \_____/
		ds.cut(20, 25);	// Ann Jack

	//      \____/
	// ds.cut(5, 10);

	//    \_______/
	// ds.cut(3, 11);

	ds.print();

 	return 0;
}
