#include <fstream>
#include <iostream>

#define SZR 100
#define SZC 100

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    int32_t hMap[SZR][SZC];
    int32_t idx = 0, sum = 0;
    bool low;
    char tmp;

    for (size_t i = 0; i < SZR; i++)
    {
        for (size_t j = 0; j < SZC; j++)
        {
            input >> tmp;
            hMap[i][j] = static_cast<int>(tmp) - 48;
        }
        input.ignore(1, ' '); // Ignore endline
    }

    for (int32_t row = 0; row < SZR; row++)
    {
        for (int32_t col = 0; col < SZC; col++)
        {
            low = true;
            if (row != 0) // Up
                low = low && (hMap[row - 1][col] > hMap[row][col]);
            if (row != SZR - 1) // Down
                low = low && (hMap[row + 1][col] > hMap[row][col]);
            if (col != 0) // Left
                low = low && (hMap[row][col - 1] > hMap[row][col]);
            if (col != SZC - 1) // Right
                low = low && (hMap[row][col + 1] > hMap[row][col]);

            if (low)
                sum += hMap[row][col] + 1;
        }
    }

    std::cout << "Ans. " << sum << std::endl;
}