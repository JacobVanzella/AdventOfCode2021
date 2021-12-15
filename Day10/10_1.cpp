#include <fstream>
#include <iostream>
#include <stack>

int main (int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::stack<char> openClose;
    bool mismatch;
    char nextChar;
    int score = 0;

    while (!input.eof())
    {
        mismatch = false;
        input >> nextChar;

        switch (nextChar)
        {
        case ')':
            mismatch = openClose.top() != '(';
            if (mismatch)
                score += 3;
            else
                openClose.pop();
            break;

        case ']':
            mismatch = openClose.top() != '[';
            if (mismatch)
                score += 57;
            else
                openClose.pop();
            break;

        case '}':
            mismatch = openClose.top() != '{';
            if (mismatch)
                score += 1197;
            else
                openClose.pop();
            break;

        case '>':
            mismatch = openClose.top() != '<';
            if (mismatch)
                score += 25137;
            else
                openClose.pop();
            break;
        
        default:
            openClose.push(nextChar);
            break;
        }
        
        // Ignore remainder of line if mismatched
        if (mismatch)
            input.ignore(1024, '\n');
    }
    
    std::cout << "Ans. " << score << std::endl;
}