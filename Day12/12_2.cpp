#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <ctype.h>

typedef enum
{
    start,
    small,
    large,
    end
} STYLE;

struct cave
{
    bool visited;
    STYLE style;
    std::string name;
    std::vector<cave *> neighbours;
};

STYLE getStyle(const std::string &name)
{
    if (name.compare("start") == 0)
        return start;
    else if (name.compare("end") == 0)
        return end;
    else if (isupper(name[0]))
        return large;
    else
        return small;
}

std::vector<cave> debug;
int DFS(cave *vertex, std::map<std::string, bool> &LUT)
{
    bool looped = false;
    int32_t pcnt = 0;
    vertex->visited = true;

    // Update lookup table forwards
    if (vertex->style == small && !LUT.count(vertex->name))
        LUT.emplace(vertex->name, false);
    else if (LUT.count(vertex->name))
        LUT.at(vertex->name) = true;
    // Check if a small cave has been visited twice
    for (auto val : LUT)
        looped = looped || val.second;
    
    // Recurse over neighbours
    for (auto neighbor : vertex->neighbours)
        if ((!neighbor->visited && !LUT.count(neighbor->name)) || neighbor->style == large || (neighbor->style == small && !looped))
            pcnt += DFS(neighbor, LUT);

    // Reset visited status so path can be restepped from alternate source
    if (vertex->style != start)
        vertex->visited = false;

    // Update lookup table backwards
    if (LUT.count(vertex->name))
        if (LUT.at(vertex->name))
            LUT.at(vertex->name) = false;
        else
            LUT.erase(vertex->name);

    return vertex->name.compare("end") == 0 ? pcnt + 1 : pcnt;
}

int main(int argc, char *argv[])
{
    std::fstream input("input.txt");
    std::stringstream inputStr;
    std::map<std::string, cave> canonicalMap;
    std::map<std::string, bool> LUT;
    std::string tmpStr, left, right;

    // Build cave graph (I fucking love graphs <3)
    while (!input.eof())
    {
        // Condition input
        std::getline(input, tmpStr);
        std::replace(tmpStr.begin(), tmpStr.end(), '-', ' ');

        inputStr.str(tmpStr);
        inputStr >> left;
        inputStr >> right;
        inputStr.clear();

        // Add caves to canonical map of caves
        canonicalMap.insert(std::pair<std::string, cave>(left, cave{false, getStyle(left), left}));
        canonicalMap.insert(std::pair<std::string, cave>(right, cave{false, getStyle(right), right}));

        // Add edges to caves
        canonicalMap.at(left).neighbours.emplace_back(&canonicalMap.at(right));
        canonicalMap.at(right).neighbours.emplace_back(&canonicalMap.at(left));
    }
    // Make edges connecting to end directed
    canonicalMap.at("end").neighbours.clear();

    std::cout << "Ans. " << DFS(&canonicalMap.at("start"), LUT) << std::endl;
}