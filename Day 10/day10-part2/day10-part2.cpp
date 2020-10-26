#include "../../AOCHeaders/stdafx.h"


std::vector<int> readInput(std::fstream& in)
{
	std::string line;
	std::getline(in, line);

	std::vector<int> lengths{ std::begin(line),std::end(line) };
	lengths.insert(std::end(lengths), {17, 31, 73, 47, 23});

	return lengths;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	const int listSize = 256;
	std::vector<int> lengths = readInput(in);
	std::array<int, listSize> list;
	int forward{ 0 }, backwards{ 0 }, skip{ 0 }, denseHash{ 0 };

	std::iota(std::begin(list), std::end(list), 0);

	for (int countRounds = 0; countRounds < 64; countRounds++)
	{
		for (const auto lenght : lengths)
		{
			std::reverse(std::begin(list), std::begin(list) + lenght);
			forward = (lenght + skip++) % listSize;
			backwards += forward;
			std::rotate(std::begin(list), std::begin(list) + forward, std::end(list));
		}
	}

	backwards = backwards % listSize;
	std::rotate(std::begin(list), std::end(list) - backwards, std::end(list));


	for (forward = 0; forward < listSize; forward += 16)
	{
		denseHash = list[forward];
		for (int it = forward + 1; it < forward + 16; it++)
		{
			denseHash ^= list[it];
		}

		if (denseHash < 16)
		{
			out << 0;
		}
		out << std::hex << denseHash;
	}

	in.close();
	out.close();
}