//
// Created by eh on 05/12/23.
//

#include "task2.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

void task2::Tests()
{
    std::string str = "2eightwo8fmktlf";
    std::regex re1("(?=(\\d|one|two|three|four|five|six|seven|eight|nine))."); // ECMA
    auto digits_begin = std::sregex_iterator(str.begin(), str.end(), re1);
    auto digits_end = std::sregex_iterator ();
    for (auto n =  digits_begin; n != digits_end; n++) {
        std::smatch match = *n;
        std::cout << match.str(1) << std::endl;
    }
}

void task2::Run()
{
    std::cout << "Task2" << std::endl;
    std::ifstream file("payload.txt");
    std::string line;
    std::regex digits_regex("(?=(\\d|one|two|three|four|five|six|seven|eight|nine)).", std::regex::ECMAScript);
    int sum = 0;
    int linecount = 0;
    std::vector<int> digit;
    while(getline(file, line))
    {
        linecount++;
        if (line.empty())
            continue;
        digit.clear();
        std::cout << line << " :: ";
        std::cout << std::endl;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), digits_regex);
        auto digits_end = std::sregex_iterator ();

        for (auto n =  digits_begin; n != digits_end; n++)
        {
            std::smatch m = *n;
            std::string val = m.str(1);
            std::cout << val << std::endl;
            if (val.empty())
                continue;

            if (val == "one")
            {
                digit.emplace_back(1);
            }
            else if (val == "two")
            {
                digit.emplace_back(2);
            }
            else if (val == "three")
            {
                digit.emplace_back(3);
            }
            else if (val == "four")
            {
                digit.emplace_back(4);
            }
            else if (val == "five")
            {
                digit.emplace_back(5);
            }
            else if (val == "six")
            {
                digit.emplace_back(6);
            }
            else if (val == "seven")
            {
                digit.emplace_back(7);
            }
            else if (val == "eight")
            {
                digit.emplace_back(8);
            }
            else if (val == "nine")
            {
                digit.emplace_back(9);
            }
            else
            {
                digit.emplace_back(std::stoi(val));
            }

            //std::cout << " " << digit.back() << " | ";
        }

        if (!digit.empty()) {
            std::string computedigit = std::to_string(digit.front()) + std::to_string(digit.back());
            int founddigit = std::stoi(computedigit);
            std::cout << sum << " + " << founddigit << " = " << sum+founddigit << std::endl;
            sum = sum + founddigit;

        }

    }
    std::cout << "Task2 SUM: " << sum << " Line count:  " << linecount << std::endl;
}
