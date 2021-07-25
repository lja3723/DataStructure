#include "list.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <Windows.h>

using std::cout;
using std::endl;

int main()
{
	List<std::string> list;

	std::string words[] = {
		"capacity",
		"lower",
		"macintochi",
		"bistonic",
		"navy",
		"level",
		"coinsident",
		"medic",
		"harmful",
		"digit",
		"gravity",
		"windstorm"
	};
	int wordsSize = sizeof(words) / sizeof(*words);

	for (int i = 0; i < wordsSize; i++)
		if ((i + 1) % 4 == 0)
			list.add_first(words[i]);
		else
			list.add_last(words[i]);

	while (list.isNextDataExist())
	{
		cout << list.getNextData() << " ";
	}
	cout << "\n\n";

	while (1)
	{
		char c = getchar();

		if (c == 'c')
		{
			if (list.isPrevDataExist())
			{
				list.getPrevData();
				//list.
			}
		}

		if (c == 'v')
		{

		}

		list.iterReset();
		list.printIterNode();
		while (list.isNextDataExist())
		{
			list.getNextData();
			list.printIterNode();
		}
	}
	return 0;
}  