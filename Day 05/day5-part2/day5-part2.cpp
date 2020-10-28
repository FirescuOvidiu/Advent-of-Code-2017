#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> v(std::istream_iterator<int>{in}, {});
	int steps{ 0 }, pos{ 0 }, size = v.size();

	while ((pos >= 0) && (pos < size))
	{
		if (v[pos] < 3)
		{
			pos += v[pos]++;
		}
		else
		{
			pos += v[pos]--;
		}
		steps++;
	}

	out << steps;

	in.close();
	out.close();
}