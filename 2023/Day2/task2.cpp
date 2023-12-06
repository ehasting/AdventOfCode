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

void task2::Tests()
{
    std::string str = "2eightwo8fmktlf";
    std::regex re1("(?=(\\d|one|two|three|four|five|six|seven|eight|nine))."); // ECMA
    auto digits_begin = std::sregex_iterator(str.begin(), str.end(), re1);
    auto digits_end = std::sregex_iterator ();
    for (auto n =  digits_begin; n != digits_end; n++) {
        std::smatch match = *n;
        std::cout << match.str(1) << std::endl;
    }
}

void task2::Run()
{
    std::cout << "Task1" << std::endl;
    std::ifstream file("payload.txt");
    std::string currentline;
    // regex 1:
    // regex 2: ((\d+ (blue|red|green))(,|;|))
    std::regex game_number_regex("Game (\\d+)\\: (.*)");
    std::regex gameset_regex("((\\d+ (blue|red|green))(,|;|))");
    std::vector<Game> games;
    std::string setstring;
    while(getline(file, currentline))
    {
        std::string line = currentline + ";";
        Game current_game;
        std::vector<std::string> digit;
        //std::cout << line << std::endl;
        auto digits_begin = std::sregex_iterator(line.begin(), line.end(), game_number_regex);
        auto iter_end = std::sregex_iterator ();
        for (auto n =  digits_begin; n != iter_end; ++n)
        {
            std::smatch m = *n;
            current_game.GameId = std::stoi(m.str(1));
            setstring = m.str(2);
        }

        GameSets gset;
        auto sets_begin = std::sregex_iterator(setstring.begin(), setstring.end(), gameset_regex);
        for (auto n =  sets_begin; n != iter_end; ++n)
        {
            std::smatch m = *n;
            std::cout << n->str() << std::endl;
            int q = std::stoi(n->str().substr(0, n->str().find(" ")));
            std::string c = n->str().substr(n->str().find(" "));

            bool is_end = std::find(c.begin(), c.end(), ';') != c.end();
            c.erase(std::remove(c.begin(), c.end(), ';'), c.end());
            c.erase(std::remove(c.begin(), c.end(), ','), c.end());
            c.erase(std::remove(c.begin(), c.end(), ' '), c.end());
            GameItem::ColorsEnum col;
            if (c == "green")
            {
                col = GameItem::ColorsEnum::green;
                gset.Green = GameItem(q, col);
            }
            else if (c == "red")
            {
                col = GameItem::ColorsEnum::red;
                gset.Red = GameItem(q, col);
            }
            else if (c == "blue")
            {
                col = GameItem::ColorsEnum::blue;
                gset.Blue = GameItem(q, col);
            }
            std::cout << q << " :: " << c << std::endl;
            if (is_end)
            {
                current_game.GameSet.push_back(gset);
                gset = GameSets();
            }

        }
        games.push_back(current_game);

        //std::cout << gamenr << setstring << std::endl;

    }
    int blue = 14;
    int green = 13;
    int red =  12;
    int sum = 0;
    for ( auto n : games)
    {
        bool failedgame = false;
        int max_blue = 0;
        int max_green = 0;
        int max_red = 0;

        for (auto nn: n.GameSet)
        {
            if (nn.Blue.Qty > max_blue)
                max_blue = nn.Blue.Qty;
            if (nn.Red.Qty > max_red)
                max_red = nn.Red.Qty;
            if (nn.Green.Qty > max_green)
                max_green = nn.Green.Qty;

        }

        int game_power = max_blue * max_red * max_green;
        if (game_power == 0)
        {
            std::cout << " power by 0 +???" <<std::endl << std::endl;
        }
        sum = sum + game_power;
        std::cout << " G: " << n.GameId << " " << n.GameSet.size() << " | " << game_power << std::endl;
    }
    std::cout << "Task1 SUM: " << sum <<std::endl;
}