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
		Node* left, *right, *parent;

		Node(int key) : x(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

	}*root = nullptr, *pnode = nullptr;

	void insert(Node*& root, int key) {

		Node* newNode = new Node(key);

		if (root == nullptr) {
			root = newNode;
			root->color = BLACK;

			root->left = pnode;
			root->right = pnode;

			return;
		}

		Node* cur = root;
		Node* parent = nullptr;

		while (cur != pnode){   // Ищем

			parent = cur;

			if (key < cur->x) { cur = cur->left;}

			else if (key > cur->x) {cur = cur->right;}

			else {delete newNode;return;}

		}

		newNode->parent = parent; // Вставляем
		if (key < parent->x) {
			parent->left = newNode;
		}
		else { parent->right = newNode; }

		newNode->left = pnode;
		newNode->right = pnode;

		fixInsert(root, newNode);

	}

	void fixInsert(Node*& root, Node* node) {

		while (node != root && node->parent->color == RED) {

			Node* parent = node->parent;
			Node* gparent = parent->parent;

			if (gparent == nullptr) {
				break;
			}

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

						parent = node->parent;
						if (parent == nullptr) break;

						gparent = parent->parent;
						if (gparent == nullptr) break;
					}

					// Случай 3C: Линия
					parent->color = BLACK;
					gparent->color = RED;
					rightRotate(root, gparent);
					break;
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

						parent = node->parent;
						if (parent == nullptr) break;

						gparent = parent->parent;
						if (gparent == nullptr) break;
					}

					// Случай 3C: Линия
					parent->color = BLACK;
					gparent->color = RED;
					leftRotate(root, gparent);
					break;
				}
			}
		}
		root->color = BLACK;
	}

	void leftRotate(Node*& root, Node* node) {

		Node* tmp = node->right;    // новый "корень" после поворота
		node->right = tmp->left;    // перемещаем левое поддерево y

		if (tmp->left != pnode) {
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

		if (tmp->right != pnode) {
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

	void remove(Node*& root, int key) {

		if (root == nullptr) { return; }

		Node* cur = root;
		Node* parent = nullptr;

		while (cur->x != key && cur != pnode) {   // Ищем
			parent = cur;
			if (key < cur->x)
				cur = cur->left;
			else cur = cur->right; 
		}

		if (cur == pnode) return;

		//Случай 0, Дети черные псевдоузлы

		if (cur->left == pnode && cur->right == pnode) {

			if (parent == nullptr) {
				delete root; root = nullptr;
			}
			else {
				if (cur == parent->left) {
					parent->left = pnode;
				}
				else parent->right = pnode;

				if (cur->color == BLACK) {
					fixDelete(root, cur);
				}
				delete cur;
			}
			return;
		}

		// Случай 1 — Левый ребёнок - поддерево из более чем одного узла,
		// а правый является черным псевдоузлом

		if (cur->left != pnode && cur->right == pnode) {
			
			Node* child = cur->left;
			child->parent = cur->parent;

			if (parent == nullptr) {
				root = child;
			}
			else if (cur == parent->left) {
				parent->left = child;
			}
			else parent->right = child;

			if (cur->color == BLACK) {
				fixDelete(root, child);
			}

			delete cur;
		}

		// Случай 2 — Правый ребёнок - поддерево из более чем одного узла,
		// а левый является черным псевдоузлом

		else if (cur->right != pnode && cur->left == pnode) {

			Node* child = cur->right;
			child->parent = cur->parent;

			if (parent == nullptr) {
				root = child;
			}
			else if (cur == parent->left) {
				parent->left = child;
			}
			else parent->right = child;

			if (cur->color == BLACK) {
				fixDelete(root, child);
			}
			delete cur;
		}

		// Случай 3 — Оба ребёнка

		else {

			Node* minNode = findMin(cur->right);

			Color curColor = cur->color;     
			Color minColor = minNode->color;  
			int minValue = minNode->x;

			remove(root, minValue);

			cur->x = minValue;
			cur->color = curColor;

			//if (minColor == BLACK) {
			//	fixDelete(root, cur);
			//}
		}

	}

	Node* findMin(Node* root) {

		if (root == nullptr || root == pnode) return nullptr;

		while (root->left != pnode) {
			root = root->left;
		}
		return root;
	}

	void fixDelete(Node*& root, Node* node) {

		while (node != root && (node == pnode || node->color == BLACK)) {

			Node* parent = node->parent;

			if (node == parent->left) {
				node = fixDeleteLeft(root, node, parent);
				if (node == root) break;  // Завершаем если дошли до корня
			}
			else {
				node = fixDeleteRight(root, node, parent);
				if (node == root) break;  // Завершаем если дошли до корня
			}
		}

		if (node != pnode) {
			node->color = BLACK;
		}
	}

	Node* fixDeleteLeft(Node*& root, Node* node, Node* parent) {

		Node* brat = parent->right;
		if (brat == pnode) return parent;

		// СЛУЧАЙ 1: Брат КРАСНЫЙ
		if (brat->color == RED) {
			brat->color = BLACK;
			parent->color = RED;
			leftRotate(root, parent);
			brat = parent->right;
			if (brat == pnode) return parent;
		}
		// Перепроверяем цвета детей нового брата
		bool leftChildBlack = (brat->left == pnode) || (brat->left->color == BLACK);
		bool rightChildBlack = (brat->right == pnode) || (brat->right->color == BLACK);
		
		//СЛУЧАЙ 2: Оба ребенка брата ЧЕРНЫЕ
		if (leftChildBlack && rightChildBlack) {
			brat->color = RED;
			return parent;
		}
		else {
			//СЛУЧАЙ 3: Правый ребенок брата ЧЕРНЫЙ, левый - КРАСНЫЙ
			if (rightChildBlack) {
				if (brat->left != pnode) brat->left->color = BLACK;
				brat->color = RED;
				rightRotate(root, brat);
				brat = parent->right;
				if (brat == pnode) return parent;

				leftChildBlack = (brat->left == pnode) || (brat->left->color == BLACK);
				rightChildBlack = (brat->right == pnode) || (brat->right->color == BLACK);
			}

			// СЛУЧАЙ 4: Правый ребенок брата КРАСНЫЙ
			brat->color = parent->color;
			parent->color = BLACK;

			if (brat->right != pnode) brat->right->color = BLACK;
			leftRotate(root, parent);

			return root;  // Возвращаем корень - цикл завершится
		}
	}

	Node* fixDeleteRight(Node*& root, Node* node, Node* parent) {

		Node* brat = parent->left;
		if (brat == pnode) return parent;

		//СЛУЧАЙ 1: Брат КРАСНЫЙ
		if (brat->color == RED) {
			brat->color = BLACK;
			parent->color = RED;
			rightRotate(root, parent);
			brat = parent->left;
			if (brat == pnode) return parent;
		}

		bool leftChildBlack = (brat->left == pnode) || (brat->left->color == BLACK);
		bool rightChildBlack = (brat->right == pnode) || (brat->right->color == BLACK);

		// СЛУЧАЙ 2: Оба ребенка брата ЧЕРНЫЕ
		if (leftChildBlack && rightChildBlack) {
			brat->color = RED;
			return parent;
		}
		else {
			//СЛУЧАЙ 3: Левый ребенок брата ЧЕРНЫЙ, правый - КРАСНЫЙ
			if (leftChildBlack) {
				if (brat->right != pnode) brat->right->color = BLACK;
				brat->color = RED;
				leftRotate(root, brat);
				brat = parent->left;
				if (brat == pnode) return parent;

				leftChildBlack = (brat->left == pnode) || (brat->left->color == BLACK);
				rightChildBlack = (brat->right == pnode) || (brat->right->color == BLACK);
			}

			// СЛУЧАЙ 4: Левый ребенок брата КРАСНЫЙ
			brat->color = parent->color;
			parent->color = BLACK;

			if (brat->left != pnode) brat->left->color = BLACK;
			rightRotate(root, parent);

			return root;
		}
	}

	void printTree(Node* root, string indent = "", bool last = true) {

		if (root == nullptr) return;

		cout << indent;
		if (last) {
			cout << "L--- ";
			indent += "     ";
		}
		else {
			cout << "|--- ";
			indent += "|    ";
		}

		if (root == pnode) {
			cout << "PNode (BLACK)" << endl;
			return;
		}

		string color = (root->color == RED) ? "RED" : "BLACK";
		cout << root->x << " (" << color << ")" << endl;

		printTree(root->right, indent, false);
		printTree(root->left, indent, true);
	}

	void deleteTree(Node* root) {

		if (root == nullptr) return;

		if (root != pnode) {
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}

public:

	RBT() {
		pnode = new Node(0);
		pnode->color = BLACK;
	}

	~RBT() {
		deleteTree(root);
		delete pnode;
	}

	void remove(int key) {
		remove(root, key);
	}
	
	void printTree() {
		printTree(root, "", true);
	}

	Node* getRoot() const {
		if (root == nullptr) return 0;
		else return root;
	}

	void insert(int key) {
		insert(root, key);
	}
};