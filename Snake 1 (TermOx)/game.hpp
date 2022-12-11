#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "snake.hpp"

class game
{
private:
    int width;
    int height;
    std::vector<snake> snakes;
    std::vector<std::pair<int, int>> apples;
public:
    game(int, int);
    void generateApples(int numApples, std::vector<std::pair<int, int>> excludeLocs);
    int tick();
    void turn(int, int);
    friend std::ostream &operator<<(std::ostream &os, const game &g);
};

#endif
