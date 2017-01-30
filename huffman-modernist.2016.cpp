// huffman-modernist.cpp : 
// by Gheorghi Penkov @ FMi.uni-sofia.bg

#include "stdafx.h"

// structures 
#include <map>			// std::map
#include <queue>        // std::priority_queue
#include <deque>        // std::deque instead of vector
						// as it would fragment the heap less
						// and we mostly have front/back insertions
// stream helpers
#include <sstream>
#include <iostream>
#include <fstream>

// hoffman node correlates : 
//  input stream character code 'c' 
//  currently with some 
//  count of occurances 'count' 
//  and a possible parent '*parent''

const int NOCHAR = -1;		// denotes a nochar

struct HNode {
	int c;					// we'll use int so that we have -1 option, i.e. the NOCHAR symbol
	size_t count;			// occurances count
	HNode *parent, 
		*left, *right;		// node relationships
	std::deque<bool>  code;	// the code - precomputed 

	HNode(decltype(c) chr) : c(chr), count(1) { parent = left = right = NULL; };
	HNode(decltype(c) chr, decltype(count) cnt) : c(chr), count(cnt) { parent = left = right = NULL; };
	~HNode() { std::cout << "note: destructing HNode instance. you should not see this until program end!" << std::endl; };

	auto operator! () -> decltype(code)&;
};

inline auto operator << (std::ostream& ostr, std::pair<char, HNode> node) -> decltype(ostr) {
	for (auto &e : !node.second) ostr << e;
	return ostr;
};

inline auto operator << (std::ostream& ostr, HNode& hn) -> decltype(ostr) {
	for (auto &e : !hn) ostr << e;
	return ostr;
};

auto HNode::operator!() -> decltype(code)& {
	if (code.size()) {
		return code;
	} 

	auto curr = this;
	while (curr->parent) {
		auto par = curr->parent;
		if (curr == par->left) {
			code.push_front(0);
		} 
		if (curr == par->right) {
			code.push_front(1);
		}
		// now move up the inheritance tree -> to the root
		curr = par;	
	}

	return(code);
}

// used by the priority queue
// comparator for the node 

class HCompare {
public:
	bool reverse;
	HCompare(const decltype(reverse)& r = false) : reverse(r) {};

	auto operator() (const HNode* a, const HNode *b) const -> bool {
		return (a->count > b->count) ^ reverse;		// ^ is a XOR operation here
	}
};

////////////////////////////////////////////////////////////////

// note: we'll be usiung HNode* all the way,
// as we don't want STL push/pop operators
// doing copies of objects all the time

// used when building the Hoffman Tree
std::priority_queue<HNode *, std::deque<HNode *>, HCompare> pq;

// we'll convinently keep this map throughout the program -
// it will be used when generating the actual huffman code 
// for each char. as 
std::map <char, HNode*> items;

////////////////////////////////////////////////////////////////

auto INPUT2 = "aaaabbbbccccccc";
auto INPUT = "this is the input \
			    string that we are \
			    goig to compare \
			    in this example !!!\
			    yeah.";

void parse_input(std::istream &istr)  {
	auto c = -1;
	while ((c = istr.get()) > 0) {
		if (items[c]){
			items[c]->count++;
		} else {
			items[c] = new HNode(c);
		}
	}

	for (auto i : items) { 		// typeof(i) should be a kind of reference to pair of <char, HNode*>
		pq.push(i.second);		// pq expects pointer to HNode, which is the .second property of i
		std::cout << "character " << i.second->c << " has " << i.second->count << " occurances " << std::endl;
	}
}

auto build_tree() -> decltype(pq.top()) {
	while (pq.size() > 1) {
		auto a = pq.top(); pq.pop();	
		auto b = pq.top(); pq.pop();	
		auto par = new HNode(NOCHAR, a->count + b->count);		// produces HNode*
		a->parent = par = b->parent = par;		// set parent-child
		par->left = a; par->right = b;			// relationships
		pq.push(par);

		std::cout << a->c << "/" << a->count << " and "
			<< b->c << "/" << b->count << " combined into "
			<< par->c << "/" << par->count << std::endl;
	}
	return pq.top();
}

void encode(std::istream &istr, std::ostream& ostr, bool binout = false) {
	auto c = -1;
	ostr << "ENCODED: ";
	while ((c = istr.get()) > 0) {
		auto itm = items[c];
		if (!itm) { std::cerr << "unknown item! possible tree builder issue. "; exit(0); };
		if (binout) {
		// TODO: use std::bitset or other plain bitwise encoder technique
		} else {
			ostr << *itm;
		}
	}
}

void check_enc() {
	for (auto const &i : items) {
		std::cout << "character [" << i.first << "] encoded as: ";
		auto node = *(i.second);
		for (auto const &e : !node) {
			std::cout << e;
		}
		std::cout << std::endl;
	}
}

int main(int argc, _TCHAR* argv[]) {
	std::istringstream istr(INPUT);
	parse_input(istr);
	auto htree = build_tree();
	check_enc();

	std::istringstream estr(INPUT);
	encode(estr, std::cout);

	return 0;
}
