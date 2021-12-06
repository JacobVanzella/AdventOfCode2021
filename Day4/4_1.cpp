#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define BRDSZ 6

/*
Board Layout:
    0       [Column Hits]
[Row Hits]  [Board][Valus]

e.g.

0   0   0   0   0   0
0   1   2   3   4   5
0   6   7   8   9   10
0   11  12  13  14  15
0   16  17  18  19  20
0   21  22  23  24  25
*/

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::string topLine;
    std::vector<int> calls;
    std::vector<std::vector<std::vector<int>>> boards;
    std::vector<std::vector<int>> tmpBoard(BRDSZ, std::vector<int>(BRDSZ));
    bool winner = false;
    int num, xptr = 0, yptr = 0, callNum = -1, sum = 0;

    // Read in and store call numbers
    std::getline(input, topLine);
    std::replace(topLine.begin(), topLine.end(), ',', ' ');
    std::stringstream callStream(topLine);
    while (callStream >> num)
        calls.emplace_back(num);

    // Read in and store board numbers
    while (!input.eof())
    {
        for (int i = 0; i < BRDSZ; i++)
        {
            for (int j = 0; j < BRDSZ; j++)
            {
                if (i == 0 || j == 0)
                    tmpBoard[i][j] = 0;
                else
                    input >> tmpBoard[i][j];
            }
        }
        boards.emplace_back(tmpBoard);
    }

    for (auto call : calls)
    {
        callNum++;
        for (int board = 0; board < boards.size(); board++)
        {
            for (int row = 1; row < BRDSZ; row++)
            {
                for (int col = 1; col < BRDSZ; col++)
                {
                    if (boards[board][row][col] == call)
                    {
                        // Increment row and column count
                        boards[board][0][col]++;
                        boards[board][row][0]++;
                        // Set value to -1 to signify it has been called
                        boards[board][row][col] = -1;

                        winner = boards[board][0][col] == 5 || boards[board][row][0] == 5;
                        if (winner)
                        {
                            tmpBoard = boards[board];
                            goto DONE;
                        }
                    }
                }
            }
        }
    }

    DONE:
    for (int row = 1; row < BRDSZ; row++)
    {
        for (int col = 1; col < BRDSZ; col++)
        {
            if (tmpBoard[row][col] != -1)
            {
                sum += tmpBoard[row][col];
            }
        }
    }

    std::cout << "Ans = sum * call = " << sum << " * " << calls[callNum];
    std::cout << " = " << sum * calls[callNum] << std::endl << std::endl;
}