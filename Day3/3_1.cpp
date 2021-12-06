#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::string str;

    input >> str;

    int cols = str.size(), rows = 0, gamma = 0, epsilon = 0;
    int ones[cols] = {0};

    // Count up numbers
    do
    {
        rows++;
        for (int i = 0; i < cols; i++)
            if (str[i] == '1')
                ones[i]++;
    } while (input >> str);
    
    // Convert binary representation of counts to decimal (Big Endian)
    for (int i = 0; i < cols; i++)
        if (ones[i] > rows / 2)
            gamma += 1<<(cols - i - 1);
        else
            epsilon += 1<<(cols - i - 1);

    std::cout << "(Gamma, Epsilon, Power) = (" << gamma << ", " << epsilon;
    std::cout << ", " << gamma * epsilon << ")" << std::endl;
}