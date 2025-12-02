#include "user_comms.h"
#include "BST.h"
#include "AVL.h"
#include "RBT.h"
#include "Func.h"

int main() {

	setlocale(LC_ALL, "Ru");
    
	cout << "Введите тип дерева для работы (1 - BST, 2 - AVL, 3 - RBT): ";
	int x; cin >> x;

	switch (x) {
		case 1: {
			cout << "\nBST TREE-------------------------------------\n\n";

			BST bst;

			cout << "1 - Сгенерировать дерево, 2 - Ввести вручную: "; int tmp; cin >> tmp;
			if (tmp == 2) {
				fillBST(bst);
				showTreeInfo(bst);
				addElBST(bst);
				removeElBST(bst);
				bst.printTree();
				cout << "\nВысота: " << maxDepth(bst.getRoot()) << endl;
			}
			else if (tmp == 1) { createData(bst); bst.printTree(); cout << "\nДанные занесены в таблицу в файле data.txt\n"; }

			else {
				cout << "\nОшибка!\n"; return 0;
			}
			break;
		}
		case 2: {
			cout << "\nAVL TREE-------------------------------------\n\n";

			AVL avl;

			cout << "1 - Сгенерировать дерево, 2 - Ввести вручную: "; int tmp; cin >> tmp;
			if (tmp == 2) {
				fillAVL(avl);
				cout << "\nСтруктура дерева:\n\n"; avl.printTree();
				addElAVL(avl);
				cout << "\nСтруктура дерева:\n\n"; avl.printTree();
				removeElAVL(avl);
				cout << "Структура дерева:\n\n"; avl.printTree();
				cout << "\nВысота: " << maxDepth(avl.getRoot()) << endl;
			}
			else if (tmp == 1) {createData(avl); avl.printTree(); cout << "\nДанные занесены в таблицу в файле data.txt\n";}

			else {
				cout << "\nОшибка!\n"; return 0;
			}

			break;
		}
		case 3: {
			cout << "\nRBT TREE-------------------------------------\n\n";

			RBT rbt;

			cout << "1 - Сгенерировать дерево, 2 - Ввести вручную: "; int tmp; cin >> tmp;
			if (tmp == 2) {
				fillRBT(rbt);
				cout << "\nСтруктура дерева:\n\n";
				rbt.printTree();
				addElRBT(rbt);
				cout << "\nСтруктура дерева:\n\n";
				rbt.printTree();
				removeElRBT(rbt);
				cout << "\nСтруктура дерева:\n\n";
				rbt.printTree();
				cout << "\nВысота: " << maxDepth(rbt.getRoot()) << endl;
			}

			else if (tmp == 1) {createData(rbt); rbt.printTree(); cout << "\nДанные занесены в таблицу в файле data.txt\n";}

			else {
				cout << "\nОшибка!\n"; return 0;
			}

			break;
		}
		default: cout << "\nОшибка выбора!\n"; return 1;
	}

	return 0;
}