#include <fstream>
#include <iostream>
#include <map>

#define INT_MAX 2147483647

// C = sum(|V_d - V_p_i|,0) * |P_i|

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::map<int, int> pos;
    std::map<int, int>::iterator p;
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

        for (p = pos.begin(); p != pos.end(); p++)
        {
            tmp = 0;
            for (int i = 0; i < abs(destPos - p->first); i++)
                tmp += abs(destPos - p->first) - i;
            currCost += tmp * p->second;
        }

        destPos++;
    }

    std::cout << "Ans. " << prevCost << std::endl;
}