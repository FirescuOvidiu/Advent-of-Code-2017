#include "../../AOCHeaders/stdafx.h"


std::vector<std::string> readInput(std::fstream& in)
{
	std::vector<std::string> instructions;
	std::string line;

	while (std::getline(in, line, ','))
	{
		instructions.push_back(line);
	}

	return instructions;
}


void dance(const std::vector<std::string>& instructions, std::string& programs)
{
	int first{ 0 }, second{ 0 };
	char c{};

	for (const auto line : instructions)
	{
		std::stringstream ss{ line };

		switch (line[0])
		{
		case 's':
			ss >> c >> first;
			std::rotate(std::rbegin(programs), std::rbegin(programs) + first, std::rend(programs));
			break;

		case 'x':
			ss >> c >> first >> c >> second;
			std::swap(programs[first], programs[second]);
			break;

		case 'p':
			std::iter_swap(std::find(std::begin(programs), std::end(programs), line[1]),
				std::find(std::begin(programs), std::end(programs), line[3]));
			break;

		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::string> instructions = readInput(in);
	std::string programs(16, 'a'), originalPrograms;
	int repeatCount{ 0 };

	std::iota(std::begin(programs), std::end(programs), 97);
	originalPrograms = programs;

	do
	{
		dance(instructions, programs);
		repeatCount++;
	} while (programs != originalPrograms);

	repeatCount = 1000000000 % repeatCount;
	for (int it = 0; it < repeatCount; it++)
	{
		dance(instructions, programs);
	}

	out << programs;

	in.close();
	out.close();
}