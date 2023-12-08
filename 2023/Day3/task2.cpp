//
// Created by eh on 05/12/23.
//

#include "task2.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "gamesets.hpp"


    /*
426.....
...*251.
68......
*/


void task2::Run()
{
    long sum = 0;
    long notfoundcount = 0;
    std::cout << "Task2" << std::endl;
    std::ifstream file("payload.txt");
    std::string currentline;
    std::vector<std::string> lines;
    while(getline(file, currentline))
    {
        if (!currentline.empty()) {
            lines.emplace_back(currentline);
        }
    }

    std::cout << "Done loading file" << std::endl;

    auto iter_end = std::sregex_iterator ();
    std::vector<int> digits_list;
    for (int x = 0; x < lines.size();x++)
    {
        auto &l = lines[x];
        for (int innerx = 0; innerx < l.size(); ++innerx )
        {
            std::string digit = std::string(1, l[innerx] );
            if (l[innerx] != '*')
            {

                continue;
            }
            std::string chksum;
            auto startpos = innerx;
            auto length = digit.size();

            bool isatbegining = startpos == 0;
            bool isatend = startpos + length > l.length();

            bool isattop = x-1 < 0;
            bool isatbottom = x + 1 == lines.size();

            auto spos = isatbegining ? 0 : startpos - 1;
            auto len = isatend || isatbegining ? length + 1 : length + 2;


            if (isattop)
            {
                chksum.append(lines[x].substr(spos,len));
                chksum.append(lines[x+1].substr(spos,len));
            }
            else if (isatbottom)
            {
                chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));
            }
            else
            {
                chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));
                chksum.append(lines[x+1].substr(spos,len));
            }
            int matchcount = 0;
            bool found = false;
            std::smatch digit_match;
            std::string current_checksum = chksum;
            while ( std::regex_search(current_checksum, digit_match, std::regex(R"(\d+)")) )
            {
                found = true;
                current_checksum = digit_match.suffix().str();
            }
            if (found)
            {
                std::vector<int> rval;
                if (isattop)
                {
                    {
                        auto t = this->FindFullNumber(lines[x].substr(spos, len), lines[x], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                    {
                        auto t = this->FindFullNumber(lines[x + 1].substr(spos, len), lines[x + 1], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                }
                else if (isatbottom)
                {
                    {
                        auto t = this->FindFullNumber(lines[x - 1].substr(spos, len), lines[x - 1], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                    {
                        auto t = this->FindFullNumber(lines[x].substr(spos, len), lines[x], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                }
                else
                {
                    {
                        auto t = this->FindFullNumber(lines[x - 1].substr(spos, len), lines[x - 1], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                    {
                        auto t = this->FindFullNumber(lines[x].substr(spos, len), lines[x], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                    {
                        auto t = this->FindFullNumber(lines[x + 1].substr(spos, len), lines[x + 1], spos);
                        rval.insert(rval.end(), t.begin(), t.end());
                    }
                }
                int factor = 1;
                std::cout << std::endl;
                if (rval.size() == 2)
                {


                for(auto a:rval)
                {
                    std::cout << factor << " * " << a << std::endl;
                    factor = factor * a;
                }
                sum = sum + factor;
                }
                std::cout << std::endl;
            }
        }

    }

    std::cout << "Not found: " << notfoundcount << std::endl;
    std::cout << "Task1 SUM: " << sum <<std::endl;
}
std::vector<int> task2::FindFullNumber(std::string cutted, std::string &s, int sp)
{
    std::vector<int> rval;
    std::string search = cutted;
    std::smatch founddigits;
    std::vector<task2::search> positions;
    auto digitsregex = std::regex("\\d+");
    auto digits_begin = std::sregex_iterator(cutted.begin(), cutted.end(), digitsregex);
    auto iter_end = std::sregex_iterator();
    for (auto n = digits_begin; n != iter_end; ++n)
    {
        std::smatch match = *n;
        task2::search rval;
        rval.pos = sp + match.position();
        if (match.position() == 0)
        {
            rval.atstart = true;
        }
        if (match.position() + match.str().length() == cutted.length())
        {
            rval.atend = true;
        }
        positions.push_back(rval);

    }

    if (positions.size() == 0)
    {
        return rval;
    }

    for(auto pos: positions)
    {
        int startposition = pos.pos;

        bool reverse_search = pos.atstart;

        if (reverse_search)
        {
            for (int x = startposition;;)
            {
                if (std::isdigit(s[x]))
                {
                    if (x == 0)
                    {
                        startposition = 0;
                        break;
                    }
                    x--;
                    continue;
                }
                startposition = x;
                break;
            }
        }

        std::string outstring;

        bool innumber = false;
        for (int x = startposition;;)
        {
            if (std::isdigit(s[x]))
            {
                innumber = true;
                outstring.append(std::string(1, s[x]));

            }
            if (!std::isdigit(s[x]) && innumber)
            {
                break;
            }
            x++;
        }
        rval.push_back(std::stoi(outstring));
    }
    for(auto n:rval)
    {
        std::cout << "RVAL: " << n << std::endl;
    }
    return rval;

}