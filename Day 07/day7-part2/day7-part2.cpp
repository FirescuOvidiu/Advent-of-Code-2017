#include "../../AOCHeaders/stdafx.h"


struct Program
{
	Program() : weight(0), totalWeight(0) {}

	std::string name;
	int weight;
	int totalWeight;
	std::vector<std::string> abovePrograms;
};


void readInput(std::fstream& in, std::unordered_map<std::string, Program>& programs, std::vector<Program>& neededPrograms)
{
	std::string line, word;
	char c{};

	while (std::getline(in, line))
	{
		std::istringstream iss{ line };
		Program current;

		iss >> current.name;
		iss >> c >> current.weight >> c;
		iss >> word;

		while (iss >> word)
		{
			if (word.back() == ',')
			{
				word.pop_back();
			}
			current.abovePrograms.push_back(word);
		}

		if (!current.abovePrograms.empty())
		{
			current.totalWeight = -1;
			neededPrograms.push_back(current);
		}
		else
		{
			current.totalWeight = current.weight;
		}

		programs[current.name] = current;
	}
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::unordered_map<std::string, Program> programs;
	std::vector<Program> neededPrograms;	// programs that don't have the total weight calculated yet

	readInput(in, programs, neededPrograms);

	while (!neededPrograms.empty())
	{
		// Parse the programs that don't have the total weight calculated yet
		for (auto& program : neededPrograms)
		{
			// Check if we can calculate the totalWeight of the current program
			if (!std::all_of(std::begin(program.abovePrograms), std::end(program.abovePrograms), [&programs](const auto curr)
				{
					return programs[curr].totalWeight != -1;
				}))
			{
				continue;
			}

			// Check if all the above programs have the same weight
			if (std::adjacent_find(std::begin(program.abovePrograms), std::end(program.abovePrograms),
				[&programs](const auto& first, const auto& second)
				{
					return programs[first].totalWeight != programs[second].totalWeight;
				}) == std::end(program.abovePrograms))
			{
				// Calculate the total weight for the current program by adding the above programs weights and current program weight
				programs[program.name].totalWeight = std::accumulate(std::begin(program.abovePrograms), std::end(program.abovePrograms), programs[program.name].weight,
					[&programs](int& total, const std::string& name)
					{
						return total + programs[name].totalWeight;
					});
			}
			else
			{
				// The above programs don't have the same total weight so we will find the program with the wrong weight
				std::sort(std::begin(program.abovePrograms), std::end(program.abovePrograms),
					[&programs](const auto& first, const auto& second)
					{
						return programs[first].totalWeight > programs[second].totalWeight;
					});

				// Calculate and write the correct weight of the program
				out << programs[program.abovePrograms.front()].weight - programs[program.abovePrograms.front()].totalWeight + programs[*(program.abovePrograms.begin() + 1)].totalWeight;

				neededPrograms.clear();
				break;
			}
		}
	}

	in.close();
	out.close();
}