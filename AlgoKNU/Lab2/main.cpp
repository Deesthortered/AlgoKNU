#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<int> tree;

	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(6);
	tree.Insert(7);

	tree.Delete(4);

	for (size_t i = 1; i < 8; i++)
	{
		cout << tree.GetRank(i) << endl;
	}

	system("pause");
	return 0;
}