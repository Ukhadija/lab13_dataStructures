#include <iostream>
#include "Header.h"
using namespace std;

int main()
{
	AVL tree;
	AvlNode* root = tree.getRoot();
	root = tree.Insert(50, root);
	root = tree.Insert(10, root);
	root = tree.Insert(8, root);
	root = tree.Insert(20, root);
	root = tree.Insert(15, root);
	root = tree.Insert(60, root);
	tree.LevelOrder(root);

}