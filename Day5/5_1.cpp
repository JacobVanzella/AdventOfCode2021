#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define SZ 1000

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::string inputStr;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines;
    std::pair<int, int> tmpA, tmpB;

    int count = 0;
    int map[SZ][SZ] = {0}; // map[Y-cord][X-cord]

    while (!input.eof())
    {
        // Condition the string input, a bit combersome, but easy to understand
        std::getline(input, inputStr);
        std::replace(inputStr.begin(), inputStr.end(), ',', ' ');
        std::replace(inputStr.begin(), inputStr.end(), '-', ' ');
        std::replace(inputStr.begin(), inputStr.end(), '>', ' ');
        std::stringstream strStream(inputStr);

        // First is X-cord, Second is Y-cord
        strStream >> tmpA.first;
        strStream >> tmpA.second;
        strStream >> tmpB.first;
        strStream >> tmpB.second;

        lines.emplace_back(tmpA, tmpB);
    }

    for (auto line : lines)
    {
        // Vertical Line
        if (line.first.first == line.second.first)
        {
            for (int i = line.first.second; i <= line.second.second; i++)
                map[i][line.first.first]++;
            for (int i = line.first.second; i >= line.second.second; i--)
                map[i][line.first.first]++;
        }

        // Horizontal Line
        if (line.first.second == line.second.second)
        {
            for (int i = line.first.first; i <= line.second.first; i++)
                map[line.first.second][i]++;
            for (int i = line.first.first; i >= line.second.first; i--)
                map[line.first.second][i]++;
        }
    }

    for (int i = 0; i < SZ; i++)
    {
        for (int j = 0; j < SZ; j++)
        {
            if (map[i][j] > 1)
                count++;
        }
    }
    
    std::cout << "Ans. " << count << std::endl;
}