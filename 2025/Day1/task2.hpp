//
// Created by eh on 05/12/23.
//

#ifndef DAY2_TASK2_HPP
#define DAY2_TASK2_HPP
#include <cmath>
#include <iostream>

class task2
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
    int isZeroCross(int current, int newnum, bool isPositive)
    {
        int rval = 0;
        //std::cout <<"!! isZeroCross: " << current << std::endl;
        while (newnum > 0)
        {
            current += isPositive ? 1 : -1;
            if (current > 99)
                current = 0;
            if (current < 0)
                current = 99;
            if (current == 0)
                rval++;
            newnum -= 1;
            //std::cout <<"calculateNewCode: " << current << std::endl;
        }

        return rval;
    }
};


#endif //DAY1_TASK2_HPP
