#include <fstream>
#include <iostream>
#include <queue>

#define SZ 10

struct pos
{
    int32_t x, y;
};

int32_t main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::queue<pos> flashers;
    int32_t dumbField[SZ * SZ];
    int32_t idx = 0, fCount = 0;
    pos p;
    char tmp;

    while (!input.eof())
    {
        input >> tmp;
        if (tmp == '\n')
            continue;
        else
            dumbField[idx++] = static_cast<int32_t>(tmp) - 48;
    }

    for (idx = 0; idx < 100; idx++)
    {
        // Increment all the boys and queue flashers
        for (int32_t i = 0; i < SZ; i++)
            for (int32_t j = 0; j < SZ; j++)
            {
                ++dumbField[SZ * i + j] %= 10;
                if (dumbField[SZ * i + j] == 0)
                {
                    flashers.push(pos{j, i});
                    fCount++;
                }
            }

        // BFS style increment over flashers
        while (!flashers.empty())
        {
            p = flashers.front();
            flashers.pop();

            // Iterate over 8-connected neighbours
            for (int32_t i = -1; i < 2; i++)
                for (int32_t j = -1; j < 2; j++)
                {
                    // Check bounds
                    if (p.x + j <= -1 ||
                        p.x + j >= SZ ||
                        p.y + i <= -1 ||
                        p.y + i >= SZ ||
                        dumbField[SZ * (p.y + i) + p.x + j] == 0)
                        continue;

                    // Add new flashers to the queue
                    ++dumbField[SZ * (p.y + i) + p.x + j] %= 10;
                    if (dumbField[SZ * (p.y + i) + p.x + j] == 0)
                    {
                        flashers.push(pos{(p.x + j), (p.y + i)});
                        fCount++;
                    }
                }
        }
    }

    std::cout << "Ans. " << fCount << std::endl;
}