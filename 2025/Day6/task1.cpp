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
    Table1 currentTable;
    long rowindex = 0;
    long colindex = 0;
    std::regex digits_regex("(\\d*)");
    std::regex art_regex("([\\+\\-\\*\\/])");
    while(getline(file, line))
    {
        bool hasmatch = false;
        std::vector<long> currentrow;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), digits_regex);
        auto digits_end = std::sregex_iterator ();
        for (auto n =  digits_begin; n != digits_end; ++n)
        {

            std::smatch m = *n;

            std::string digit = m.str(1);
            if (digit.empty())
            {
                continue;
            }
            hasmatch = true;
            std::print("{} ",digit);;
            currentrow.push_back(std::stol(digit));
        }
        std::println("");
        if (hasmatch)
        {
            currentTable.Table.push_back(currentrow);
        }
        else
        {
            auto art_begin = std::sregex_iterator(line.begin(), line.end(), art_regex);
            auto art_end = std::sregex_iterator ();
            for (auto n =  art_begin; n != art_end; ++n)
            {
                std::smatch m = *n;
                std::string art = m.str(1);
                if (art.empty())
                {
                    continue;
                }
                std::print("{} ", art);
                currentTable.Arithmetics.push_back(art[0]);
            }
        }
    }
    for (auto &n: currentTable.Table)
    {
        for (auto &nn: n)
        {
            std::print("{} ", nn);
        }
        std::println("");
    }


    long rval = currentTable.CalculateTable();
    std::cout << this->TaskName << " SUM: " << rval <<std::endl;
}
