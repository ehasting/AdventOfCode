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
        const long lineLength = line.length();
        int index = 0;

        start:;
        int highestDigitVal = 0;
        int firstSeenIndex = -1;
        for (; index < line.length();index++)
        {
            char d = line[index];
            int numericVal = d - '0';
            if (first)
            {
                if (numericVal == 9)
                {
                    firstDigit = d;
                    firstSeenIndex = index;
                    break;
                }
                if (numericVal > highestDigitVal)
                {
                    highestDigitVal = numericVal;
                    firstSeenIndex = index;
                    firstDigit = d;
                }
                if (index == lineLength - 2)
                {
                    break;
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
        }
        if (first)
        {
            first = false;
            if (firstSeenIndex != -1) {
                index = firstSeenIndex;
            }
            std::println("first: {0} {1}", index, firstDigit);
            index++;
            goto start;
        }
        else {
            std::println("second: {0} {1}", index, secondDigit);
        }
        std::string digits;

        digits += firstDigit;
        digits += secondDigit;

        std::println("{0}", digits);
        return std::stoi(digits);
    }

};


#endif //DAY1_TASK1_HPP
