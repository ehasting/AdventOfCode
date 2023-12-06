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
    std::regex digits_regex("(\\d)");
    long sum = 0;
    while(getline(file, line))
    {
        std::vector<std::string> digit;
        //std::cout << line << std::endl;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), digits_regex);
        auto digits_end = std::sregex_iterator ();

        for (auto n =  digits_begin; n != digits_end; ++n)
        {
            std::smatch m = *n;
            digit.push_back(m.str());
            //std::cout << m.str();
        }
        if (!digit.empty()) {
            std::string computedigit = digit.front() + "" + digit.back();
            sum = sum + std::stol(computedigit);
        }

    }
    std::cout << "Task1 SUM: " << sum <<std::endl;
}
