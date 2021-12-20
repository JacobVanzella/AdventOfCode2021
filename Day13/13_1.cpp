#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[])
{
    bool flag = false;
    char tmp;
    int32_t tmpx, tmpy, sz = 0;
    std::fstream input("input.txt");
    std::stringstream ss;
    std::string line;
    std::vector<std::pair<int32_t, int32_t>> coords;
    std::vector<std::pair<char, int32_t>> folds;

    while (!input.eof())
    {
        std::getline(input, line);
        ss.str(line);
        // Get Points
        if (!flag)
        {
            flag = line.size() == 0;
            if (flag)
                continue;

            ss >> tmpx;
            ss.ignore(1, ' ');
            ss >> tmpy;
            ss.clear();
            coords.emplace_back(tmpx, tmpy);

            if (tmpx > sz)
                sz = tmpx;
            if (tmpy > sz)
                sz = tmpy;
        }
        // Get Folds
        else
        {
            ss.str(line);
            ss.ignore(11, '\n');
            ss >> tmp;
            ss.ignore(1, '\n');
            ss >> tmpx;
            folds.emplace_back(tmp, tmpx);
            ss.clear();
        }
    }

    // Calculate Folds
    for (auto flip : folds)
    {
        int32_t grid[sz][sz];
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                grid[j][i] = 0;

        // Fold Y
        if (flip.first == 'y')
        {
            for (int i = 0; i < coords.size(); i++)
                if (coords[i].second > flip.second)
                    coords[i].second = 2 * flip.second - coords[i].second;
        }
        // Fold X
        else
        {
            for (int i = 0; i < coords.size(); i++)
                if (coords[i].first > flip.second)
                    coords[i].first = 2 * flip.second - coords[i].first;
        }
        break;
    }

    // Calculate Answer
    tmpx = tmpy = sz = 0;
    for (auto pnt : coords)
    {
        tmpx = tmpx <= pnt.first ? pnt.first + 1 : tmpx;
        tmpy = tmpy <= pnt.second ? pnt.second + 1 : tmpy;
    }

    int32_t grid[tmpx][tmpy] = {0};
    for (auto pnt : coords)
        grid[pnt.first][pnt.second] = 1;

    for (int i = 0; i < tmpy; i++)
        for (int j = 0; j < tmpx; j++)
            if (grid[j][i] == 1)
                sz++;

    std::cout << "Ans. " << sz << std::endl;
}