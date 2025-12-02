//
// Created by eh on 05/12/23.
//

#ifndef DAY1_TASK1_HPP
#define DAY1_TASK1_HPP
#include <cmath>
#include <iostream>
#include <vector>

class task1
{
public:
    std::string TaskName = "Task1";
    void Run();
    std::vector<long> processRange(const long startId, const long stopId)
    {
        std::vector<long> rval;
        for (long i = startId; i <= stopId; i++)
        {
            //std::cout << i << std::endl;
            if (this->hasInvalidId(i))
            {
                std::cout << i << std::endl;
                rval.push_back(i);
            }

        }

        return rval;
    }
    bool hasInvalidId(long value)
    {
        const std::string str_number = std::to_string(value);
        const std::string lower = str_number.substr(0, (str_number.size()) / 2);
        const std::string higher = str_number.substr((str_number.size() ) / 2);
        if (lower == higher)
            return true;
        //std::cout << lower << " <-lower|higher-> " << higher << std::endl;
        return false;
    }

};


#endif //DAY1_TASK1_HPP
