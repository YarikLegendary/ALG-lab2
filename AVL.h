#pragma once
#include <iostream>
using namespace std;

class AVL {

	struct Node {

		int x;
		int height;
		Node* left, *right;

		Node(int key) : x(key), height(1), left(nullptr), right(nullptr) {}

		~Node() {
			//if (left) delete left;
			//if (right) delete right;
		}
	} *root = nullptr;

	unsigned height(Node* root) {
		return root ? root->height : 0;
	}

	void fixheight(Node* root)
	{
		if (!root) return;

		unsigned hl = height(root->left);
		unsigned hr = height(root->right);
		root->height = (hl > hr ? hl : hr) + 1;
	}

	int bfactor(Node* root) {

		if (!root) return 0;

		return height(root->left) - height(root->right);
	}

	Node* rotateright(Node* root) {

		if (!root || !root->left) return root;

		Node* newRoot = root->left;
		root->left = newRoot->right;
		newRoot->right = root;

		fixheight(root);
		fixheight(newRoot);

		return newRoot;

	}

	Node* rotateleft(Node* root) {

		if (!root || !root->right) return root;

		Node* newRoot = root->right;
		root->right = newRoot->left;
		newRoot->left = root;

		fixheight(root);
		fixheight(newRoot);

		return newRoot;
	}

	Node* balance(Node* root) {

		if (!root) return nullptr;

		fixheight(root);

		if (bfactor(root) > 1) {

			if (bfactor(root->left) < 0) {
				root->left = rotateleft(root->left);
			}
			return rotateright(root);
		}

		if (bfactor(root) < -1) {

			if (bfactor(root->right) > 0) {
				root->right = rotateright(root->right);
			}
			return rotateleft(root);
		}
		return root;
	}

	void insert(Node*& root, int key) {

		if (!root) {
			root = new Node(key); return;
		}
		if (key > root->x) {
			insert(root->right, key);
		}
		else {
			insert(root->left, key);
		}
		root = balance(root);
	}

	Node* findMin(Node* root) {

		if (!root) return nullptr;

		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}

	Node* removemin(Node* root)
	{
		if (!root) return nullptr;

		if (root->left == nullptr)
			return root->right;
		root->left = removemin(root->left);
		return balance(root);
	}

	Node* remove(Node* root, int key) {

		if (!root) return nullptr;

		if (key < root->x) {
			root->left = remove(root->left, key);
		}
		else if (key > root->x) root->right = remove(root->right, key);

		else
		{
			Node* lt = root->left;
			Node* rt = root->right;

			delete root;

			if (!rt) return lt;

			Node* min = findMin(rt);

			min->right = removemin(rt);
			min->left = lt;
			return balance(min);

		}
		return balance(root);
	}

	void print(Node* root) {

		if (root == nullptr) return;

		print(root->left);
		cout << root->x << endl;
		print(root->right);

	}

public:
	void insert(int key) {
		insert(root, key);
	}
	void remove(int key) {
		root = remove(root, key);
	}
	void print() {
		print(root);
	}
};