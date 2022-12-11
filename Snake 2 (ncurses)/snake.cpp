#include "snake.hpp"

#include "dir.hpp"

using namespace std;

snake::snake(int x, int y) : length{1},
                             direction{RIGHT},
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
    positions.push_front(inFrontLoc());
    if (grow)
    {
        ++length;
    }
    else
    {
        positions.pop_back();
    }
}

void snake::setDirection(int dir)
{
    if (length <= 1 || abs(dir - direction) != 2)
    {
        direction = dir;
    }
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
    case UP:
        --inFront.first;
        break;
    case RIGHT:
        ++inFront.second;
        break;
    case DOWN:
        ++inFront.first;
        break;
    case LEFT:
        --inFront.second;
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
    os << "Length: " << s.length << "\tDirection: ";
    if (s.direction == UP)
    {
        os << "Up";
    }
    else if (s.direction == RIGHT)
    {
        os << "Right";
    }
    else if (s.direction == DOWN)
    {
        os << "Down";
    }
    else if (s.direction == LEFT)
    {
        os << "Left";
    }
    os << endl << "Positions: " << endl;
    for (auto &p : s.positions)
    {
        os << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return os;
}
