#include "../../AOCHeaders/stdafx.h"


std::vector<int> findSeenState(std::fstream& in)
{
	std::vector<int> v(std::istream_iterator<int>{in}, {});
	std::set<std::vector<int>> states;
	int cycles{ 0 }, size = v.size();

	while (std::find(std::begin(states), std::end(states), v) == std::end(states))
	{
		states.insert(v);

		auto max = std::max_element(std::begin(v), std::end(v));
		int additionalElements = *max % size;
		*max = 0;

		// *max / size will give us the number that needs to be added to each element
		for (auto& element : v)
		{
			element += *max / size;
		}

		// additional (*max % size) will give us the number of the elements that need an additional +1 
		// besides that added number from above
		while (additionalElements > 0)
		{
			if (++max == std::end(v))
			{
				max = std::begin(v);
			}
			(*max)++;
			additionalElements--;
		}

		cycles++;
	}

	return v;
}

int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<int> v = findSeenState(in), auxV = v;
	int cycles{ 0 }, size = v.size();

	do
	{
		auto max = std::max_element(std::begin(v), std::end(v));
		int additionalElements = *max % size;
		*max = 0;

		// *max / size will give us the number that needs to be added to each element
		for (auto& element : v)
		{
			element += *max / size;
		}

		// additional (*max % size) will give us the number of the elements that need an additional +1 
		// besides that added number from above
		while (additionalElements > 0)
		{
			if (++max == std::end(v))
			{
				max = std::begin(v);
			}
			(*max)++;
			additionalElements--;
		}

		cycles++;
	} while (auxV != v);


	out << cycles;

	in.close();
	out.close();
}