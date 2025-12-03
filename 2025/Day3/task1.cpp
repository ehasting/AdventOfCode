//
// Created by eh on 05/12/23.
//

#include "task1.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <numeric>


void task1::Run()
{
    std::cout << this->TaskName << std::endl;
    std::ifstream file("payload.txt");
    std::string line;
    std::regex digits_regex("(\\d*)-(\\d*),");
    int pass = 50;
    int zeroCount = 0;
    std::vector<long> badIds;
    while(getline(file, line))
    {
        std::vector<std::string> digit;
        //std::cout << line << std::endl;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), digits_regex);
        auto digits_end = std::sregex_iterator ();

        for (auto n =  digits_begin; n != digits_end; ++n)
        {
            std::smatch m = *n;
            auto firstId = std::stol(m.str(1));
            auto lastId = std::stol(m.str(2));
            auto rval = this->processRange(firstId, lastId);
            if (!rval.empty())
                badIds.insert(badIds.end(), rval.begin(), rval.end());
            //std::cout << firstId << " !! " << lastId << std::endl;

        }

    }
    auto result = std::reduce(badIds.begin(), badIds.end());
    std::cout << this->TaskName << " SUM: " << result <<std::endl;
}
