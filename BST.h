#pragma once
#include <iostream>
using namespace std;

class BST {

	struct Node {

		int x;
		Node* left, *right;

		Node(int key) : x(key), left(nullptr), right(nullptr) { }

		~Node() {
			if (left) delete left;
			if (right) delete right;
		}
	} *root = nullptr;

	void insert(Node*& root, int key) {

		if (exists(root, key)) return;
		if (root == nullptr) { root = new Node(key); return; }
		if (key < root->x) insert(root->left, key);
		if (key > root->x) insert(root->right, key);
	}

	bool exists(Node* root, int key) {

		if (root == nullptr) return false;

		if (root->x == key) return true;

		if (key < root->x) return exists(root->left, key);

		return exists(root->right, key);
	}

	void remove(Node*& root, int key) {

		if (root == nullptr) return;

		if (key < root->x) {
			remove(root->left, key);
		}
		else if (key > root->x) {
			remove(root->right, key);

		}
		else {

			if (root->left == nullptr && root->right == nullptr) remove_leaf(root); // 1 случай

			else if (root->left == nullptr || root->right == nullptr) remove_one_chld(root); // 2 случай

			else remove_two_chld(root); // 3 случай
		}
	}

	void remove_leaf(Node*& root) {
		delete root;
		root = nullptr;
	}
	void remove_one_chld(Node*& root) {

		Node* tmp = root;

		if (root->left != nullptr) root = root->left;
		else root = root->right;

		tmp->left = nullptr;
		tmp->right = nullptr;
		delete tmp;
	}
	void remove_two_chld(Node*& root) {

		Node* maxNode = findMax(root->left);

		root->x = maxNode->x;

		remove(root->left, maxNode->x);

	}

	void print(Node* root) {

		if (root == nullptr) return;

		print(root->left);
		cout << root->x << endl;
		print(root->right);

	}

	Node* findMax(Node* root) {

		if (root == nullptr) return 0;
		while (root->right != nullptr) {
			root = root->right;
		}
		return root;
	}
	Node* findMin(Node* root) {

		if (root == nullptr) return 0;
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}

	struct QueueNode {
		Node* treeNode;        // узел дерева
		QueueNode* next;       // следующий элемент очереди

		QueueNode(Node* node) : treeNode(node), next(nullptr) {}
	};
	void BFS(Node* root) {

		if (root == nullptr) return;

		// Создаем простую очередь через связный список
		QueueNode* front = new QueueNode(root);
		QueueNode* rear = front;

		while (front != nullptr) {

			// Извлекаем из начала
			Node* current = front->treeNode;
			QueueNode* temp = front;
			front = front->next;

			cout << current->x << " ";

			// Добавляем потомков в конец
			if (current->left != nullptr) {
				QueueNode* newNode = new QueueNode(current->left);
				if (front == nullptr) {
					front = rear = newNode;
				}
				else {
					rear->next = newNode;
					rear = newNode;
				}
			}

			if (current->right != nullptr) {
				QueueNode* newNode = new QueueNode(current->right);
				if (front == nullptr) {
					front = rear = newNode;
				}
				else {
					rear->next = newNode;
					rear = newNode;
				}
			}

			delete temp;  // освобождаем память узла очереди
		}
	}

	void deep_trav(Node* node) {
		if (node == nullptr) return;

		deep_trav(node->left);   // Сначала левая ветка
		cout << node->x << " ";       // Потом текущий узел
		deep_trav(node->right);  // Затем правая ветка
	}

	void preorder_trav(Node* node) {
		if (node == nullptr) return;
		cout << node->x << " ";
		preorder_trav(node->left);
		preorder_trav(node->right);
	}

	void postorder_trav(Node* node) {
		if (node == nullptr) return;

		postorder_trav(node->left);
		postorder_trav(node->right);
		cout << node->x << " ";
	}

	void inorder_trav(Node* node) {
		if (node == nullptr) return;

		inorder_trav(node->left);
		cout << node->x << " ";
		inorder_trav(node->right);
	}

public:
	void insert(int key) {
		insert(root, key);
	}
	void print() {
		print(root);
	}
	void remove(int key) {
		remove(root, key);
	}
	int printMax() {
		if (findMax(root))
			return findMax(root)->x;
		else return 0;
	}
	int printMin() {
		if (findMin(root))
			return findMin(root)->x;
		else return 0;
	}
	void printBFS() {
		BFS(root);
	}
	void printDeep() {
		deep_trav(root);
	}
	void printDirect() {
		preorder_trav(root);
	}
	void printReverse() {
		postorder_trav(root);
	}
	void printSymmetric() {
		inorder_trav(root);
		cout << endl;
	}
};