#include "user_comms.h"
#include "BST.h"
#include "AVL.h"
#include "RBT.h"

int main() {

	setlocale(LC_ALL, "Ru");

    BST bst;
	AVL avl;
	RBT rbt;
    
	//cout << "\BST TREE---------------------------------\n\n";

 //   fillBST(bst);
 //   showTreeInfo(bst);
 //   addElBST(bst);
 //   removeElBST(bst);
	//bst.print();

	//cout << "\nAVL TREE---------------------------------\n\n";

	//fillAVL(avl);
	//addElAVL(avl);
	//removeElAVL(avl);
	//avl.print();

	cout << "\RBT TREE---------------------------------\n\n";

	fillRBT(rbt);
	rbt.print();
	addElRBT(rbt);
	rbt.print();

	cout << rbt.getRoot();

	return 0;
}