//
// Created by eh on 05/12/23.
//

#ifndef DAY2_GAMESETS_HPP
#define DAY2_GAMESETS_HPP

#include <vector>


class GameItem {
public:
    enum ColorsEnum {
        blue,
        red,
        green
    };
    int Qty;
    ColorsEnum Color;
    GameItem() {}
    GameItem(int q, ColorsEnum c)
    {
        this->Qty = q;
        this->Color = c;
    }
};

class GameSets
{
public:
    GameItem Green;
    GameItem Blue;
    GameItem Red;
};

class Game
{
public:
    int GameId;
    std::vector<GameSets> GameSet;
};

#endif //DAY2_GAMESETS_HPP
