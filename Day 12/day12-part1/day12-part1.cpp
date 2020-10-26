#include "../../AOCHeaders/stdafx.h"


std::vector<std::vector<int>> readInput(std::fstream& in)
{
	std::vector<std::vector<int>> programs;
	std::string line, aux;
	int id{ 0 };

	while (std::getline(in, line))
	{
		std::istringstream iss{ line };
		std::vector<int> program;

		iss >> id >> aux;
		while (iss >> id)
		{
			program.push_back(id);
			iss >> aux;
		}

		programs.push_back(program);
	}

	return programs;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<int>> programs = readInput(in);
	std::set<int> visited;
	std::queue<int> toVisit;
	int countPrograms{ 1 };

	toVisit.push(0);
	visited.insert(0);

	while (!toVisit.empty())
	{
		int id = toVisit.front();
		toVisit.pop();

		for (const auto& p : programs[id])
		{
			if (visited.find(p) == std::end(visited))
			{
				visited.insert(p);
				toVisit.push(p);
				countPrograms++;
			}
		}
	}

	out << countPrograms;

	in.close();
	out.close();
}