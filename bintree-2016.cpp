// sdp-16-12-2016.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


struct Node {
	Node *left, *right;
	Node *parent;
	int key;
	int value;
	Node(int k, int v) {
		key = k; 	value = v;
		left = right = NULL;
		parent = NULL;
	}

	Node& operator =(Node& b) {
		Node &a = *this;
		a.key = b.key;
		a.value = b.value;

		return *this;
	}
};


Node* insert(Node*& root, Node *parent, int key, int value) {
	if (!root) {
		root = new Node(key, value);
		root->parent = parent;
	}

	else if (key < root->key)
		root->left = insert(root->left, root, key, value);
	else  // key >= root->key
		root->right = insert(root->right, root, key, value);
	return root;
}

Node* find_min(Node* root) {
	if (!root) return NULL;

	if (root->left)
		return find_min(root->left);

	return root;
}

/*
def replace_node_in_parent(self, new_value=None):
    if self.parent:
        if self == self.parent.left_child:
            self.parent.left_child = new_value
        else:
            self.parent.right_child = new_value
    if new_value:
        new_value.parent = self.parent
		*/

void replace_node_in_parent(Node* root, Node *nv) {
	if (root->parent) {
		if (root == root->parent->left) {
			root->parent->left = nv;
		}
		else {
			root->parent->right = nv;
		}
	}

	if (nv) {
		nv->parent = root->parent;
	}
}

void del(Node* root, int key) {

	// find the one to delete

	if (key < root->key)
		return del(root->left, key);
	if (key > root->key)
		return del(root->right, key);

	// ...

	if (root->left && root->right) {
		Node *succ = find_min(root->right);
		*root = *succ;

		return del(root, succ->key);
	}
	else if (root->left) {
		replace_node_in_parent(root, root->left);
	}
	else if (root->right) {
		replace_node_in_parent(root, root->right);
	}
	else {
		replace_node_in_parent(root, NULL);
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	Node* root = NULL;

	insert(root, NULL, 10, 10);
	insert(root, NULL, 2, 2);
	insert(root, NULL, 13, 13);
	insert(root, NULL, 4, 4);
	insert(root, NULL, 3, 3);
	insert(root, NULL, 41, 41);
	insert(root, NULL, 5, 5);
	insert(root, NULL, 6, 6);

	del(root, 4);

	return 0;
}

