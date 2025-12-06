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
    std::ifstream file("payload.txt");
    std::string line;
    Table2 currentTable;
    std::regex digits_regex("\\d+");
    std::regex art_regex("([\\+\\-\\*\\/])");
    std::vector<char> arts;
    while(getline(file, line))
    {
        bool hasmatch = false;
        std::vector<long> currentrow;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), digits_regex);
        auto digits_end = std::sregex_iterator ();
        long digitindex = 0;
        bool searchingfordigit = true;

        if (std::regex_search(line, digits_regex))
        {
            currentTable.Rows.push_back(line);
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
                arts.push_back(art[0]);
            }
        }
    }
    std::ranges::reverse(arts);
    currentTable.Arithmetics = arts;
    std::println("");

    long cursor = currentTable.Rows[0].size()-1;
    std::vector<long> currentrow;
    long vectorindex = 0;
    while (cursor > -1)
    {
        std::string digits = "";
        for (int i = 0; i < currentTable.Rows.size(); ++i)
        {
            //std::println("{}", currentTable.Rows[i][cursor]);
            digits += currentTable.Rows[i][cursor];
        }
        //std::println("{}", digits);
        if (this->is_digits(digits))
        {
            long digit = std::stol(digits);
            currentrow.push_back(digit);

        }
        else
        {
            auto _art = currentTable.Arithmetics[vectorindex];
            for (auto row : currentrow)
            {
                std::print("{} {} ", row, _art);
            }
            std::println("");

            currentTable.Table.push_back(currentrow);
            currentrow.clear();
            vectorindex++;
        }

        cursor--;
    }
    currentTable.Table.push_back(currentrow);

    long rval = currentTable.CalculateTable();
    /*
    for (auto &n: currentTable.Rows )
    {

        std::println("row length: {}", n.length());
    }
    */

    std::println("");
    std::println("{} SUM: {}", this->TaskName, rval);

}