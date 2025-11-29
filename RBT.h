#pragma once
#include <iostream>
using namespace std;

class RBT {

	enum Color {
		RED,
		BLACK
	};

	struct Node {

		int x;
		Color color;
		Node* left;
		Node* right;
		Node* parent;

		Node(int key) : x(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

	} *root = nullptr;

	void insert(Node*& root, int key) {

		Node* newNode = new Node(key);

		if (root == nullptr) {
			root = newNode;
			root->color = BLACK;
			return;
		}

		Node* cur = root;
		Node* parent = nullptr;

		// Ищем

		while (cur != nullptr) {

			parent = cur;

			if (key < cur->x) {
				cur = cur->left;
			}
			else if (key > cur->x) {
				cur = cur->right;
			}
			else {
				delete newNode;
				return;
			}
		}

		// Вставляем
		newNode->parent = parent;
		if (key < parent->x) {
			parent->left = newNode;
		}
		else { parent->right = newNode; }

		fixInsert(root, newNode);

	}

	void fixInsert(Node*& root, Node* node) {

		while (node != root && node->parent->color == RED) {
			Node* parent = node->parent;
			Node* gparent = parent->parent;

			if (parent == gparent->left) {

				Node* uncle = gparent->right;

				// Случай 3A: Дядя красный
				if (uncle != nullptr && uncle->color == RED) {
					parent->color = BLACK;
					uncle->color = BLACK;
					gparent->color = RED;
					node = gparent;  // Поднимаемся выше
				}
				else {
					// Случай 3B: Треугольник
					if (node == parent->right) {
						node = parent;
						leftRotate(root, node);
					}

					// Случай 3C: Линия
					parent->color = BLACK;
					gparent->color = RED;
					rightRotate(root, gparent);
				}
			}
			else {
				// Симметричный случай для правой стороны
				Node* uncle = gparent->left;

				// Случай 3A: Дядя красный
				if (uncle != nullptr && uncle->color == RED) {
					parent->color = BLACK;
					uncle->color = BLACK;
					gparent->color = RED;
					node = gparent;
				}
				else {
					// Случай 3B: Треугольник
					if (node == parent->left) {
						node = parent;
						rightRotate(root, node);
					}

					// Случай 3C: Линия
					parent->color = BLACK;
					gparent->color = RED;
					leftRotate(root, gparent);
				}
			}
		}
		root->color = BLACK;
	}

	void leftRotate(Node*& root, Node* node) {

		Node* tmp = node->right;    // новый "корень" после поворота
		node->right = tmp->left;    // перемещаем левое поддерево y

		if (tmp->left != nullptr) {
			tmp->left->parent = node;  // обновляем родителя
		}

		tmp->parent = node->parent;    // переносим родителя

		// Обновляем ссылку у родителя x
		if (node->parent == nullptr) {
			root = tmp;             // x был корнем
		}
		else if (node == node->parent->left) {
			node->parent->left = tmp;  // x был левым ребенком
		}
		else {
			node->parent->right = tmp; // x был правым ребенком
		}

		tmp->left = node;    // x становится левым ребенком y
		node->parent = tmp;  // обновляем родителя x
	}

	void rightRotate(Node*& root, Node* node) {
		Node* tmp = node->left;     // новый "корень" после поворота
		node->left = tmp->right;    // перемещаем правое поддерево x

		if (tmp->right != nullptr) {
			tmp->right->parent = node;  // обновляем родителя
		}

		tmp->parent = node->parent;    // переносим родителя

		// Обновляем ссылку у родителя y
		if (node->parent == nullptr) {
			root = tmp;             // y был корнем
		}
		else if (node == node->parent->left) {
			node->parent->left = tmp;  // y был левым ребенком
		}
		else {
			node->parent->right = tmp; // y был правым ребенком
		}

		tmp->right = node;   // y становится правым ребенком x
		node->parent = tmp;  // обновляем родителя y
	}

	void print(Node* root) {

		if (root == nullptr) return;

		print(root->left);
		cout << root->x << " " << ((root->color==RED)?"RED":"BLACK") << endl;
		print(root->right);

	}

public:

	int getRoot() {
		return root->x;
	}

	void insert(int key) {
		insert(root, key);
	}
	void print() {
		print(root);
	}
};