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
#include <atomic>
#include <map>

class Coord
{
public:
    const long X;
    const long Y;
    Coord(const long x, const long y) : X(x), Y(y)
    { }
    [[nodiscard]] bool IsEqual(const Coord &cord) const
    {
        if (this->X == cord.X && this->Y == cord.Y)
            return true;
        return false;
    }
    std::string ToString() const
    {
        return std::format("{},{}", this->X, this->Y);
    }
};

class Leaf
{
    public:
    static std::atomic<int> s_nextId;

    static int getNextId() {
        std::println("increasing: {}", s_nextId.load());
        return ++s_nextId; // Increment and return the next ID
    }
    int Id;
    Coord Coordinates;
    std::shared_ptr<Leaf> Left = nullptr;
    std::shared_ptr<Leaf> Right = nullptr;
    std::shared_ptr<Leaf> Parent = nullptr;
    Leaf(const Coord &cord) : Id(Leaf::getNextId()), Coordinates(cord.X, cord.Y)
    {

    }
    Leaf(const Coord &cord, const std::shared_ptr<Leaf> &parent) : Leaf(cord)
    {
        this->Parent = parent;
    }

    ~Leaf()
    {
        std::println("~Leaf: {}", this->Id);
    }
    std::shared_ptr<Leaf> &CreateAndReturnLeftLeaf(const Coord &cord, const std::shared_ptr<Leaf>& parent)
    {
        this->Left = std::make_shared<Leaf>(cord, parent);
        return this->Left;
    }
    std::shared_ptr<Leaf> &CreateAndReturnRightLeaf(const Coord &cord, const std::shared_ptr<Leaf>& parent)
    {
        this->Right = std::make_shared<Leaf>(cord, parent);
        return this->Right;
    }
};





class Data
{
    public:
    // if (std::equal(vector1.begin(), vector1.end(), vector2.begin()))
    std::vector<std::vector<int>> PathTraces;
    std::shared_ptr<Leaf> BinaryTree;
    std::map<std::string, std::shared_ptr<Leaf>> LeafMap;
    const char StartChar = 'S';
    const char EmptyChar = '.';
    const char SplitterChar = '^';
    const char BeamChar = '|';
    std::shared_ptr<Coord> Start;
    std::vector<std::vector<char>> Table;
    long Cols = 0;
    long Rows = 0;
    long GlobalTraceCounter = 0;
    Data()
    {

    }
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


    void MapBtree(const std::shared_ptr<Leaf> &node)
    {
        if (node->Left != nullptr)
        {
            MapBtree(node->Left);
            std::print(" [{}]{}",node->Id, node->Left->Id);
        }
        else
        {
            std::println("");
        }
        if (node->Right != nullptr)
        {
            MapBtree(node->Right);
            std::print(" [{}]{}",node->Id, node->Right->Id);
        }
        else
        {
            std::println("");
        }
    }

    void SearchForExistingNode(const Coord &searchcoord, std::shared_ptr<Leaf> &out)
    {
        if (LeafMap.contains(searchcoord.ToString()))
        {
            out = LeafMap[searchcoord.ToString()];
        }
    }

    void RecurseBTree(const Coord &searchcoord, std::shared_ptr<Leaf> &node, std::shared_ptr<Leaf> &out)
    {
        //std::println("Checking: {} == {}", searchcoord.ToString(), node->Coordinates.ToString());
        if (searchcoord.IsEqual(node->Coordinates))
        {
            //std::println("FOUND: {}", searchcoord.ToString());
            out = node;
        }
        else
        {
            if (node->Left != nullptr)
            {
                RecurseBTree(searchcoord, node->Left, out);
            }
            if (node->Right != nullptr)
            {
                RecurseBTree(searchcoord, node->Right, out);
            }
            //std::println("Did not find {}", searchcoord.ToString());
        }
    }

    void CheckBranch(const Coord &coord, std::shared_ptr<Leaf> &parent)
    {
        Coord newCoord(coord.X, coord.Y + 1); // jump down one.
        if (newCoord.Y == Rows)
        {
            std::println("{} reached bottom on {} (tested: {})",parent->Id, parent->Coordinates.ToString(), newCoord.ToString());
            return ;
        }
        if (GetCharAtCoord(newCoord) == SplitterChar)
        {
            {
                Coord branchl(newCoord.X - 1, newCoord.Y);
                std::shared_ptr<Leaf> left = nullptr;
                SearchForExistingNode(branchl,left);
                if (left == nullptr)
                {
                    left = parent->CreateAndReturnLeftLeaf(branchl, parent);
                    LeafMap[branchl.ToString()] = left;
                }
                else
                {
                    parent->Left = left;
                }
                CheckBranch(branchl, parent->Left);
            }
            {
                Coord branchr(newCoord.X + 1, newCoord.Y);
                std::shared_ptr<Leaf> right = nullptr;
                SearchForExistingNode(branchr, right);
                if (right == nullptr)
                {
                    right = parent->CreateAndReturnRightLeaf(branchr, parent);
                    LeafMap[branchr.ToString()] = right;
                }
                else
                {
                    parent->Right = right;
                }
                CheckBranch(branchr, parent->Right);
            }
        }
        else if (GetCharAtCoord(newCoord) == EmptyChar)
        {
            CheckBranch(newCoord, parent);
        }

    }

    void Compute()
    {
        Cols = this->Table.at(0).size();
        Rows = this->Table.size();

        for (long j = 0; j < Cols; j++)
        {
            if (this->Table.at(0).at(j) == StartChar)
            {
                this->Start = std::make_shared<Coord>(j, 0);
                break;
            }
        }

        this->BinaryTree = std::make_shared<Leaf>(*Start);
        LeafMap[Start->ToString()] = this->BinaryTree;
        CheckBranch(*Start, this->BinaryTree);
    }

};
#endif //DAY5_DATACLASS_HPP