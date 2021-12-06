#include <fstream>
#include <iostream>
#include <string>

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

    // Create Huffman Tree
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

    // Search Huffman Tree (surely writing this recursively would be more compact . . . )
    itr = &head;    // Finds O2 number
    itr2 = &head;   // Finds CO2 number
    for (int i = 0; i < cols; i++)
    {
        // Iterate over maximal values
        more1 = itr->ones >= itr->zeros;
        if (more1)
        {
            if (itr->one != nullptr)
            {
                o2 += 1<<(cols - i - 1);
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
                o2 += 1<<(cols - i - 1);
                itr = itr->one;
            }
        }

        // Iterate over minimal values
        more1 = itr2->ones >= itr2->zeros;
        if (!more1)
        {
            if (itr2->one != nullptr)
            {
                co2 += 1<<(cols - i - 1);
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
                co2 += 1<<(cols - i - 1);
                itr2 = itr2->one;
            }
        }
    }

    std::cout << "(O2, CO2, ANS) = (" << o2 << ", " << co2 << ", " << o2 * co2 << ")" << std::endl;
}