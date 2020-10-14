#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<char> v(std::istream_iterator<char>(in), {});
	int size = v.size(), offset = v.size() / 2, sum = 0;

	for (int it = 0; it < size; it++)
	{
		if (v[it] == v[(it + offset) % size])
		{
			sum += v[it] - '0';
		}
	}

	out << sum;

	in.close();
	out.close();
}