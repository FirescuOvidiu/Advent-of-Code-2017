#include "../../AOCHeaders/stdafx.h"


struct Instruction
{
	Instruction(const std::string op = {}, const int reg = { 0 }, const std::string value = { "0" }) : op(op), reg(reg), value(value) {}

	std::string op;
	int reg;
	std::string value;
};


std::vector<Instruction> readInput(std::fstream& in)
{
	std::vector<Instruction> instructions;
	std::string line;

	while (std::getline(in, line))
	{
		std::stringstream ss{ line };
		Instruction curr;
		std::string c;

		ss >> curr.op >> c >> curr.value;
		if ((curr.op == "snd") || (curr.op == "rcv"))
		{
			curr.value = c;
		}
		curr.reg = std::islower(c[0]) ? c[0] - 'a' : std::stoi(c);
		instructions.push_back(curr);
	}

	return instructions;
}


long long getValue(const std::vector<Instruction>& instructions, const std::array<long long, 25>& registers, const int pos)
{
	if (!std::islower(instructions[pos].value[0]))
	{
		return std::stoi(instructions[pos].value);
	}

	return registers[*instructions[pos].value.c_str() - 'a'];
}


bool checkrime(long long n)
{
	if ((n == 2) || (n == 3))
	{
		return true;
	}

	if (n <= 1 || n % 2 == 0 || n % 3 == 0)
	{
		return false;
	}

	for (int i = 5; i * i <= n; i = i + 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			return false;
		}
	}
	return true;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::map<std::string, std::function<long long(long long, long long)>> operations{
	{"set", [](long long, long long value) {  return value; }}, {"add", std::plus<long long>()},
	{"mul", std::multiplies<long long>()},	{"mod", std::modulus<long long>()},
	{"sub", std::minus<long long>()}
	};

	std::vector<Instruction> instructions = readInput(in);
	std::array<long long, 25> registers{ 0 };

	int initialValue{ (int)operations[instructions[0].op](registers[instructions[0].reg], getValue(instructions, registers, 0)) };
	initialValue = operations[instructions[4].op](initialValue, getValue(instructions, registers, 4));
	initialValue = operations[instructions[5].op](initialValue, getValue(instructions, registers, 5));

	int finalValue{ (int)operations[instructions[7].op](initialValue, getValue(instructions, registers, 7)) }, registerH{ 0 };
	int offset{ (int)operations[instructions[30].op](0, getValue(instructions, registers, 30)) };

	for (; initialValue <= finalValue; initialValue += offset)
	{
		if (!checkrime(initialValue))
		{
			registerH++;
		}
	}

	out << registerH;

	in.close();
	out.close();
}