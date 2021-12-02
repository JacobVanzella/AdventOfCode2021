#include <fstream>
#include <iostream>

int main (int argc, char *argv[])
{
    std::fstream input ("input.txt");
    char direction;
    
    int depth = 0, xpos = 0, aim = 0, tmp;

    while (input >> direction)
    {
        input.ignore(256, ' ');
        input >> tmp;

        switch (direction)
        {
            case 'f':
                xpos += tmp;
                depth += aim * tmp;
                break;
            case 'd':
                aim += tmp;
                break;
            case 'u':
                aim -= tmp;
                break;
        }
    }
    
    std::cout << "Depth: " << depth << " X-Pos: " << xpos << " Ans. " << depth * xpos << std::endl;
}