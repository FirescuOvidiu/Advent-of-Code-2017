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
	long long pos{ 0 }, valueFreq{ 0 }, value{ 0 }, countMulInstruction{ 0 };

	while (pos < instructions.size())
	{
		value = getValue(instructions, registers, pos);

		if (instructions[pos].op == "jnz")
		{
			pos = registers[instructions[pos].reg] != 0 ? pos + value : pos + 1;
			continue;
		}
		if (instructions[pos].op == "mul")
		{
			countMulInstruction++;
		}
		registers[instructions[pos].reg] = operations[instructions[pos].op](registers[instructions[pos].reg], value);

		pos++;
	}

	out << countMulInstruction;

	in.close();
	out.close();
}