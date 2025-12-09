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
#include "dataclass.hpp"

void task2::Run()
{
    std::cout << this->TaskName << std::endl;
    std::ifstream file("testpayload.txt");

    std::string line;
    Data currentTable;
    while(getline(file, line))
    {
        std::vector<char> row;
        for (auto &c: line)
        {
            row.push_back(c);
        }
        currentTable.Table.push_back(row);

    }
    currentTable.Compute();
    currentTable.Draw();


    long rval = 0;
    Data newTable = currentTable;
    std::vector<long> RowCount;




    long firstSplitterPos = -1;
    for (long i = 0; i < newTable.Table.size();i++)
    {
        for (long j = 0; j < newTable.Table[i].size();j++)
        {
            if (newTable.Table[i][j] == newTable.SplitterChar)
            {
                long currentCount = 0;
                firstSplitterPos = j;
                for (long inneri = i; inneri < newTable.Table.size();inneri = inneri + 2)
                {
                    if (newTable.Table[inneri][firstSplitterPos] == newTable.SplitterChar)
                    {
                        newTable.Table[inneri][firstSplitterPos] = '0';
                        currentCount++;
                    }
                    firstSplitterPos--;
                    if (firstSplitterPos < 0)
                        break;
                }
                RowCount.push_back(currentCount);
            }

        }

    }



    rval = 0;
    for (auto &n : RowCount)
    {
        if (n == 1 || n == 0)
            continue;
        std::print("({} * 2) + ", n);
        rval += (n*2);
    }
    /*
        std::string output;
        currentTable.Trace(currentTable.StartBeam, output);
        std::println("{}", output);
    */

    std::print("{} SUM: {}", this->TaskName, rval);
}