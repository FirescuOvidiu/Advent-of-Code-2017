#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	int addUp{ 0 }, count{ 0 };
	bool openGarbage = false;
	char c{};

	while (in >> c)
	{
		if ((c == '<') && (openGarbage == false))
		{
			openGarbage = true;
			continue;
		}

		if (c == '>')
		{
			openGarbage = false;
			continue;
		}
		if (c == '!')
		{
			in >> c;
			continue;
		}

		if (openGarbage == true)
		{
			count++;
		}
	}

	out << count;

	in.close();
	out.close();
}