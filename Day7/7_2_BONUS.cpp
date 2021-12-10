#include <fstream>
#include <iostream>
#include <map>

// C = sum(|V_d - V_p_i|,0) * |P_i|

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::map<int, int> pos;
    std::map<int, int>::iterator p;
    int tmp, destPos1, destPos2;
    int cost1 = 0, cost2 = 0, sum = 0, count = 0;

    while (!input.eof())
    {
        input >> tmp;
        input.ignore(1, '\n');

        sum += tmp;
        count++;

        if (pos.find(tmp) == pos.end())
            pos.insert(std::pair<int, int>(tmp, 1));
        else
            pos.at(tmp)++;
    }

    // Get destination position as truncated int. Sometimes rounding works and sometimes
    // it doesn't so we'll truncate and test that value and the next.
    destPos1 = sum / count;
    destPos2 = destPos1 + 1;

    for (p = pos.begin(); p != pos.end(); p++)
    {
        tmp = abs(destPos1 - p->first);
        tmp = (tmp * (tmp + 1)) / 2;
        cost1 += tmp * p->second;

        tmp = abs(destPos2 - p->first);
        tmp = (tmp * (tmp + 1)) / 2;
        cost2 += tmp * p->second;
    }
    
    if (cost1 > cost2)
    {
        destPos1 = destPos2;
        cost1 = cost2;
    }

    std::cout << "Ans. " << cost1 << " , Dest: " << destPos1 << std::endl;
}