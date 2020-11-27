#include "../../AOCHeaders/stdafx.h"


int maxStr{ 0 };


struct Component
{
	Component(int port1 = 0, int port2 = 0, int str = 0) : port1(port1), port2(port2), str(str) {}

	int port1, port2;
	int str;
};


std::vector<Component> readInput(std::fstream& in)
{
	std::vector<Component> components;
	Component comp;
	char c{};

	while (in >> comp.port1 >> c >> comp.port2)
	{
		comp.str = comp.port1 + comp.port2;
		components.push_back(comp);
	}

	return components;
}


void findTotalStr(const std::vector<Component>& components, std::vector<bool> visited, int port, int pos, int currStr)
{
	visited[pos] = true;
	currStr += port;

	maxStr = std::max(maxStr, currStr);

	for (int it = 0; it < components.size(); it++)
	{
		if ((port == components[it].port1) && (!visited[it]) && (components[it].port1 != 0))
		{
			findTotalStr(components, visited, components[it].port2, it, currStr + components[it].port1);
		}

		if ((port == components[it].port2) && (!visited[it]) && (components[it].port2 != 0))
		{
			findTotalStr(components, visited, components[it].port1, it, currStr + components[it].port2);
		}
	}
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<Component> components = readInput(in);
	std::vector<bool> visited(components.size(), false);

	for (int pos = 0; pos < components.size(); pos++)
	{
		if (components[pos].port1 == 0)
		{
			visited[pos] = true;
			findTotalStr(components, visited, components[pos].port2, pos, 0);
		}

		if (components[pos].port2 == 0)
		{
			visited[pos] = true;
			findTotalStr(components, visited, components[pos].port1, pos, 0);
		}
	}

	out << maxStr;

	in.close();
	out.close();
}