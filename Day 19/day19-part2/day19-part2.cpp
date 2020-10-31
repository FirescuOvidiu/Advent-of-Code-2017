#include "../../AOCHeaders/stdafx.h"


struct Coordinate
{
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	int x, y;
};


std::vector<std::string> readInput(std::fstream& in)
{
	std::vector<std::string> diagram;
	std::string line;

	while (std::getline(in, line))
	{
		diagram.push_back(line);
	}

	return diagram;
}


bool checkInDiagram(const int x, const int y, const int xMax, const int yMax)
{
	return (x >= 0 && y >= 0 && x < xMax&& y < yMax);
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> dx{ -1,0,1,0 }, dy{ 0,-1,0,1 };
	std::vector<std::string> diagram = readInput(in);
	Coordinate curr;
	int xMax = diagram.size(), yMax = diagram[0].size(), dir{ 2 }, steps{ 0 };

	for (int y = 0; y < yMax; y++)
	{
		if (diagram[0][y] == '|')
		{
			curr = { 0, y };
			break;
		}
	}

	while (diagram[curr.x][curr.y] != ' ')
	{
		if (diagram[curr.x][curr.y] == '+')
		{
			for (int it = 0; it < 4; it++)
			{
				if ((checkInDiagram(curr.x + dx[it], curr.y + dy[it], xMax, yMax)) &&
					(diagram[curr.x + dx[it]][curr.y + dy[it]] != ' ') && (it != (dir + 2) % 4))
				{
					dir = it;
					break;
				}
			}
		}

		curr.x += dx[dir];
		curr.y += dy[dir];
		steps++;
	}

	out << steps;

	in.close();
	out.close();
}