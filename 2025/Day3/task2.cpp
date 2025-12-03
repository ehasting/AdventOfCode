//
// Created by eh on 05/12/23.
//

#include "task2.hpp"

#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <regex>
#include <vector>
#include <execution>

void task2::Run()
{
    std::cout << this->TaskName << std::endl;
    std::ifstream file("testpayload.txt");
    std::string line;
    long sum = 0;
    while(getline(file, line))
    {
        int joltage = this->processLine(line);
        sum += joltage;

    }
    std::cout << this->TaskName << " SUM: " << sum <<std::endl;
}
