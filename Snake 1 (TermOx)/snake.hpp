#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <memory>
#include <deque>

class snake
{
private:
    int length;
    int direction;
    std::deque<std::pair<int, int>> positions;
public:
    snake(int, int);
    snake(int, int, int);
    void move(bool);
    void setDirection(int);
    int getLength();
    int getDirection();
    std::pair<int, int> getHead();
    std::pair<int, int> inFrontLoc();
    std::deque<std::pair<int, int>> getBody();
    friend std::ostream &operator<<(std::ostream &os, const snake &s);
};

#endif
