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
    // regex 1:
    // regex 2: ((\d+ (blue|red|green))(,|;|))
    std::vector<std::string> lines;
    while(getline(file, currentline))
    {
        if (!currentline.empty()) {
            lines.emplace_back(currentline);
        }
    }
    std::regex digits("(.{0,1}\\d+.{0,1})");

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
            //std::cout << digit << std::endl;


            auto spos = l.find(digit);
            auto len = digit.size();




            if (x-1 < 0)
            {
                //chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));
                chksum.append( lines[x+1].substr(spos,len));
                // -- std::cout << lines[x-1].substr(spos,len)    << std::endl;
                //std::cout << lines[x].substr(spos,len)      << std::endl;
                //std::cout << lines[x+1].substr(spos,len)    << std::endl;
            }
            else if (x + 1 == lines.size())
            {
                chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));
                //chksum.append( lines[x+1].substr(spos,len));

                //std::cout << lines[x-1].substr(spos,len)    << std::endl;
                //std::cout << lines[x].substr(spos,len)      << std::endl;
                // -- std::cout << lines[x+1].substr(spos,len)    << std::endl << std::endl;
            }
            else
            {
                chksum.append(lines[x-1].substr(spos,len));
                chksum.append(lines[x].substr(spos,len));
                chksum.append(lines[x+1].substr(spos,len));
            }
            // std::cout << chksum << std::endl;

            if ( std::regex_search(chksum, std::regex(R"([\*\$\+\-\/=%&@#])")) )
            {
                auto xx1_regex =  std::regex(R"(\d+)");
                auto xx1_begin = std::sregex_iterator(digit.begin(), digit.end(),xx1_regex);
                for (auto xxloop = xx1_begin; xxloop != iter_end; ++xxloop)
                {
                    
                    std::smatch xxm = *xxloop;
                    int d = std::stoi(xxm.str());

                    digits_list.emplace_back(d);
                    sum = sum + d;
                    //std::cout << digit  << " " << "FOUND (" << chksum << ") Cleaned: " << d <<std::endl;
                }
            }
            else
            {
                //std::cout <<  digit  << " " << "NOT FOUND (" << chksum << ")" <<std::endl;
                notfoundcount++;
            }

        }

    }


    std::cout << "Not found: " << notfoundcount << std::endl;
    std::cout << "Task1 SUM: " << sum <<std::endl;
}
