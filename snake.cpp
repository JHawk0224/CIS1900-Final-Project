#include "snake.hpp"

#include <memory>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

snake::snake(int x, int y) : length{1},
                            direction{0},
                            positions{vector<pair<int, int>>{pair<int, int>{x, y}}}
{
}

snake::snake(int x, int y, int dir) : length{1},
                                     direction{dir},
                                     positions{vector<pair<int, int>>{pair<int, int>{x, y}}}
{
}

void snake::move(bool grow)
{
    if (grow)
    {
        ++length;
        positions.push_back(positions[length - 2]);
    }
    else
    {
        for (int i{length - 1}; i > 0; --i)
        {
            positions[i] = positions[i - 1];
        }
    }

    positions[0] = inFrontLoc();
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

std::pair<int, int> snake::getHead()
{
    return positions[0];
}

std::pair<int, int> snake::inFrontLoc()
{
    pair<int, int> inFront = positions[0];
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

std::vector<std::pair<int, int>> snake::getBody()
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
