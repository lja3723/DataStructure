#include "list.h"
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

int main()
{
	List<int> list;
	cout << list.size() << endl;
	list.add_last(3);
	cout << list.size() << endl;
	return 0;
}