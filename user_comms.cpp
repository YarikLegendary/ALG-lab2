#include "user_comms.h"

void fillBST(BST& bst) {
    cout << "\nВведите элементы дерева (0 для завершения):\n" << endl;
    while (true) {
        int x; cin >> x;
        if (x == 0) break;
        bst.insert(x);
    }
}
void showTreeInfo(BST& bst) {
    cout << "\n"; cout << "BST ДЕРЕВО: \n" << endl;
    bst.printTree(); cout << endl;
    cout << "Наибольший элемент: " << bst.printMax() << endl; 
    cout << "Наименьший элемент: " << bst.printMin() << endl; cout << endl;
    cout << "Обход в ширину: "; bst.printBFS(); cout << endl; 
    cout << "Обход в глубину: "; bst.printDeep(); cout << endl; 
    cout << "Прямой обход: "; bst.printDirect(); cout << endl; 
    cout << "Обратный обход: "; bst.printReverse(); cout << endl; 
    cout << "Центрированный обход: "; bst.printSymmetric(); cout << endl;
}
void addElBST(BST& bst) {
    cout << "Вставить элемент: ";
    int a; cin >> a; bst.insert(a);
}
void removeElBST(BST& bst) {
    cout << "Удалить элемент: ";
    int b; cin >> b; bst.remove(b); cout << endl;
}

void fillAVL(AVL& avl) {
    cout << "\nВведите элементы дерева (0 для завершения):\n" << endl;
    while (true) {
        int x; cin >> x;
        if (x == 0) break;
        avl.insert(x);
    }
}
void addElAVL(AVL& avl) {
    cout << "\nВставить элемент: ";
    int a; cin >> a; avl.insert(a); 
}
void removeElAVL(AVL& avl) {
    cout << "\nУдалить элемент: ";
    int b; cin >> b; avl.remove(b); cout << endl;
}

void fillRBT(RBT& rbt) {
    cout << "\nВведите элементы дерева (0 для завершения):\n" << endl;
    while (true) {
        int x; cin >> x;
        if (x == 0) break;
        rbt.insert(x);
    }
}
void addElRBT(RBT& rbt) {
    cout << "\nВставить элемент: ";
    int a; cin >> a; rbt.insert(a);
}
void removeElRBT(RBT& rbt) {
    cout << "\nУдалить элемент: ";
    int b; cin >> b; rbt.remove(b); cout << endl;
}