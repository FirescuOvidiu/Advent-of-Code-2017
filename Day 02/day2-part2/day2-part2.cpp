#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string line{};
	int sum = 0;

	while (std::getline(in, line))
	{
		std::istringstream  iss{ line };
		const std::vector<int> v(std::istream_iterator<int>(iss), {});

		for (int first = 0; first < v.size() - 1; first++)
		{
			for (int second = first + 1; second < v.size(); second++)
			{
				if (v[first] % v[second] == 0 || v[second] % v[first] == 0)
				{
					sum += v[first] > v[second] ? v[first] / v[second] : v[second] / v[first];
					first = v.size();
					second = v.size();
				}
			}
		}
	}

	out << sum;

	in.close();
	out.close();
}