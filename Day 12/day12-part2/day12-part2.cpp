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


std::optional<int> find(std::vector<bool>& visited)
{
	for (int it = 0; it < visited.size(); it++)
	{
		if (!visited[it])
		{
			return it;
		}
	}

	return {};
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<std::vector<int>> programs = readInput(in);
	std::vector<bool> visited(programs.size());
	std::queue<int> toVisit;;
	int countGroups{ 0 };

	while (auto value = find(visited))
	{
		toVisit.push(*value);
		visited[*value] = true;
		countGroups++;

		while (!toVisit.empty())
		{
			int id = toVisit.front();
			toVisit.pop();

			for (const auto& p : programs[id])
			{
				if (!visited[p])
				{
					visited[p] = true;
					toVisit.push(p);
				}

			}
		}
	}

	out << countGroups;

	in.close();
	out.close();
}