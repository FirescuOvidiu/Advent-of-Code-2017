#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::map<std::string, std::function<bool(int, int)>> operations = {
	{ "==", std::equal_to<int>() }, { "!=", std::not_equal_to<int>() },
	{ ">", std::greater<int>() }, { ">=", std::greater_equal<int>() },
	{ "<", std::less<int>() }, { "<=", std::less_equal<int>() } };

	std::unordered_map<std::string, int> values;
	std::string firstName, firstOp, secondName, secondOp;
	int registers{ 0 }, firstNumber{ 0 }, secondNumber{ 0 }, max{ -1 };

	while (in >> firstName >> firstOp >> firstNumber >> secondName >> secondName >> secondOp >> secondNumber)
	{
		if (values.find(firstName) == std::end(values))
		{
			values[firstName] = 0;
		}

		if (values.find(secondName) == std::end(values))
		{
			values[secondName] = 0;
		}

		if (operations[secondOp](values[secondName], secondNumber))
		{
			if (firstOp == "inc")
			{
				values[firstName] += firstNumber;
			}
			else
			{
				values[firstName] -= firstNumber;
			}
		}

		max = std::max(values[firstName], max);
	}

	out << max;

	in.close();
	out.close();
}