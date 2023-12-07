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
    for (int x = 0; x < lines.size();)
    {
        auto &l = lines[x];
        for (int innerx = 0; innerx < l.size(); innerx++ )
        {
            std::string digit = std::string(1, l[innerx] );
            if (l[innerx] != '*')
            {
                std::cout << innerx  << " of "  << l.size() << " " << digit << std::endl;
                continue;
            }
            std::string chksum;

            std::cout << digit << std::endl;

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
                chksum.append( lines[x+1].substr(spos,len));
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
            //std::cout << std::endl;

            if ( std::regex_search(chksum, std::regex(R"(\d)")) )
            {
                int d = std::stoi(digit);
                digits_list.emplace_back(d);
                if (isattop)
                {
                    std::cout << lines[x].substr(spos,len)      << std::endl;
                    std::cout << lines[x+1].substr(spos,len)    << std::endl;
                }
                else if (isatbottom)
                {
                    std::cout << lines[x-1].substr(spos,len)    << std::endl;
                    std::cout << lines[x].substr(spos,len)      << std::endl;
                }
                else
                {
                    std::cout << lines[x-1].substr(spos,len)    << std::endl;
                    std::cout << lines[x].substr(spos,len)      << std::endl;
                    std::cout << lines[x+1].substr(spos,len)    << std::endl;
                }
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
