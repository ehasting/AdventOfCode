//
// Created by eh on 05/12/23.
//

#ifndef DAY2_TASK2_HPP
#define DAY2_TASK2_HPP
#include <cmath>
#include <iostream>
#include <vector>
#include <print>
#include <algorithm>
#include <execution>
#include <ctime>
#include <ranges>
#include <chrono>

class task2
{
public:
    double TotalTimeMs = 0;
    std::string TaskName = "Task2";
    void Run();
    std::mutex mtx; // Mutex to protect myVector
    int processLine(const std::string &line)
    {
        std::vector<char> digits;
        int digitIndex = 0;
        const int MaxDigits = 12;


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


#endif //DAY1_TASK2_HPP
