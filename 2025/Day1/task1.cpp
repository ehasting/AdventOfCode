//
// Created by eh on 05/12/23.
//

#include "task1.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

void task1::Run()
{

    std::cout << "Task1" << std::endl;
    std::ifstream file("payload.txt");
    std::string line;
    std::regex digits_regex("(.)(\\d*)");
    int pass = 50;
    int zeroCount = 0;
    while(getline(file, line))
    {
        std::vector<std::string> digit;
        //std::cout << line << std::endl;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), digits_regex);
        auto digits_end = std::sregex_iterator ();

        for (auto n =  digits_begin; n != digits_end; ++n)
        {
            std::smatch m = *n;
            //digit.push_back(m.str());
            auto dir = m.str(1);
            auto num = std::stoi(m.str(2));
            bool isZero = false;
            if (dir == "R") {
                isZero = this->isZeroCross(pass, num, true);
                pass = this->calculateNewCode(pass, num, true);
            }
            else if (dir == "L") {
                isZero = this->isZeroCross(pass, num, false);
                pass = this->calculateNewCode(pass, num, false);
            }
            if (isZero)
            {
                zeroCount++;
            }

        }

    }
    std::cout << "Task1 SUM: " << zeroCount <<std::endl;
}
