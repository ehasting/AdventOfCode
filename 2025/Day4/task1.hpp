//
// Created by eh on 05/12/23.
//

#ifndef TASK1_HPP
#define TASK1_HPP
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <print>

class Matrix
{
    public:
    long NorthWest;
    long North;
    long NorthEast;
    long East;
    long SouthEast;
    long South;
    long SouthWest;
    long West;
    long Center;
    long CurrentRow;
    long CurrentCol;
    long Cols;
    std::shared_ptr<std::vector<char>> Line;
    long Pos;


    Matrix(std::vector<char> &line, const long cols, const long CurrentPos)
    {
        this->Pos = CurrentPos;
        this->Cols = cols;
        this->Line = std::make_shared<std::vector<char>>(line);
        this->CurrentRow = std::floor(CurrentPos / cols);
        this->CurrentCol = CurrentPos - (this->CurrentRow * cols);

        this->South = (this->CurrentRow+1) * cols + (this->CurrentCol);
        this->SouthEast = (this->CurrentRow+1) * cols + (this->CurrentCol + 1);
        this->SouthWest = (this->CurrentRow+1) * cols + (this->CurrentCol - 1);

        this->West = CurrentPos - 1;
        this->East = CurrentPos + 1;

        this->North = (this->CurrentRow-1) * cols + (this->CurrentCol);
        this->NorthEast = (this->CurrentRow-1) * cols + (this->CurrentCol + 1);
        this->NorthWest = (this->CurrentRow-1) * cols + (this->CurrentCol - 1);

        this->Center = CurrentPos;
    }
    long GetRollCount()
    {
        long rval = 0;
        if (this->CurrentCol == 0)
        {
            rval += this->CheckIfTogetherWithPaper(this->North);
            rval += this->CheckIfTogetherWithPaper(this->NorthEast);
            rval += this->CheckIfTogetherWithPaper(this->East);
            rval += this->CheckIfTogetherWithPaper(this->SouthEast);
            rval += this->CheckIfTogetherWithPaper(this->South);
        }
        else if (this->CurrentCol == this->Cols-1)
        {
            rval += this->CheckIfTogetherWithPaper(this->North);
            rval += this->CheckIfTogetherWithPaper(this->NorthWest);
            rval += this->CheckIfTogetherWithPaper(this->West);
            rval += this->CheckIfTogetherWithPaper(this->SouthWest);
            rval += this->CheckIfTogetherWithPaper(this->South);
        }
        else
        {
            rval += this->CheckIfTogetherWithPaper(this->North);
            rval += this->CheckIfTogetherWithPaper(this->NorthEast);
            rval += this->CheckIfTogetherWithPaper(this->East);
            rval += this->CheckIfTogetherWithPaper(this->SouthEast);
            rval += this->CheckIfTogetherWithPaper(this->South);
            rval += this->CheckIfTogetherWithPaper(this->SouthWest);
            rval += this->CheckIfTogetherWithPaper(this->West);
            rval += this->CheckIfTogetherWithPaper(this->NorthWest);
        }
        return rval;
    }
    long CheckIfTogetherWithPaper(long pos)
    {
        if (this->isInsideBounds(pos))
        {
            auto c = this->Line->at(pos);
            if (c == '@')
            {
                return 1;
            }
            else if (c == '.')
            {

            }
        }
        return 0;
    }
    bool isInsideBounds(long position)
    {
        if (position >= 0 && position < this->Line->size())
            return true;
        return false;
    }
};

class task1
{
public:
    std::string TaskName = "Task1";
    const long MaxAdjRolls = 3;

    void Run();

    long processLine(std::vector<char> &line, const long cols)
    {
        std::println("length: {}, rows: {}", line.size(), line.size() / cols);

        long currentCharIndex = 0;
        long rval = 0;
        std::vector<char> drawing = line;
        for (auto c : line)
        {
            if (c == '.')
            {
                currentCharIndex++;
                continue;
            }
            if (currentCharIndex == 49)
                std::print("");

            Matrix n(line, cols, currentCharIndex);
            auto foundRolls = n.GetRollCount();

            if (foundRolls < 4)
            {
                drawing[currentCharIndex] = 'x';
                rval++;
            }
            currentCharIndex++;
        }
        this->draw(drawing, cols);
        return rval;
    }

    void draw(const std::vector<char> &line, long length)
    {
        int index = 0;
        for (auto c : line)
        {
            std::print("{}", c);
            index++;
            if (index == length)
            {
                index = 0;
                std::println();
            }
        }
    }

};


#endif //TASK1_HPP
