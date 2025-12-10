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
    std::vector<char> row;
    while(getline(file, line))
    {
        row.clear();
        bool linewaswithsplitters = false;
        for (auto &c: line)
        {
            if (c == '^' || c == 'S') {linewaswithsplitters = true;}
            row.push_back(c);
        }
        if (linewaswithsplitters)
            currentTable.Table.push_back(row);

    }
    currentTable.Table.push_back(row);
    currentTable.Draw();
    std::println("");
    currentTable.Compute();
    currentTable.MapBtree(currentTable.BinaryTree);
    std::println("next id: {}", Leaf::s_nextId.load());
    currentTable.Draw();


    long rval = 0;



    /*
        std::string output;
        currentTable.Trace(currentTable.StartBeam, output);
        std::println("{}", output);
    */

    std::print("{} SUM: {}", this->TaskName, rval);
}