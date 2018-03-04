#include <iostream>
#include <vector>
#include "BinominalHeap.h"
using namespace std;

int main()
{
	spaceBinominalHeap::BinominalHeap<int> heap;
	
	for (int i = 0; i < 10; i++)
		heap.Insert(i);

	while (!heap.IsEmpty())
		cout << heap.ExtractMin() << endl;

	system("pause");
	return 0;
}