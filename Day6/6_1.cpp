#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    int count, fishSum = 0;
    int fishCounts[9] = {0};

    // Get all the fishies
    while (!input.eof())
    {
        input >> count;
        input.ignore(1);
        fishCounts[count]++;
    }

    // Let the fishies breed
    for (int i = 1; i <= 80; i++)
    {
        count = fishCounts[0];
        for (int j = 0; j < 8; j++)
            fishCounts[j] = fishCounts[j + 1];
        fishCounts[6] += count;
        fishCounts[8] = count;
    }

    // Harvest the fishies
    fishSum = 0;
    for (int i : fishCounts)
        fishSum += i;
    std::cout << "Ans. " << fishSum << std::endl;
}