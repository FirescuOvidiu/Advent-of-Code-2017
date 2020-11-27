#include "../../AOCHeaders/stdafx.h"


std::vector<std::vector<char>> fromStringToMatrix(const std::string& input)
{
	std::vector<std::vector<char>> output;
	std::vector<char> aux;
	std::stringstream ss{ input };
	char c{};

	while (ss >> c)
	{
		if (c == '/')
		{
			output.push_back(aux);
			aux.clear();
		}
		else
		{
			aux.push_back(c);
		}
	}
	output.push_back(aux);

	return output;
}


std::string fromMatrixToString(const std::vector<std::vector<char>>& input)
{
	std::string output;

	for (const auto& row : input)
	{
		for (const auto& c : row)
		{
			output.push_back(c);
		}
		output.push_back('/');
	}
	output.pop_back();

	return output;
}


std::vector<std::vector<char>> getGrid(const std::vector<std::vector<char>>& image, const int squaresSize, const int x, const int y)
{
	std::vector<std::vector<char>> grid(squaresSize, std::vector<char>(squaresSize));

	for (int currX = x; currX < x + squaresSize; currX++)
	{
		for (int currY = y; currY < y + squaresSize; currY++)
		{
			grid[currX - x][currY - y] = image[currX][currY];
		}
	}

	return grid;
}


void updateImage(std::vector<std::vector<char>>& image, const std::vector<std::vector<char>>& rule, const int squaresSize, int x, int y)
{
	if (squaresSize == 2)
	{
		x = x / squaresSize * 3;
		y = y / squaresSize * 3;
	}
	else
	{
		x = x / squaresSize * 4;
		y = y / squaresSize * 4;
	}

	for (int currX = x; currX <= x + squaresSize; currX++)
	{
		for (int currY = y; currY <= y + squaresSize; currY++)
		{
			image[currX][currY] = rule[currX - x][currY - y];
		}
	}
}


void rotate90Clockwise(std::vector<std::vector<char>>& grid)
{
	int n = { (int)grid.size() };

	// Traverse each cycle
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = i; j < n - i - 1; j++)
		{
			// Swap elements of each cycle
			// in clockwise direction
			int temp = grid[i][j];
			grid[i][j] = grid[n - 1 - j][i];
			grid[n - 1 - j][i] = grid[n - 1 - i][n - 1 - j];
			grid[n - 1 - i][n - 1 - j] = grid[j][n - 1 - i];
			grid[j][n - 1 - i] = temp;
		}
	}
}


void flip(std::vector<std::vector<char>>& grid)
{
	int n = { (int)grid.size() };

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			std::swap(grid[i][j], grid[j][i]);
		}
	}
}


void flipAndRotate(std::vector<std::vector<char>>& gridIn, std::vector<std::vector<char>>& gridOut, std::unordered_map<std::string, std::vector<std::vector<char>>>& rules)
{
	flip(gridIn);
	rules.insert({ fromMatrixToString(gridIn), gridOut });
	flip(gridIn);

	rotate90Clockwise(gridIn);
	rules.insert({ fromMatrixToString(gridIn), gridOut });
}


std::unordered_map<std::string, std::vector<std::vector<char>>> readInput(std::fstream& input)
{
	std::unordered_map<std::string, std::vector<std::vector<char>>> rules;
	std::vector<std::vector<char>> gridIn, gridOut;
	std::string line;

	while (std::getline(input, line))
	{
		std::string in, out;
		in = line.substr(0, line.find(' '));
		out = line.substr(line.find(' ') + 4);

		gridIn = fromStringToMatrix(in);
		gridOut = fromStringToMatrix(out);

		rules.insert({ in, gridOut });
		flipAndRotate(gridIn, gridOut, rules);
		flipAndRotate(gridIn, gridOut, rules);
		flipAndRotate(gridIn, gridOut, rules);
		flip(gridIn);
		rules.insert({ fromMatrixToString(gridIn), gridOut });
	}

	return rules;
}


int main()
{
	std::fstream input("input.in", std::fstream::in);
	std::fstream output("output.out", std::fstream::out);

	std::vector<std::vector<char>> image = { {'.', '#', '.'}, {'.', '.', '#'}, {'#', '#', '#'} }, grid;
	std::unordered_map<std::string, std::vector<std::vector<char>>> rules = readInput(input);
	int imageSize = 0, squaresSize = 0, x = 0, y = 0;

	for (int it = 1; it <= 18; it++)
	{
		imageSize = image.size();
		squaresSize = (imageSize % 2 == 0) ? 2 : 3;

		int newImageSize = imageSize / squaresSize * (squaresSize + 1);
		std::vector<std::vector<char>> newImage(newImageSize, std::vector<char>(newImageSize));

		for (int x = 0; x < imageSize; x += squaresSize)
		{
			for (int y = 0; y < imageSize; y += squaresSize)
			{
				grid = getGrid(image, squaresSize, x, y);
				if (auto rule = rules.find(fromMatrixToString(grid)); rule != std::end(rules))
				{
					updateImage(newImage, rule->second, squaresSize, x, y);
				}
			}
		}
		image = newImage;
	}

	output << std::accumulate(std::begin(image), std::end(image), 0, [](int total, const auto& row) {
		return total + std::count(std::begin(row), std::end(row), '#');
		});

	input.close();
	output.close();
}