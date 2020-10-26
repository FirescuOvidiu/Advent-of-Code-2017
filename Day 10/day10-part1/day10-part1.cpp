#include "../../AOCHeaders/stdafx.h"


std::vector<int> readInput(std::fstream& in)
{
	std::vector<int> lengths;
	int number{ 0 };
	char c{};

	while (in >> number >> c)
	{
		lengths.push_back(number);
	}
	lengths.push_back(number);

	return lengths;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	const int listSize = 256;
	std::vector<int> lengths = readInput(in);
	std::array<int, listSize> list;
	int forward{ 0 }, backwards{ 0 }, skip{ 0 };

	std::iota(std::begin(list), std::end(list), 0);

	for (const auto lenght : lengths)
	{
		std::reverse(std::begin(list), std::begin(list) + lenght);
		forward = (lenght + skip++) % listSize;
		backwards += forward;
		std::rotate(std::begin(list), std::begin(list) + forward, std::end(list));
	}

	backwards = backwards % listSize;
	std::rotate(std::begin(list), std::end(list) - backwards, std::end(list));

	out << list[0] * list[1];

	in.close();
	out.close();
}