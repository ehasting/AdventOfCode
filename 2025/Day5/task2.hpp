//
// Created by eh on 05/12/23.
//

#ifndef TASK2_HPP
#define TASK2_HPP
#include <cmath>
#include <iostream>
#include <vector>
#include <print>
#include <algorithm>
#include <execution>
#include <ctime>
#include <ranges>
#include <chrono>
#include <unordered_map>

struct Range2
{
    long From;
    long To;
};

class task2
{
public:
    double TotalTimeMs = 0;
    std::string TaskName = "Task2";
    void Run();
    std::vector<Range2> Ranges;
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
        Ranges.push_back(Range2(digitfrom, digitto));

    }
    long countIds()
    {
        std::unordered_map<long, bool> ids;
        std::unordered_map<int, std::string> myMap = {{1, "apple"}, {2, "banana"}};
        int keyToCheck = 2;



        long rval = 0;
        for (auto range : Ranges)
        {
            for (long i = range.From; i <= range.To; i++)
            {
                if (ids.find(i) == ids.end())
                {
                    rval++;
                    ids[i] = true;
                }
            }
        }
    return rval;
    }

};


#endif //TASK2_HPP
