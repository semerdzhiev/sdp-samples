
// treeprint.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <functional>
#include <string>
#include <list>
#include <memory>

std::string INPUT = "\
A 3 B C D \n\
B 2 E F \n\
C 1 G \n\
D 2 H I \n\
H 2 K L \n\
= \n\
? LEVEL 2 \n\
? CHILDREN C D \n\
? SIBLINGS E \n\
";

template <typename T>
class Tree {
public:
	struct Node {
		T pl;						// payload
		size_t level;
		std::list<Node*> children;	// descendants
		Node(const T x, const size_t l = 0) : pl(x), level(l) {};
	};

	unsigned int depth;
	Node* root;

public:
	Tree() : root(NULL) { };

	void build(std::istringstream&);

	// visits every node from certain root
	// cb - callback
	void visitsubtree(Node*, const std::function<void(Node*)> cb);
	void visit(const std::function<void(Node*)> cb);

	// finds a node starting from certain root
	// or returns false/NULL
	Node* find(Node* root, const T what) const;
};


template <typename T>
void Tree<T>::visitsubtree(Node* root, const std::function<void(Node*)> cb) {
	if (!root) return;
	cb(root);
	if (root->children.size()) {
		for (auto n : root->children) {
			visitsubtree(n, cb);
		}
	}
}

template <typename T>
void Tree<T>::visit(const std::function<void(Node*)> cb) {
	visitsubtree(root, cb);
};

// http://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
template <typename T> 
typename Tree<T>::Node* Tree<T>::find( Node* root, const T what) const {
	if (!root) return false;
	if (root->pl == what) return root;
	if (root->children.size()) {
		for (auto n : root->children) {
			auto r = find(n, what);
			if (r) return r;
		}
	}
	return false;
}

template <typename T>
void Tree<T>::build( std::istringstream& iss) {
	std::string buf;
	while (getline(iss, buf)) {
		if (buf.size() == 0) break;		// eof
		if (buf[0] == '=') break;		// end of treedef
		char parent;
		size_t cnt;
		Node* where;
		std::istringstream il(buf);
	
		// read the parent id
		il >> parent >> cnt;

		// find the node in the tree 
		// or effectively create the tree
		if (root) {
			where = this->find(root, parent);
		} else {
			where = root = new Node(parent);
		}

		while (cnt--) {
			char el;
			il >> el;
			where->children.push_back(
				new Node(el, where->level + 1));
		}
	}
}

#include <map>

typedef Tree<char>::Node treeenode;
typedef std::list < treeenode* > nodelist;

nodelist& operator << (nodelist &res, nodelist& from) {
	res.insert(res.begin(), from.begin(), from.end());
	return res;
}

std::ostream& operator << (std::ostream &ostr, nodelist& from) {
	for (auto e : from) {
		ostr << e->pl; 
	}
	return ostr; 
}

void queries(std::istringstream& iss, Tree<char> &tree) {
	std::string buf;

	typedef std::function < nodelist(const std::string&) > operfun;
	typedef std::map < std::string, operfun> operations_map;

	operations_map ops;

	ops["LEVEL"] = [&tree](const std::string& pv) -> nodelist {
		nodelist res;
		int i = std::atoi(pv.c_str()); 
		tree.visit([i, &res](treeenode *el)->void{
			if (el->level == i) {
				res.push_back(el);
			}
		}); 
		return res;
	};

	ops["CHILDREN"] = [&tree](const std::string& pv) -> nodelist {
		nodelist res;

		tree.visit([&res, &pv](treeenode *el) -> void {
			if (pv[0] == el->pl) {
				res << el->children;
			}
		});
		return res;
	};

	while (getline(iss, buf)) {
		if (buf[0] == '?') {
			for (auto op: ops) {
				size_t pos;
				if (pos = buf.find(op.first) != std::string::npos) {
					std::cout << op.second(buf.substr(pos + op.first.length() + 2));
				}
			}
		};		// end of treedef
	}
}

int main() {
	int ncount = 0;

	const auto printer = [](Tree<char>::Node* n) -> void {
		std::cout << n->pl << ' ';
	};

	const auto nodeCounter = [&](Tree<char>::Node* n) -> void {
		ncount++;
	};

	//

	Tree<char> ctree;

	// build the tree
	std::istringstream iss(INPUT);
	ctree.build(iss);
	// process queries
	queries(iss, ctree);

	ctree.visit(printer);
	ctree.visit(nodeCounter);

	std::cout << " a total of " << ncount << " nodes " << std::endl;

	return 0;
}
