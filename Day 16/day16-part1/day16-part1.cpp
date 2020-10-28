#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string program(16, 'a' ), line;
	int first{ 0 }, second{ 0 };
	char c{};

	std::iota(std::begin(program), std::end(program), 97);

	while (std::getline(in, line, ','))
	{
		std::stringstream ss{ line };

		switch (line[0])
		{
		case 's':
			ss >> c >> first;
			std::rotate(std::rbegin(program), std::rbegin(program) + first, std::rend(program));
			break;

		case 'x':
			ss >> c >> first >> c >> second;
			std::swap(program[first], program[second]);
			break;

		case 'p':
			std::iter_swap(std::find(std::begin(program), std::end(program), line[1]),
				std::find(std::begin(program), std::end(program), line[3]));
			break;

		}
	}

	out << program;

	in.close();
	out.close();
}