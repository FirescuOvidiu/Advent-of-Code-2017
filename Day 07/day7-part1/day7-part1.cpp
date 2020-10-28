#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::set<std::string> aboveProgramNames;
	std::vector<std::string> programNames;
	std::string line, word;

	while (std::getline(in, line))
	{
		std::istringstream iss{ line };

		iss >> word;
		programNames.push_back(word);
		iss >> word >> word;

		while (iss >> word)
		{
			if (word.back() == ',')
			{
				word.pop_back();
			}
			aboveProgramNames.insert(word);
		}
	}

	for (const auto& name : programNames)
	{
		if (std::find(std::begin(aboveProgramNames), std::end(aboveProgramNames), name) == std::end(aboveProgramNames))
		{
			out << name;
			break;
		}
	}

	in.close();
	out.close();
}