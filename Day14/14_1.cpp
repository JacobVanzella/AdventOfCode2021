#include <fstream>
#include <iostream>
#include <map>
#include <string>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

void updatePolymere(
    const std::string &link,
    std::map<std::string, int32_t> &links,
    std::map<std::string, int32_t> &tmpLinks,
    std::map<std::string, std::string> &rules)
{
    if (links.at(link) == 0)
        return;

    std::string newLink1 = link.substr(0, 1) + rules.at(link);
    std::string newLink2 = rules.at(link) + link.substr(1, 1);

    if (!tmpLinks.count(newLink1))
        tmpLinks.emplace(newLink1, links.at(link));
    else
        tmpLinks.at(newLink1) += links.at(link);

    if (!tmpLinks.count(newLink2))
        tmpLinks.emplace(newLink2, links.at(link));
    else
        tmpLinks.at(newLink2) += links.at(link);

    tmpLinks.at(link) -= links.at(link);
}

int main(int argc, char *argv[])
{
    int32_t steps = 10, min = INT_MAX, max = INT_MIN;
    std::string pair, put, pTemplate;
    std::fstream input("input.txt");
    std::map<char, int32_t> occurences;
    std::map<std::string, int32_t> links, tmpLinks;
    std::map<std::string, std::string> rules;

    // Get initial template pair
    input >> pTemplate;
    input.ignore(1, ' ');
    for (int32_t i = 0; i < pTemplate.size() - 1; i++)
    {
        if (!links.count(pTemplate.substr(i, 2)))
            links.emplace(pTemplate.substr(i, 2), 1);
        else
            links.at(pTemplate.substr(i, 2))++;
    }

    // Get polymerization rules
    while (!input.eof())
    {
        input >> pair;
        input.ignore(4, '\n');
        input >> put;
        rules.emplace(pair, put);

        if (!occurences.count(pair[0]))
            occurences.emplace(pair[0], 0);
        if (!occurences.count(pair[1]))
            occurences.emplace(pair[1], 0);
    }

    // Create the polymere chain
    for (int32_t i = 0; i < steps; i++)
    {
        tmpLinks = links;
        for (auto link : links)
            updatePolymere(link.first, links, tmpLinks, rules);
        links = tmpLinks;
    }

    // Count elements in the chain
    for (auto link : links)
        occurences.at(link.first[0]) += link.second;
    occurences.at(pTemplate[pTemplate.size() - 1])++;

    // Find the largest and smallet values
    for (auto element : occurences)
    {
        min = min > element.second ? element.second : min;
        max = max < element.second ? element.second : max;
    }

    std::cout << "Ans. " << max << " - " << min << " = " << max - min << std::endl;
}