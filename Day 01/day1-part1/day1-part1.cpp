#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	char first{}, second{}, auxFirst{};
	int sum = 0;

	in >> first;
	auxFirst = first;

	while (in >> second)
	{
		if (first == second)
		{
			sum += second - '0';
		}
		first = second;
	}

	if (auxFirst == first)
	{
		sum += first - '0';
	}

	out << sum;

	in.close();
	out.close();
}