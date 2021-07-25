#include "list.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <Windows.h>

using std::cout;
using std::endl;

class OrderedString
{
public:
	std::string str;
	int order;
	OrderedString(std::string m_str = "", int m_order = 0)
		: str(m_str), order(m_order) {}

	OrderedString(const char* str) { this->str = str; }

	friend std::ostream& operator<<(std::ostream& os, const OrderedString& inst)
	{
		os << inst.order << ". " << inst.str << ";";
		return os;
	}
};

int order(const OrderedString& s1, const OrderedString& s2)
{
	return std::strcmp(s1.str.c_str(), s2.str.c_str());
}

int main()
{
	List<OrderedString> list(order);
	OrderedString words[] = {
		{"capacity",	1},
		{"lower",		2},
		{"macintochi",	3},
		{"bistonic",	4},
		{"navy",		5},
		{"level",		6},
		{"coinsident",	7},
		{"medic",		8},
		{"harmful",		9},
		{"digit",		10},
		{"gravity",		11},
		{"windstorm",	12}
	};
	int wordsSize = sizeof(words) / sizeof(*words);

	for (int i = 0; i < wordsSize; i++)
		if ((i + 1) % 4 == 0)
			list.addFirst(words[i]);
		else
			list.addLast(words[i]);

	cout << list << endl;

	list.setIterLast();
	while (list.isPrevDataExist())
	{
		list.getPrevData();
		list.printIterNode();
	}

	list.setIterFirst();
	while (list.isNextDataExist())
	{
		if (list.getNextData().str == "medic")
			list.removeAccessedData();
	}

	cout << list << endl;

	return 0;
}  