//
// Created by eh on 05/12/23.
//

#ifndef DAY1_TASK2_HPP
#define DAY1_TASK2_HPP
#include <string>
#include <vector>

class task2 {
public:
    void Tests();
    void Run();
    std::vector<int> FindFullNumber(std::string cutted, std::string &s, int startposition);
    struct search
    {
        int pos;
        bool atstart = false;
        bool atend = false;
    };
};


#endif //DAY1_TASK2_HPP
