//
// Created by eh on 07.12.2025.
//

#ifndef DAY5_DATACLASS_HPP
#define DAY5_DATACLASS_HPP
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <print>

class Coord
{
public:
    long X;
    long Y;
    Coord()
    {
        X = 0;
        Y = 0;
    }
    Coord(const long x, const long y)
    {
        X = x;
        Y = y;
    }
};

class Data
{
    public:
    const char StartChar = 'S';
    const char EmptyChar = '.';
    const char SplitterChar = '^';
    const char BeamChar = '|';
    Coord StartBeam;
    std::vector<std::vector<char>> Table;
    long Cols = 0;
    long Rows = 0;
    long GlobalTraceCounter = 0;
    void Draw()
    {
        for (auto &row : Table)
        {
            for (auto &col : row)
            {
                std::print("{}", col);
            }
            std::println("");
        }
    }
    char GetCharAtCoord(const Coord &coord)
    {
        return this->Table.at(coord.Y).at(coord.X);
    }
    void SetCharAtCoord(const Coord &coord, const char c)
    {
        this->Table.at(coord.Y).at(coord.X) = c;
    }
    void SetBeamsAtSplitter(const Coord &splittercoord)
    {
        this->Table.at(splittercoord.Y).at(splittercoord.X-1) = BeamChar;
        this->Table.at(splittercoord.Y).at(splittercoord.X+1) = BeamChar;
    }

    Coord JumpDown(const Coord &coord)
    {
        Coord newCoord(coord.X, coord.Y);
        newCoord.Y++;
        return newCoord;
    }
    void SplitBeam(const Coord &splittercoord)
    {
        SetBeamsAtSplitter(splittercoord);
        Coord branchl(splittercoord.X - 1, splittercoord.Y);
        Coord branchr(splittercoord.X + 1, splittercoord.Y);
        CheckBranch(branchl);
        CheckBranch(branchr);

    }
    void CheckBranch(const Coord &coord)
    {
        auto newCoord = JumpDown(coord);
        if (newCoord.Y > Rows - 1)
            return;
        if (GetCharAtCoord(newCoord) == SplitterChar)
        {
            SplitBeam(newCoord);
        }
        else if (GetCharAtCoord(newCoord) == EmptyChar)
        {
            SetCharAtCoord(newCoord, BeamChar);
            CheckBranch(newCoord);
        }
        else if (GetCharAtCoord(newCoord) == BeamChar)
        {
            //CheckBranch(coord);
        }
    }
    void Compute()
    {
        Cols = this->Table.at(0).size();
        Rows = this->Table.size();

        long currentRow = 0;
        long currentCol = 0;

        for (long j = 0; j < Cols; j++)
        {
            if (this->Table.at(currentRow).at(j) == StartChar)
            {
                currentCol = j;
                this->Table.at(currentRow+1).at(j) = BeamChar;
                currentRow++;
                break;
            }
        }
        Coord current(currentCol, 1);
        StartBeam.Y = current.Y;
        StartBeam.X = current.X;
        CheckBranch(current);
    }
    void Trace(const Coord &coord, std::string &output)
    {
        auto newCoord = JumpDown(coord);
        if (newCoord.Y > Rows - 1)
            return;
        auto currentChar = GetCharAtCoord(newCoord);
        //std::println("{}", currentChar);
        if (currentChar == SplitterChar)
        {
            TraceSplitBeam(newCoord, output);
        }
        else if (currentChar == BeamChar)
        {
            JumpDown(newCoord);
            Trace(newCoord, output);
        }

    }
    void TraceSplitBeam(const Coord &coord, std::string &output)
    {
        Coord l(coord.X - 1, coord.Y);
        output += "L";
        Trace(l, output);
    }
};
#endif //DAY5_DATACLASS_HPP