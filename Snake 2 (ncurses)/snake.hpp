#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <deque>
#include <ncurses.h>

class snake
{
private:
    int length;
    int direction;
    bool invincible;
    attr_t attrs;
    std::deque<std::pair<int, int>> positions;
public:
    snake(int, int);
    snake(int, int, int);
    void move(bool);
    void setDirection(int);
    int getLength();
    int getDirection();
    bool isInvincible();
    void setInvincible(bool);
    attr_t getAttrs();
    void setAttrs(attr_t);
    std::pair<int, int> getHead();
    std::pair<int, int> inFrontLoc();
    std::deque<std::pair<int, int>> getBody();
    friend std::ostream &operator<<(std::ostream &os, const snake &s);
};

#endif
