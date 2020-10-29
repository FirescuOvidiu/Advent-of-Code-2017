#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> values{ 0 };
	int spinlock{ 0 }, pos{ 0 };

	in >> spinlock;

	for (int value = 1; value <= 2017; value++)
	{
		pos = (pos + spinlock) % values.size() + 1;
		values.insert(std::begin(values) + pos, value);
	}

	out << values[(pos + 1) % values.size()];

	in.close();
	out.close();
}