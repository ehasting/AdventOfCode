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

    for (long i = 0; i < newTable.Table.size(); i++)
    {
        long cursorIndex = 0;
        auto &row = newTable.Table[i];
        bool foundbeam = false;
        bool anythingfound = false;
        for (auto &col : row)
        {
            if (col == newTable.SplitterChar)
            {
                anythingfound = true;
                foundbeam = false;
                if (RowCount.size() < cursorIndex+1)
                {
                    std::println("Creating {}", cursorIndex);
                    RowCount.push_back(1);
                }
                else
                {
                    std::println("Adding to {}", cursorIndex);
                    RowCount[cursorIndex]++;
                }
            }
            else if (col == newTable.BeamChar && foundbeam)
            {
                //std::println("- Found Second BeamChar ");
                foundbeam = false;
                cursorIndex++;
            }
            else if (col == newTable.BeamChar)
            {
                //std::println("- Found First BeamChar ");
                foundbeam = true;
            }
        }
        if (anythingfound)
            std::println("--------");

    }

    newTable.Draw();
    rval = 0;
    for (auto &n : RowCount)
    {
        std::print("({} * 2) + ", n);
        rval += (n*2);
    }
/*
    std::string output;
    currentTable.Trace(currentTable.StartBeam, output);
    std::println("{}", output);
*/

    std::cout << this->TaskName << " SUM: " << rval <<std::endl;
}