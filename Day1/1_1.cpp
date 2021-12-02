#include <fstream>
#include <iostream>

int main (int argc, char *argv[])
{
    std::fstream input ("input.txt");

    unsigned int prev = 4294967295u, current;
    unsigned int count = 0u;

    while (input >> current)
    {
        if (current > prev)
            count++;

        prev = current;
    }
    
    std::cout << "Ans. " << count << std::endl;
}