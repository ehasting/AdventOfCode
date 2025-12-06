//
// Created by eh on 05/12/23.
//

#ifndef TASK1_HPP
#define TASK1_HPP
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <print>

struct Range
{
    long From;
    long To;
};

class task1
{
public:
    std::string TaskName = "Task1";
    const long MaxAdjRolls = 3;

    std::vector<Range> Ranges;
    void Run();

    void loadRange(std::string &line)
    {
        long digitfrom = 0;
        long digitto = 0;
        std::string buffer;
        for (auto c : line)
        {
            if (c == '-')
            {
                digitfrom = std::stol(buffer);
                buffer = "";
                continue;
            }
            buffer += c;
        }
        digitto = std::stol(buffer);
        Ranges.push_back(Range(digitfrom, digitto));

    }
    long testId(std::string &line)
    {
        auto digit = std::stol(line);
        for (auto range : Ranges)
        {
            std::println("{} : {}-{}",digit, range.From, range.To);
            if (digit >= range.From && digit <= range.To)
            {

                return 1;
            }
        }
        return 0;
    }

};


#endif //TASK1_HPP
