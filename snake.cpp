#include "snake.hpp"

#include <memory>
#include <iostream>
#include <iomanip>
#include <deque>

using namespace std;

snake::snake(int x, int y) : length{1},
                            direction{0},
                            positions{deque<pair<int, int>>{pair<int, int>{x, y}}}
{
}

snake::snake(int x, int y, int dir) : length{1},
                                     direction{dir},
                                     positions{deque<pair<int, int>>{pair<int, int>{x, y}}}
{
}

void snake::move(bool grow)
{
    for (auto pos : positions)
    {
        cout << pos.first << ", " << pos.second << endl;
    }
    positions.push_front(inFrontLoc());
    if (grow)
    {
        ++length;
    }
    else
    {
        positions.pop_back();
    }
    cout << grow << endl;
    for (auto pos : positions)
    {
        cout << pos.first << ", " << pos.second << endl;
    }
}

void snake::setDirection(int dir)
{
    direction = dir;
}

int snake::getLength()
{
    return length;
}

int snake::getDirection()
{
    return direction;
}

pair<int, int> snake::getHead()
{
    return positions.front();
}

pair<int, int> snake::inFrontLoc()
{
    pair<int, int> inFront = positions.front();
    switch (direction)
    {
    case 0:
        ++inFront.second;
        break;
    case 1:
        ++inFront.first;
        break;
    case 2:
        --inFront.second;
        break;
    case 3:
        --inFront.first;
        break;
    }
    return inFront;
}

deque<pair<int, int>> snake::getBody()
{
    return positions;
}

ostream &operator<<(ostream &os, const snake &s)
{
    os << "Length: " << s.length << "\tDirection: " << s.direction << endl;
    os << "Positions: " << endl;
    for (auto &p : s.positions)
    {
        os << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return os;
}
