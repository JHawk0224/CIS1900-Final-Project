#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include "snake.hpp"
#include "board.hpp"
#include "apple.hpp"

class game
{
private:
    int width;
    int height;
    std::vector<snake> snakes;
    std::vector<apple> apples;
    board b;
    int score;
    bool playing;
public:
    game(int, int);
    game(int, int, int);
    void generateApples(int numApples, std::vector<std::pair<int, int>> excludeLocs, int type);
    int tick();
    void turn(int, int);
    bool isPlaying();
    int getScore();
    void processInput();
    void draw();
    friend std::ostream &operator<<(std::ostream &os, const game &g);
};

#endif
