#include "../../AOCHeaders/stdafx.h"


std::tuple<long long, long long> readInput(std::fstream& in)
{
	long long A{ 0 }, B{ 0 };
	std::string aux;

	in >> aux >> aux >> aux >> aux >> A;
	in >> aux >> aux >> aux >> aux >> B;

	return { A,B };
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	auto [A, B] = readInput(in);
	int count{ 0 }, mod{ 2147483647 };

	for (int it = 0; it < 40000000; it++)
	{
		A = (A * 16807) % mod;
		B = (B * 48271) % mod;

		if ((A & 0xffff) == (B & 0xffff))
		{
			count++;
		}
	}

	out << count;

	in.close();
	out.close();
}