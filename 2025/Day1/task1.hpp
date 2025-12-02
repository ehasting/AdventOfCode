//
// Created by eh on 05/12/23.
//

#ifndef DAY1_TASK1_HPP
#define DAY1_TASK1_HPP
#include <cmath>
#include <iostream>

class task1
{
public:
    void Run();
    bool isPositive(int num)
    {
        return num > 0;
    }
    int calculateNewCode(int current, int newnum, bool isPositive)
    {
       // std::cout << "!! calculateNewCode: " << newnum << std::endl;
        while (newnum > 0)
        {
            current += isPositive ? 1 : -1;
            if (current > 99)
                current = 0;
            if (current < 0)
                current = 99;
            newnum -= 1;
            //std::cout <<"calculateNewCode: " << current << std::endl;
        }

        return current;
    }
    bool isZeroCross(int current, int newnum, bool isPositive)
    {
        //std::cout <<"!! isZeroCross: " << current << std::endl;
        while (newnum > 0)
        {
            current += isPositive ? 1 : -1;
            if (current > 99)
                current = 0;
            if (current < 0)
                current = 99;
            newnum -= 1;
            //std::cout <<"calculateNewCode: " << current << std::endl;
        }
        if (current == 0)
            return true;
        return false;
    }
};


#endif //DAY1_TASK1_HPP
