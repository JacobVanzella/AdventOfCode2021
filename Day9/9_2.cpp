#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define SZR static_cast<int32_t>(100)
#define SZC static_cast<int32_t>(100)

struct pos
{
    int32_t x, y;
};

// Used to sort in reverse order
bool compare (int a, int b) { return (a > b); }

// Depth First Search on low point
int DFS(pos p, const int32_t hMap[], bool visitMap[])
{
    int visitCount = 1;
    visitMap[SZC * p.y + p.x] = true;

    if (hMap[SZC * p.y + p.x] == 9)
        return 0;
    
    if (p.y != 0 && !visitMap[SZC * (p.y - 1) + p.x]) // Up
        visitCount += DFS(pos{p.x, p.y - 1}, hMap, visitMap);
    if (p.y != SZR - 1 && !visitMap[SZC * (p.y + 1) + p.x]) // Down
        visitCount += DFS(pos{p.x, p.y + 1}, hMap, visitMap);
    if (p.x != 0 && !visitMap[SZC * p.y + p.x - 1]) // Left
        visitCount += DFS(pos{p.x - 1, p.y}, hMap, visitMap);
    if (p.x != SZC - 1 && !visitMap[SZC * p.y + p.x + 1]) // Right
        visitCount += DFS(pos{p.x + 1, p.y}, hMap, visitMap);

    return visitCount;
}

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::vector<pos> lowPos; // x,y of low pos
    std::vector<int> grpSz;
    int32_t hMap[SZR * SZC];
    bool visitMap[SZR * SZC] = {false};
    bool low;
    char tmp;

    // Read file into matrix
    for (size_t i = 0; i < SZR; i++)
    {
        for (size_t j = 0; j < SZC; j++)
        {
            input >> tmp;
            hMap[SZC * i + j] = static_cast<int>(tmp) - 48;
        }
        input.ignore(1, ' '); // Ignore endline
    }

    // Find low values
    for (int32_t row = 0; row < SZR; row++)
    {
        for (int32_t col = 0; col < SZC; col++)
        {
            low = true;
            if (row != 0) // Up
                low = low && (hMap[SZC * (row - 1) + col] > hMap[SZC * row + col]);
            if (row != SZR - 1) // Down
                low = low && (hMap[SZC * (row + 1) + col] > hMap[SZC * row + col]);
            if (col != 0) // Left
                low = low && (hMap[SZC * row + col - 1] > hMap[SZC * row + col]);
            if (col != SZC - 1) // Right
                low = low && (hMap[SZC * row + col + 1] > hMap[SZC * row + col]);

            if (low)
                lowPos.emplace_back(pos{col, row});
        }
    }
    
    // Call DFS for each low group
    for (auto p : lowPos)
        grpSz.emplace_back(DFS(p, hMap, visitMap));
    std::sort(grpSz.begin(), grpSz.end(), compare);
    

    std::cout << "Ans. = " << grpSz[0] << " * " << grpSz[1] << " * " << grpSz[2];
    std::cout << " = " << grpSz[0] * grpSz[1] * grpSz[2] << std::endl;
}