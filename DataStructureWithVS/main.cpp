#include "list.h"
#include <iostream>
#include <cstdio>
#include <string>

using std::cout;
using std::endl;

int main()
{
	List<int> list;

	for (int i = 0; i < 30; i++)
		if ((i + 1) % 7 == 0)
			list.add_first(i + 1);
		else
			list.add_last(i + 1);

	while (list.isNextDataExist())
	{
		cout << list.getNextData() << " ";
		//if (list.peek_prevAccessedData() % 4 == 0)
			//list.delete_prevAccessedData();
	}

	//cout << endl << list.size() << endl;

	//list.iterReset();
	//while (list.isNextDataExist())
	//{
	//	cout << list.getNextData() << " ";
	//}
	return 0;
}  