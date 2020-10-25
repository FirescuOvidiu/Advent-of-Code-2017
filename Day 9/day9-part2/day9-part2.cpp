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
		if (!openGarbage)
		{
			switch (c)
			{
			case '<':
				openGarbage = true;
				break;
			}
		}
		else
		{
			switch (c)
			{
			case '>':
				openGarbage = false;
				break;

			case '!':
				in >> c;
				break;

			default:
				count++;
				break;
			}
		}
	}

	out << count;

	in.close();
	out.close();
}