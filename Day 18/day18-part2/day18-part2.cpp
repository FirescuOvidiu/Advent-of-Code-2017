#include "../../AOCHeaders/stdafx.h"


struct Instruction
{
	Instruction(const std::string op = {}, const int reg = { 0 }, const std::string value = { "0" }) : op(op), reg(reg), value(value) {}

	std::string op;
	int reg;
	std::string value;
};


struct Program
{
	Program(int id) : registers({ 0 }), pos(0), id(id) {}

	std::array<long long, 25> registers;
	std::queue <int> input;
	long long pos;
	int id;
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


void execute(Program& A, Program& B, long long& countValuesSend, const std::vector<Instruction>& instructions, std::map<std::string, std::function<long long(long long, long long)>>& operations)
{
	long long value{ 0 };

	if (instructions[A.pos].op == "rcv")
	{
		if (!A.input.empty())
		{
			A.registers[instructions[A.pos].reg] = A.input.front();
			A.input.pop();
			A.pos++;
		}
		return;
	}

	value = getValue(instructions, A.registers, A.pos);

	if (instructions[A.pos].op == "jgz")
	{
		A.pos = A.registers[instructions[A.pos].reg] > 0 ? A.pos + value : A.pos + 1;
		return;
	}

	if (instructions[A.pos].op == "snd")
	{
		B.input.push(value);

		if (A.id == 1)
		{
			countValuesSend++;
		}
	}
	else
	{
		A.registers[instructions[A.pos].reg] = operations[instructions[A.pos].op](A.registers[instructions[A.pos].reg], value);
	}

	A.pos++;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::map<std::string, std::function<long long(long long, long long)>> operations{
		{"set", [](long long, long long value) {  return value; }}, {"add", std::plus<long long>()},
		{"mul", std::multiplies<long long>()},	{"mod", std::modulus<long long>()}
	};

	std::vector<Instruction> instructions = readInput(in);
	Program A(0), B(1);
	long long countValuesSend{ 0 };

	B.registers['p' - 'a'] = 1;

	while ((!A.input.empty() || !B.input.empty() || instructions[A.pos].op != "rcv" || instructions[B.pos].op != "rcv"))
	{
		execute(A, B, countValuesSend, instructions, operations);
		execute(B, A, countValuesSend, instructions, operations);
	}

	out << countValuesSend;

	in.close();
	out.close();
}