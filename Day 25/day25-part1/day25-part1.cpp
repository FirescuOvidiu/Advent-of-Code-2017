#include "../../AOCHeaders/stdafx.h"


struct Component
{
	int currValue, newValue, dir;
	char newState;
};


struct State
{
	Component first, second;
};


Component getComponent(std::fstream& in)
{
	std::string matches("0123456789"), line;
	Component c;

	std::getline(in, line);
	c.currValue = line[line.find_first_of(matches)] - '0';
	std::getline(in, line);
	c.newValue = line[line.find_first_of(matches)] - '0';
	std::getline(in, line);
	c.dir = line.find("right") != std::string::npos ? 1 : -1;
	std::getline(in, line);
	c.newState = line[26];

	return c;
}


std::tuple<std::unordered_map<char, State>, int, char> readInput(std::fstream& in)
{
	std::unordered_map<char, State> states;
	std::string line;
	State currState;
	int steps{ 0 };
	char startState{};

	std::getline(in, line);
	startState = line[15];
	in >> line >> line >> line >> line >> line >> steps >> line;
	std::getline(in, line);

	while (std::getline(in, line))
	{
		std::getline(in, line);
		states.insert({ line[9], {getComponent(in), getComponent(in)} });
	}

	return { states, steps, startState };
}


int main()
{
	std::fstream input("input.in", std::fstream::in);
	std::fstream output("output.out", std::fstream::out);

	std::vector<bool> tape(100000, false);
	auto [states, steps, currState] = readInput(input);
	int pos{ 50000 };

	for (int it = 1; it <= steps; ++it)
	{
		if (tape[pos] == states[currState].first.currValue)
		{
			tape[pos] = states[currState].first.newValue;
			pos += states[currState].first.dir;
			currState = states[currState].first.newState;
		}
		else
		{
			tape[pos] = states[currState].second.newValue;
			pos += states[currState].second.dir;
			currState = states[currState].second.newState;
		}
	}

	output << std::count(std::begin(tape), std::end(tape), true);

	input.close();
	output.close();
}