#include "../../AOCHeaders/stdafx.h"


struct Coordinate
{
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

	int x, y;
};


std::vector<std::string> readInput(std::fstream& in)
{
	std::vector<std::string> directions;
	std::string line;

	while (std::getline(in, line, ','))
	{
		directions.push_back(line);
	}

	return directions;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::map<std::string, Coordinate> moveDir{ {"n", {-2, 0}}, {"ne", {-1, 1}},
		{"nw", {-1, -1}}, {"s", {2, 0}}, {"se", {1, 1}}, {"sw", {1, -1}} };

	std::vector<std::string> inputDirections = readInput(in);
	int maxSteps{ 0 }, currSteps{ 0 };
	Coordinate curr;

	for (const auto& dir : inputDirections)
	{
		curr.x += moveDir[dir].x;
		curr.y += moveDir[dir].y;
		currSteps = (abs(curr.x) + abs(curr.y)) / 2;
		maxSteps = std::max(currSteps, maxSteps);
	}

	out << maxSteps;

	in.close();
	out.close();
}