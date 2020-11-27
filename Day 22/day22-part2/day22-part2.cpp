#include "../../AOCHeaders/stdafx.h"


std::vector<std::vector<char>> readInput(std::fstream& input)
{
    std::vector<std::vector<char>> map;
    std::vector<char> row;
    std::string line;

    while (std::getline(input, line))
    {
        for (const auto& c : line)
        {
            row.push_back(c);
        }
        map.push_back(row);
        row.clear();
    }

    return map;
}


std::vector<std::vector<char>> expandMap(std::fstream& input)
{
    std::vector<std::vector<char>> map = readInput(input);
    std::vector<std::vector<char>> expandedMap(map.size() * 1000, std::vector<char>(map[0].size() * 1000, '.'));
    int initialX{ (int)expandedMap.size() / 2 - (int)map.size() / 2 }, initialY{ (int)expandedMap[0].size() / 2 - (int)map[0].size() / 2 };

    for (int x = initialX; x <= expandedMap.size() / 2 + map.size() / 2; x++)
    {
        for (int y = initialY; y <= expandedMap[0].size() / 2 + map[0].size() / 2; y++)
        {
            expandedMap[x][y] = map[x - initialX][y - initialY];
        }
    }

    return expandedMap;
}


int main()
{
    std::fstream input("input.in", std::fstream::in);
    std::fstream output("output.out", std::fstream::out);

    const std::vector<int> dx{ -1,0,1,0 }, dy{ 0,-1,0,1 };
    std::vector<std::vector<char>> map = expandMap(input);
    int countBursts{ 0 }, dir{ 0 }, currX{ (int)map.size() / 2 }, currY{ (int)map[0].size() / 2 };

    for (int it = 1; it <= 10000000; it++)
    {
        switch (map[currX][currY])
        {
        case '.':
            map[currX][currY] = 'W';
            dir = (dir + 1) % 4;
            break;

        case 'W':
            map[currX][currY] = '#';
            countBursts++;
            break;

        case '#':
            map[currX][currY] = 'F';
            dir = (dir + 3) % 4;
            break;

        case 'F':
            map[currX][currY] = '.';
            dir = (dir + 2) % 4;
            break;
        }
        currX += dx[dir];
        currY += dy[dir];
    }

    output << countBursts;

    input.close();
    output.close();
}