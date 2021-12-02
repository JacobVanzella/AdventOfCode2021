#include <fstream>
#include <iostream>

int main (int argc, char *argv[])
{
    std::fstream input ("input.txt");

    unsigned int prev = 4294967295u, idx = 2, sum;
    unsigned int count = 0u;
    unsigned int values[3];

    input >> values[0];
    input >> values[1];
    while (input >> values[idx++])
    {
        idx %= 3;
        sum = 0;
        for (auto i : values)
            sum += i;

        if (sum > prev)
            count++;

        prev = sum;
    }
    
    std::cout << "Ans. " << count << std::endl;
}