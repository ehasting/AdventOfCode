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
    long processLine(const std::string &line)
    {
        std::vector<char> digits;
        int lastDigitIndex = 0;
        const int MaxDigits = 12;

        // std::println("{}", line);
        int index = 0;
        for (int digitIndex = 0; digitIndex < MaxDigits; digitIndex++)
        {
            int currentHighestDigits = 0;
            int currentLowestIndex = -1;
            char currentHighestDigitChar = ' ';
            int capLength = (line.length() - MaxDigits) + digitIndex;
            for (; index < capLength+1;index++)
            {

                char d = line[index];
                int numericVal = d - '0';

                if ((currentHighestDigits < numericVal) && (currentLowestIndex < capLength))
                {
                    currentHighestDigits = numericVal;
                    currentLowestIndex = index;
                    currentHighestDigitChar = d;
                }
            }
            digits.push_back(currentHighestDigitChar);
            index = currentLowestIndex + 1 ;
        }

        std::string digitsString;
        for (auto d : digits)
        {
            digitsString += d;
        }

        std::println("new digitstring: {0}", digitsString);
        return std::stol(digitsString);
    }
};


#endif //DAY1_TASK2_HPP
