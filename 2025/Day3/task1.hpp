//
// Created by eh on 05/12/23.
//

#ifndef DAY1_TASK1_HPP
#define DAY1_TASK1_HPP
#include <cmath>
#include <iostream>
#include <vector>
#include <print>

class task1
{
public:
    std::string TaskName = "Task1";
    void Run();
    int processLine(const std::string &line)
    {
        bool first = true;
        char firstDigit = '0';
        char secondDigit = '0';


        std::println("{}", line);
        const int lineLength = line.length();
        int index = 0;

        start:;
        int highestDigitVal = 0;
        int firstSeenIndex = 0;
        for (; index < line.length();)
        {
            char d = line[index];
            int numericVal = d - '0';
            if (first)
            {
                if (index == lineLength - 2)
                {
                    if (numericVal > highestDigitVal)
                    {
                        firstDigit = d;
                    }
                    index++;
                    firstSeenIndex = index;
                    break;

                }
                if (numericVal == 9)
                {
                    firstDigit = d;
                    index++;
                    firstSeenIndex = index;
                    break;
                }
                else if (numericVal > highestDigitVal)
                {
                    highestDigitVal = numericVal;
                    firstDigit = d;
                }
            }
            else
            {
                if (numericVal > highestDigitVal)
                {
                    highestDigitVal = numericVal;
                    secondDigit = d;
                }
            }
            index++;
        }
        if (first)
        {
            first = false;
            goto start;
        }
        std::string digits;

            digits += firstDigit;
            digits += secondDigit;

        std::println("{0}", digits);
        return std::stoi(digits);
    }

};


#endif //DAY1_TASK1_HPP
