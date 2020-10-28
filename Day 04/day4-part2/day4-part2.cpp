#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::string line{}, word{};
	bool check{ true };
	int count{ 0 };

	while (std::getline(in, line))
	{
		std::istringstream iss{ line };
		std::set<std::string> words;

		check = true;
		while (iss >> word)
		{
			std::sort(std::begin(word), std::end(word));
			if (words.find(word) == std::end(words))
			{
				words.insert(word);
			}
			else
			{
				check = false;
			}
		}

		if (check)
		{
			count++;
		}
	}

	out << count;

	in.close();
	out.close();
}