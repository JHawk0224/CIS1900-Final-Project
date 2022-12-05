// snake game
#include "game.hpp"

#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <deque>
#include "random.hpp"

using namespace std;

game::game(int width, int height) : width{width},
                                   height{height},
                                   snakes{vector<snake>{snake{width / 2, height / 2}}},
                                   apples{vector<pair<int, int>>{}}
{
    vector<pair<int, int>> excludeLocs;
    for (auto &snake : snakes)
    {
        deque<pair<int, int>> body = snake.getBody();
        excludeLocs.insert(excludeLocs.end(), body.begin(), body.end());
    }
    game::generateApples(1, excludeLocs);
}

void game::generateApples(int numApples, vector<pair<int, int>> excludeLocs)
{
    apples = randomAppleLocations(width, height, excludeLocs, numApples);
}

int game::tick()
{
    for (auto &snake : snakes)
    {
        pair<int, int> inFront = snake.inFrontLoc();
        if (inFront.first < 0 || inFront.first >= width ||
            inFront.second < 0 || inFront.second >= height)
        {
            return -1;
        }
        deque<pair<int, int>> body = snake.getBody();
        if (count(body.begin(), body.end(), inFront) > 0)
        {
            return -1;
        }
        if (count(apples.begin(), apples.end(), inFront) > 0)
        {
            snake.move(true);
            apples.erase(find(apples.begin(), apples.end(), inFront));
            if (apples.size() == 0)
            {
                vector<pair<int, int>> excludeLocs;
                for (auto &snake : snakes)
                {
                    deque<pair<int, int>> body = snake.getBody();
                    excludeLocs.insert(excludeLocs.end(), body.begin(), body.end());
                }
                generateApples(1, excludeLocs);
            }
        }
        else
        {
            snake.move(false);
        }
    }
    return 0;
}

void game::turn(int snake_i, int dir)
{
    if (dir >= 0 && dir <= 3)
    {
        snakes[snake_i].setDirection(dir);
    }
}

ostream &operator<<(ostream &os, const game &g)
{
    // top wall
    for (int i{0}; i < g.width + 2; ++i)
    {
        os << setw(3) << "#";
    }
    os << "\n";
    // print row by row
    for (int i{0}; i < g.height; ++i)
    {
        os << setw(3) << "#";
        for (int j{0}; j < g.width; ++j)
        {
            // print the value of the cell
            pair<int, int> loc{j, i};
            if (count(g.apples.begin(), g.apples.end(), loc) > 0)
            {
                os << setw(3) << "*";
            }
            else
            {
                bool inSnake{false};
                for (auto snake : g.snakes)
                {
                    deque<pair<int, int>> body = snake.getBody();
                    if (count(body.begin(), body.end(), loc) > 0)
                    {
                        inSnake = true;
                        break;
                    }
                }
                if (inSnake)
                {
                    os << setw(3) << "O";
                }
                else
                {
                    os << setw(3) << " ";
                }
            }
        }
        os << setw(3) << "#";
        os << "\n";
    }
    // top wall
    for (int i{0}; i < g.width + 2; ++i)
    {
        os << setw(3) << "#";
    }
    return os;
}
