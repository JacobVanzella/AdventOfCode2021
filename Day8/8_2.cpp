#include <fstream>
#include <iostream>
#include <map>
#include <math.h>

// Solve using prime factorization maping letters to primes
// {a,b,c,d,e,f,g} = {2, 3, 5, 7, 11, 13, 17}

// Convert 7 segment digit into product of primes
int primeConv(const std::string word)
{
    int primeKey = 1;
    for (int i = 0; i < word.size(); i++)
    {
        switch (word[i])
        {
        case 'a':
            primeKey *= 2;
            break;

        case 'b':
            primeKey *= 3;
            break;

        case 'c':
            primeKey *= 5;
            break;

        case 'd':
            primeKey *= 7;
            break;

        case 'e':
            primeKey *= 11;
            break;

        case 'f':
            primeKey *= 13;
            break;

        case 'g':
            primeKey *= 17;
            break;

        default:
            std::cout << "Unreachable" << std::endl;
            return -1;
        }
    }

    return primeKey;
}

// Map starts as <primeProduct, characterCount> and leaves <primeProduct, intRepresentation>
void solvDigits(std::map<int, int> &keyVal)
{
    std::map<int, int>::iterator it;
    int one, four, seven, eight; // Knowns
    int zero, two, three, five, six, nine; // Unknowns
    int twoThreeFive = 0, zeroSixNine = 0; // Compounds

    for (it = keyVal.begin(); it != keyVal.end(); it++)
    {
        switch (it->second)
        {
        case 2:
            one = it->first;
            it->second = 1;
            break;
            
        case 3:
            seven = it->first;
            it->second = 7;
            break;

        case 4:
            four = it->first;
            it->second = 4;
            break;

        case 5:
            twoThreeFive *= it->first;
            break;

        case 6:
            zeroSixNine *= it->first;
            break;

        case 7:
            eight = it->first;
            it->second = 8;
            break;

        default:
            std::cout << "Unreachable" << std::endl;
            return;
        }
    }
    
    zero = (eight * sqrt(zeroSixNine)) / twoThreeFive;
}

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::map<int, int> keyVal;
    char c;
    int sum = 0, keyProd;

    while (!input.eof())
    {
        for (int i = 0; i < 10; i++)
        {
            input >> c;
            while (c != ' ')
            {

                input >> c;
            }
        }
    }

    // std::cout << "Ans. " << count << std::endl;
}