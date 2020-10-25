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
		if ((c == '{') && (openGarbage == false))
		{
			addUp++;	
			continue;
		}

		if ((c == '}') && (openGarbage == false))
		{
			score += addUp;
			addUp--;
			continue;
		}

		if (c == '<')
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
		}
	}

	out << score;

	in.close();
	out.close();
}