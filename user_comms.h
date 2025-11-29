#pragma once
#include "BST.h"
#include "AVL.h"
#include "RBT.h"

void fillBST(BST& bst);
void showTreeInfo(BST& bst);
void addElBST(BST& bst);
void removeElBST(BST& bst);

void fillAVL(AVL& avl);
void addElAVL(AVL& avl);
void removeElAVL(AVL& avl);

void fillRBT(RBT& rbt);
void addElRBT(RBT& rbt);