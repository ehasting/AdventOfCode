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

class task2
{
public:
    std::string TaskName = "Task2";
    void Run();
    std::mutex mtx; // Mutex to protect myVector
    void addToVector(std::vector<long> &list, std::vector<long> vals) {
        std::lock_guard<std::mutex> lock(mtx);
        list.insert(list.end(), vals.begin(), vals.end());
    }
    std::vector<long> processRange(const long startId, const long stopId)
    {
        std::println("START: Processing {0} to {1}", startId, stopId);
        std::vector<long> rval;
        std::vector<long> currentrange;
        for (long i = startId; i <= stopId; i++)
        {
            currentrange.push_back(i);
        }

        std::for_each(std::execution::par_unseq, currentrange.begin(), currentrange.end(), [&](long& value) {
            auto ids = this->hasInvalidIds(value);
            if (!ids.empty())
            {
                this->addToVector(rval, ids);
                //rval.insert(rval.end(), ids.begin(), ids.end());
            }
        });
        /*
        for (long i = startId; i <= stopId; i++)
        {
            //std::cout << i << std::endl;
            auto ids = this->hasInvalidIds(i);
            if (!ids.empty())
            {
                rval.insert(rval.end(), ids.begin(), ids.end());
            }

        }
        */
        std::println("STOP: Processing {0} to {1}", startId, stopId);
        return rval;
    }

    std::vector<long> hasInvalidIds(const long value)
    {
        std::vector<long> rval;
        const std::string str_number = std::to_string(value);
        int digits = str_number.size()-1;
        bool is_added = false;
        while (digits != 0)
        {
            double digitsgroup = (double)str_number.size() / (double)digits;
            //std::println("a: {0} == b: {1}", digitsgroup,  std::floor(digitsgroup));
            if (digitsgroup == std::floor(digitsgroup))
            {
                std::vector<std::string> group;
                // we have grouping - lets iterate
                for (int i = 0; i<digitsgroup; ++i)
                {
                    std::string sub = str_number.substr(i*digits, digits);
                    //std::println("group: {0} (start index: {1}, length: {2})", sub, i*digits, digits);
                    group.push_back(sub);
                }
                auto target_value = *group.begin();
                if (std::all_of(group.cbegin(), group.cend(), [&](std::string x) { return x == target_value; }))
                {
                    //std::println("found {0} of value: {1} (adding: {2})", group.size(), target_value, value);
                    if (!is_added)
                    {
                        is_added = true;
                        rval.push_back(value);
                    }
                }

            }

            digits--;

        }
        return rval;
    }
};


#endif //DAY1_TASK2_HPP
