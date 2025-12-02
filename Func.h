#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

template <typename T>
int maxDepth(T* root) {
    
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    return 1 + max(leftDepth, rightDepth);
}

template <typename TreeType>
void createData(TreeType& tree) {

    srand(time(nullptr));

    ofstream f("data.txt");
    if (!f) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }
    f << "Высота      Количество элементов" << endl;
    f << "----------------------------------" << endl;

    int start = 1, end = 100000, value = 0, height = 1;
    unsigned N = 0;

	for (int i = 0; i < 100; i++) {

        for (int step = 0; step < 100; step++) {
            value = rand() % (end - start + 1) + start;
            tree.insert(value); N++;
        }
        height = maxDepth(tree.getRoot());

        f << height;
        if ((height - 10) < 0) f << " ";
        f << "       |        " << N << endl;;
	}
    f.close();
}