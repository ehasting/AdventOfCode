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
    while(getline(file, line))
    {
        int joltage = this->processLine(line);
        sum += joltage;

    }
    std::cout << this->TaskName << " SUM: " << sum <<std::endl;
}
