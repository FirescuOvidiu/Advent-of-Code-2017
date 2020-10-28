#include "../../AOCHeaders/stdafx.h"


class Coordinate
{
public:
	Coordinate(int x = 0, int y = 0) : x(x), y(y) {}
	void operator++(int)
	{
		x++;
		y++;
	}

public:
	int x, y;
};


// Function used to move on the edge of the spiral and finding the input position
void move(int& pos, int& value, const char sign, const int tiles, const int input)
{
	// value will always be on a edge corner
	// tiles memorates the number of numbers in a row/column

	// Checking if we already found the input
	if (value == input)
	{
		return;
	}

	// Checking if the input it's on the current row/column
	if (value - tiles > input)
	{
		value = value - tiles;
		if (sign == '-')
		{
			pos -= tiles;
		}
		else
		{
			pos += tiles;
		}
	}
	else
	{
		// Found the input position
		if (sign == '-')
		{
			pos -= value - input;
		}
		else
		{
			pos += value - input;
		}
		value = input;
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int input = 0, value = 1, tiles = 0, offset = 8;
	in >> input;

	Coordinate curr((std::sqrt(input) + 2) / 2, (std::sqrt(input) + 2) / 2), start = curr;

	while (value < input)
	{
		value += offset;
		tiles += 2;
		offset += 8;
		curr++;
	}

	if (value != input)
	{
		move(curr.y, value, '-', tiles, input);	// Move left
		move(curr.x, value, '-', tiles, input);	// Move up
		move(curr.y, value, '+', tiles, input);	// Move right
		move(curr.x, value, '+', tiles, input);	// Move down
	}

	out << std::abs(curr.x - start.x) + std::abs(curr.y - start.y);

	in.close();
	out.close();
}