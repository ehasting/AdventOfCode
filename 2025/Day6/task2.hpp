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
class Table2
{
public:
    std::vector<std::vector<long>> Table;
    std::vector<char> Arithmetics;
    std::vector<std::string> Rows;
    long CalculateTable()
    {
        long rval = 0;
        long i = 0;
        for (auto &t : Table)
        {
            auto art = Arithmetics[i];
            rval += CalculateVector(t, art);
            i++;
        }
        return rval;
    }
    long CalculateVector(std::vector<long> &row, char art)
    {
        long rval = 0;
        bool first = true;
        for (auto n : row)
        {
            if (first)
            {
                rval = n;
                first = false;
                continue;
            }
            auto prev = rval;
            rval = this->Calculate(art, rval, n);
            //std::println("{} = {} {} {}", rval, prev, art, n);
        }
        return rval;
    }

    long Calculate(char art, long currentsum, long newnum)
    {
        if (art == '*')
        {
            return currentsum *= newnum;
        }
        if (art == '/')
        {
            return currentsum /= newnum;
        }
        if (art == '+')
        {
            return currentsum += newnum;
        }
        if (art == '-')
        {
            return currentsum -= newnum;
        }
        return 0;
    }
};
class task2
{
public:
    double TotalTimeMs = 0;
    std::string TaskName = "Task2";
    void Run();
    bool is_digits(const std::string& str)
    {
        bool hasspace = false;
        bool hasdigit = false;
        for (char ch : str)
        {
            if (std::isspace(ch))
            {
                hasspace = true;
            }
            else if (!std::isdigit(ch))
            {
                return false;
            }
            else
            {
                hasdigit = true;
            }
        }
        if (hasspace && !hasdigit)
            return false; // All characters are digits
         return true;
    }

};


#endif //TASK2_HPP
