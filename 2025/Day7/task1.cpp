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
#include "dataclass.hpp"


void task1::Run()
{
    std::cout << this->TaskName << std::endl;
    std::ifstream file("payload.txt");

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
    long rowi = 0;

    long rval = 0;
    for (auto &row : currentTable.Table)
    {
        long coli = 0;
        for (auto &col : row)
        {
            if (col == currentTable.SplitterChar && currentTable.Table.at(rowi-1).at(coli) == currentTable.BeamChar )
            {
                rval++;
            }
            coli++;
        }
        rowi++;
    }

    std::cout << this->TaskName << " SUM: " << rval <<std::endl;
}
