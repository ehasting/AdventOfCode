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

class Table1
{
public:
    std::vector<std::vector<long>> Table;
    std::vector<char> Arithmetics;
    long CalculateTable()
    {
        long rval = 0;
        for (long i = 0; i < Table[0].size(); i++)
        {
            rval += CalculateColumn(i);
        }
        return rval;
    }
    long CalculateColumn(long col)
    {

        auto art = Arithmetics[col];
        long rval = 0;
        bool first = true;
        for (auto n : this->Table)
        {
            if (first)
            {
                rval = n[col];
                first = false;
                continue;
            }
            auto prev = rval;
            rval = this->Calculate(art, rval, n[col]);
            std::print("{} = {} {} {}", rval, prev, art, n[col]);
        }
        std::println("{}", rval);
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

class task1
{
public:
    std::string TaskName = "Task1";
    const long MaxAdjRolls = 3;

    void Run();
};


#endif //TASK1_HPP
