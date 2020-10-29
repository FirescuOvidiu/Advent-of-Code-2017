#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int spinlock{ 0 }, pos{ 0 }, valueAfterZero{ 0 };

	in >> spinlock;

	for (int value = 1; value <= 50000000; value++)
	{
		pos = (pos + spinlock) % value + 1;
		if (pos == 1)
		{
			valueAfterZero = value;
		}
	}

	out << valueAfterZero;

	in.close();
	out.close();
}