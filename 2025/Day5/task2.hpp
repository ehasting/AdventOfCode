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

    long Min;
    long Max;

    bool IsOverlap(const std::shared_ptr<Range2>& compare)
    {
        if (!isRangeInsideRange(compare, std::make_shared<Range2>(*this)))
            return false;
        if (this->Min > compare->Min)
            this->Min = compare->Min;
        if (this->Max < compare->Max)
            this->Max = compare->Max;
        return true;
    }
private:
    static bool isRangeInsideRange(std::shared_ptr<Range2> a, std::shared_ptr<Range2> b) {
        return a->Min <= b->Max && b->Min <= a->Max;
    }

};

class task2
{
public:
    double TotalTimeMs = 0;
    std::string TaskName = "Task2";
    void Run();
    std::vector<std::shared_ptr<Range2>> Ranges;
    void loadRange(const std::string &line)
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
        Ranges.push_back(std::make_shared<Range2>(Range2(digitfrom, digitto)));

    }
    long countIds()
    {
        long rval = 0;

        start:
        std::println("Starting. Ranges size: {}", Ranges.size());
        /*
        for (auto range : Ranges)
        {
            std::println("{} - {}", range->Min, range->Max);
        }
        */
        for (int i = 0; i < Ranges.size(); i++)
        {
            auto range = Ranges[i];
            for (int inneri = 0; inneri < Ranges.size(); inneri++)
            {
                auto innerrange = Ranges[inneri];

                if (i == inneri)
                {
                    continue;
                }

                if (range->IsOverlap(innerrange))
                {
                    std::println("Deleting {} - {} [{}] (is matching {} - {} [{}])", innerrange->Min, innerrange->Max, inneri, range->Min, range->Max, i);
                    Ranges.erase(Ranges.begin() + inneri);
                    goto start;
                }
            }
        }

        for (auto range : Ranges)
        {
            rval += (range->Max - range->Min) + 1;
        }
        return rval;
    }

};


#endif //TASK2_HPP
