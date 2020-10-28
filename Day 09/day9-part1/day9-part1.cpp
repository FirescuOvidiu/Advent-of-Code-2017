#include "../../AOCHeaders/stdafx.h"


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	
	int score{ 0 }, addUp{ 0 };
	bool openGarbage{ false };
	char c{};

	while (in >> c)
	{
		if (!openGarbage)
		{
			switch (c)
			{
			case '{':
				addUp++;
				break;

			case '}':
				score += addUp--;
				break;

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
			}
		}
	}

	out << score;

	in.close();
	out.close();
}