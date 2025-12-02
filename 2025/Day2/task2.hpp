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
    void addToVector(std::vector<long> &list, long vals) {
        std::lock_guard<std::mutex> lock(mtx);
        list.push_back(vals);
    }
    std::vector<long> processRange(const long startId, const long stopId)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::println("START: Processing {0} to {1}", startId, stopId);
        std::vector<long> rval;
        std::vector<long> currentrange = std::views::iota(startId, stopId) | std::ranges::to<std::vector>();

        std::for_each(std::execution::par_unseq, currentrange.begin(), currentrange.end(), [&](long& value) {
            if (this->hasInvalidIds(value))
                this->addToVector(rval, value);
        });
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        TotalTimeMs += duration_ms.count();
        std::println("STOP: Processing {0} to {1} (took {2}ms on {3} iterations)", startId, stopId, duration_ms.count(), currentrange.size());
        return rval;
    }

    bool hasInvalidIds(const long value)
    {
        //std::vector<long> rval;
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
                if (std::ranges::all_of(std::as_const(group), [&](const std::string &x) { return x == target_value; }))
                {
                    //std::println("found {0} of value: {1} (adding: {2})", group.size(), target_value, value);
                    if (!is_added)
                    {
                        return true;
                        //return rval;
                    }
                }

            }

            digits--;

        }
        return false;
    }
};


#endif //DAY1_TASK2_HPP
