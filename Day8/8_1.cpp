#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::string tmp;
    int count = 0;

    while (!input.eof())
    {
        input.ignore(1024, '|');
        input.ignore(1, ' ');

        for (int i = 0; i < 4; i++)
        {
            input >> tmp;

            if (tmp.size() == 2 ||  // 1
                tmp.size() == 4 ||  // 4
                tmp.size() == 3 ||  // 7
                tmp.size() == 7)    // 8
                count++;
        }
    }
    
    std::cout << "Ans. " << count << std::endl;
}