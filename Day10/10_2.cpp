#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::stack<char> openClose;
    std::vector<long long> scoreList;
    bool mismatch, endOfFile = false;
    char nextChar;
    long long score = 0;

    while (!endOfFile)
    {
        mismatch = false;

        // Populate stack
        if (input.peek() != '\n' && !input.eof())
        {
            input >> nextChar;
            switch (nextChar)
            {
            case ')':
                mismatch = openClose.top() != '(';
                if (!mismatch)
                    openClose.pop();
                break;

            case ']':
                mismatch = openClose.top() != '[';
                if (!mismatch)
                    openClose.pop();
                break;

            case '}':
                mismatch = openClose.top() != '{';
                if (!mismatch)
                    openClose.pop();
                break;

            case '>':
                mismatch = openClose.top() != '<';
                if (!mismatch)
                    openClose.pop();
                break;

            default:
                openClose.push(nextChar);
                break;
            }

            // Ignore remainder of line if mismatched and dump stack
            if (mismatch)
            {
                input.ignore(1024, '\n');
                while (!openClose.empty())
                    openClose.pop();
            }
        }
        // Calculate score and dump stack
        else
        {
            score = 0;
            while (!openClose.empty())
            {
                switch (openClose.top())
                {
                case '(':
                    score = (score * 5L) + 1L;
                    break;

                case '[':
                    score = (score * 5L) + 2L;
                    break;

                case '{':
                    score = (score * 5L) + 3L;
                    break;

                case '<':
                    score = (score * 5L) + 4L;
                    break;

                default:
                    std::cout << "Unreachable" << std::endl;
                    return -1;
                }

                openClose.pop();
            }
            
            // Store score and ignore '\n'
            scoreList.emplace_back(score);
            input.ignore(1, ' ');
            if (input.eof())
                endOfFile = true;
        }
    }
    
    std::sort(scoreList.begin(), scoreList.end());
    score = scoreList[scoreList.size() / 2];
    
    std::cout << "Ans. " << score << std::endl;
}