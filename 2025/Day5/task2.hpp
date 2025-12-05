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

class Range2
{
public:
    long From;
    long To;
    bool IsFromOutside;
    bool IsToOutside;
    Range2 Evaluate(Range2 compare)
    {
        auto end1 = compare.To;
        auto start2 = From;
        auto end2 = To;
        auto start1 = compare.From;
        bool notOverlap = (end1 < start2) || (end2 < start1);
        if (notOverlap)
            return compare;

        if (compare.From > From)
            IsFromOutside = true;
        if (compare.To < To)
            IsToOutside = true;

        if (IsFromOutside)
            compare.From = From;
        if (IsToOutside)
            compare.To = To;

    }

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
