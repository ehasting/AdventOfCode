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
    long sum = 0;
    int linelength = 0;
    std::vector<char> payload;
    payload.reserve(19000);
    while(getline(file, line))
    {
        linelength = line.length();
        for (auto c : line)
        {
            payload.push_back(c);
        }
    }
    auto rval = this->processLine(payload, linelength);
    //this->draw(rval, linelength);
    std::cout << this->TaskName << " SUM: " << rval <<std::endl;
}
