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
		const auto [min, max] = std::minmax_element(std::begin(v), std::end(v));
		sum += *max - *min;
	}

	out << sum;

	in.close();
	out.close();
}