#include <fstream>
#include <iostream>
#include <map>

#define INT_MAX 2147483647

// C = |V_d - V_p_i| * |P_i|

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::map<int, int> pos;
    int tmp, currCost = INT_MAX, prevCost = INT_MAX, destPos = 0;

    while (!input.eof())
    {
        input >> tmp;
        input.ignore(1, '\n');

        if (pos.find(tmp) == pos.end())
            pos.insert(std::pair<int, int>(tmp, 1));
        else
            pos.at(tmp)++;
    }

    while (currCost <= prevCost)
    {
        prevCost = currCost;
        currCost = 0;

        for (auto p : pos)
            currCost += abs(destPos - p.first) * p.second;

        destPos++;
    }

    std::cout << "Ans. " << prevCost << std::endl;
}