//
// Created by eh on 05/12/23.
//

#include "task1.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "gamesets.hpp"

void task1::Run()
{
    long sum = 0;
    long notfoundcount = 0;
    std::cout << "Task1" << std::endl;
    std::ifstream file("payload.txt");
    std::string currentline;
    std::vector<std::string> lines;
    while(getline(file, currentline))
    {
        if (!currentline.empty()) {
            lines.emplace_back(currentline);
        }
    }
    std::regex digits("(\\d+)");

    auto iter_end = std::sregex_iterator ();
    std::vector<int> digits_list;
    for (int x = 0; x < lines.size(); x++)
    {
        auto &l = lines[x];
        auto digits_begin = std::sregex_iterator(l.begin(), l.end(), digits);
        for (auto n = digits_begin; n != iter_end; ++n)
        {
            std::string chksum;
            std::smatch m = *n;
            auto digit = m.str(1);
            std::cout << digit << std::endl;

            auto startpos = m.position();
            auto length = digit.size();

            bool isatbegining = startpos == 0;
            bool isatend = startpos + length > l.length();

            bool isattop = x-1 < 0;
            bool isatbottom = x + 1 == lines.size();

            auto spos = isatbegining ? 0 : startpos - 1;
            auto len = isatend || isatbegining ? length + 1 : length + 2;

            /*
            if (lines[x].substr(spos,len) == "01.")
            {
                std::cout << "SPOS: " << spos << " Len: " << len << std::endl;
                std::cout << lines[x].substr(spos) << std::endl;
                std::cout << lines[x] << std::endl;
                return;
            }
            */

            if (isattop)
            {
                chksum.append(lines[x].substr(spos,len));
                chksum.append( lines[x+1].substr(spos,len));

                std::cout << lines[x].substr(spos,len)      << std::endl;
                std::cout << lines[x+1].substr(spos,len)    << std::endl;
            }
            else if (isatbottom)
            {
                chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));

                std::cout << lines[x-1].substr(spos,len)    << std::endl;
                std::cout << lines[x].substr(spos,len)      << std::endl;
            }
            else
            {
                chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));
                chksum.append(lines[x+1].substr(spos,len));
                std::cout << lines[x-1].substr(spos,len)    << std::endl;
                std::cout << lines[x].substr(spos,len)      << std::endl;
                std::cout << lines[x+1].substr(spos,len)    << std::endl;
            }
            //std::cout << std::endl;

            if ( std::regex_search(chksum, std::regex(R"([\*\$\+\-\/=%&@#])")) )
            {
                    int d = std::stoi(digit);
                    digits_list.emplace_back(d);
                    /*
                    std::cout << " " << "FOUND ("
                        << chksum << ") Cleaned: "
                        << d << " | sum = "
                        << sum << " + "
                        << d
                        << " ( = " << sum+d << ")"
                        <<  std::endl;
                    */
                    sum = sum + d;
            }
            else
            {
                std::cout << " " << "NOT FOUND (" << chksum << ")" <<std::endl;
                notfoundcount++;
            }

        }

    }

    std::cout << "Not found: " << notfoundcount << std::endl;
    std::cout << "Task1 SUM: " << sum <<std::endl;
}
