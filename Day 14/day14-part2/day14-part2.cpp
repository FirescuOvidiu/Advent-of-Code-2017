#include "../../AOCHeaders/stdafx.h"


struct Coordinate
{
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	int x, y;
};


std::vector<int> readInput(std::fstream& in)
{
	std::string line;
	std::getline(in, line);

	return std::vector<int> { std::begin(line), std::end(line) };
}


std::string day10_part2(std::vector<int> lengths, const std::string number)
{
	const int listSize = 256;
	std::array<int, listSize> list;
	int forward{ 0 }, backwards{ 0 }, skip{ 0 }, denseHash{ 0 };
	std::stringstream ss;

	std::iota(std::begin(list), std::end(list), 0);

	lengths.insert(std::end(lengths), std::begin(number), std::end(number));
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


void markRegion(std::array<std::array < int, 128>, 128>& regions, const int startX, const int startY, const int regionNumber)
{
	std::vector<int> dx{ -1,0,1,0 }, dy{ 0,-1,0,1 };
	std::queue<Coordinate> coord;
	Coordinate curr;
	int x{ 0 }, y{ 0 };

	coord.push({ startX,startY });
	regions[startX][startY] = regionNumber;

	while (!coord.empty())
	{
		curr = coord.front();
		coord.pop();

		for (int k = 0; k < 4; k++)
		{
			x = curr.x + dx[k];
			y = curr.y + dy[k];

			if ((x < 0) || (y < 0) || (x > 127) || (y > 127))
			{
				continue;
			}

			if (regions[x][y] == 0)
			{
				coord.push({ x ,y });
				regions[x][y] = regionNumber;
			}
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> lengths = readInput(in);
	std::array<std::string, 128> hexa, bin;

	lengths.push_back('-');

	for (int it = 0; it < 128; it++)
	{
		hexa[it] = day10_part2(lengths, std::to_string(it));
		bin[it] = hexToBin(hexa[it]);
	}

	std::array<std::array < int, 128>, 128> regions;
	int regionNumber{ 0 };

	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			regions[i][j] = (bin[i][j] == '1') ? 0 : -1;
		}
	}

	for (int x = 0; x < 128; x++)
	{
		for (int y = 0; y < 128; y++)
		{
			if (regions[x][y] == 0)
			{
				regionNumber++;
				markRegion(regions, x, y, regionNumber);
			}
		}
	}

	out << regionNumber;

	in.close();
	out.close();
}