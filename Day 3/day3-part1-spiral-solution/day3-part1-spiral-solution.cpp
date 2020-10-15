#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

public:
	int x, y;
};


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> dx{ 0,-1,0,1 }, dy{ 1,0,-1,0 };
	int currSteps = 0, neededStepsToTurn = 0, countTurns = 0, direction = 0, input = 0, value = 2;

	in >> input;

	std::vector<std::vector<int>> v(std::sqrt(input) + 2, std::vector<int>(std::sqrt(input) + 2, 0));
	Coordinate curr(v.size() / 2, v.size() / 2);
	v[curr.x][curr.y] = 1;

	while (v[curr.x][curr.y] != input)
	{
		curr.x += dx[direction];
		curr.y += dy[direction];

		// If we reach the needed steps we change direction to the left, otherwise we keep the same direction
		if (currSteps == neededStepsToTurn)
		{
			direction = (direction + 1) % 4;
			currSteps = 0;
			countTurns++;
		}
		else
		{
			currSteps++;
		}

		v[curr.x][curr.y] = value;
		value++;

		// Every two times we turn, the number of steps are increased by one
		if (countTurns == 2)
		{
			neededStepsToTurn++;
			countTurns = 0;
		}
	}

	out << std::abs(curr.x - (int)v.size() / 2) + std::abs(curr.y - (int)v.size() / 2);

	in.close();
	out.close();
}