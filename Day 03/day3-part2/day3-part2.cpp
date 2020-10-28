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

	std::vector<int> dx{ 0,-1,0,1,-1,-1,1,1 }, dy{ 1,0,-1,0,1,-1,-1,1 };
	std::vector<std::vector<int>> v(100, std::vector<int>(100, 0));
	int currSteps = 0, neededStepsToTurn = 0, countTurns = 0, direction = 0, input = 0;
	Coordinate curr(v.size() / 2, v.size() / 2);

	in >> input;
	v[curr.x][curr.y] = 1;

	while (v[curr.x][curr.y] < input)
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

		for (int it = 0; it < 8; it++)
		{
			v[curr.x][curr.y] += v[curr.x + dx[it]][curr.y + dy[it]];
		}

		// Every two times you turn, the number of steps are increased by one
		if (countTurns == 2)
		{
			neededStepsToTurn++;
			countTurns = 0;
		}
	}

	out << v[curr.x][curr.y];

	in.close();
	out.close();
}