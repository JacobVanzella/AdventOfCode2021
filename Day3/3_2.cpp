#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

struct Node
{
    int zeros, ones;
    Node *zero, *one;
};

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::string str;
    Node head{0, 0, nullptr, nullptr};
    Node *itr, *itr2;

    input >> str;

    bool more1;
    int cols = str.size(), rows = 0;
    int o2 = 0, co2 = 0;

    // Count up numbers and insert into binary search tree
    do
    {
        rows++;
        itr = &head;
        for (int i = 0; i < cols; i++)
        {
            if (str[i] == '1')
            {
                if (itr->one == nullptr)
                {
                    itr->one = new Node{0, 0, nullptr, nullptr};
                }
                itr->ones++;
                itr = itr->one;
            }
            else
            {
                if (itr->zero == nullptr)
                {
                    itr->zero = new Node{0, 0, nullptr, nullptr};
                }
                itr->zeros++;
                itr = itr->zero;
            }
        }
    } while (input >> str);

    // Search binary tree based on gamma criteria
    itr = &head;
    itr2 = &head;
    for (int i = 0; i < cols; i++)
    {
        more1 = itr->ones >= itr->zeros;
        if (more1)
        {
            if (itr->one != nullptr)
            {
                o2 += pow(2, cols - i - 1);
                itr = itr->one;
            }
            else
            {
                itr = itr->zero;
            }
        }
        else
        {
            if (itr->zero != nullptr)
            {
                itr = itr->zero;
            }
            else
            {
                o2 += pow(2, cols - i - 1);
                itr = itr->one;
            }
        }

        more1 = itr2->ones >= itr2->zeros;
        if (!more1)
        {
            if (itr2->one != nullptr)
            {
                co2 += pow(2, cols - i - 1);
                itr2 = itr2->one;
            }
            else
            {
                itr2 = itr2->zero;
            }
        }
        else
        {
            if (itr2->zero != nullptr)
            {
                itr2 = itr2->zero;
            }
            else
            {
                co2 += pow(2, cols - i - 1);
                itr2 = itr2->one;
            }
        }
    }

    std::cout << "(O2, CO2, ANS) = (" << o2 << ", " << co2 << ", " << o2 * co2 << ")" << std::endl;
}