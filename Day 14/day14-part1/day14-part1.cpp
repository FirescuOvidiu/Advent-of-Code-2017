#include "../../AOCHeaders/stdafx.h"


std::vector<int> readInput(std::fstream& in)
{
	std::string line;
	std::getline(in, line);

	return std::vector<int> { std::begin(line), std::end(line) };
}


std::string day10_part2(std::vector<int> lengths, const std::string digit)
{
	const int listSize = 256;
	std::array<int, listSize> list;
	int forward{ 0 }, backwards{ 0 }, skip{ 0 }, denseHash{ 0 };
	std::stringstream ss;

	std::iota(std::begin(list), std::end(list), 0);
	
	lengths.insert(std::end(lengths), std::begin(digit), std::end(digit));
	lengths.insert(std::end(lengths), { 17, 31, 73, 47, 23 });

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
			ss << 0;
		}
		ss << std::hex << denseHash;
	}

	return ss.str();
}


std::string hexToBin(const std::string& hex)
{
	std::string bin;
	int number{ 0 };

	for (const auto& el : hex)
	{
		number = el <= '9' ? (el - '0') : (10 + el - 'a');

		for (int it = 3; it >= 0; it--)
		{
			bin += number & (1 << it) ? '1' : '0';
		}
	}

	return bin;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> lengths = readInput(in);
	std::array<std::string, 128> hexa, bin;
	int countSquares{ 0 };

	lengths.push_back('-');

	for (int it = 0; it <= 127; it++)
	{
		hexa[it] = day10_part2(lengths, std::to_string(it));
		bin[it] = hexToBin(hexa[it]);
	}

	for (const auto& el : bin)
	{
		countSquares += std::count(std::begin(el), std::end(el), '1');
	}

	out << countSquares;

	in.close();
	out.close();
}