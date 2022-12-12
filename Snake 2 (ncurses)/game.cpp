#include "game.hpp"

#include <iomanip>
#include <algorithm>
#include <vector>
#include <deque>
#include "random.hpp"
#include "apple.hpp"
#include "dir.hpp"

using namespace std;

game::game(int width, int height) : width{width},
                                    height{height},
                                    snakes{vector<snake>{snake{width / 2, height / 2}}},
                                    apples{vector<apple>{}},
                                    b{board{width, height}},
                                    score{0},
                                    playing{true}
{
    srand(board::milliseconds());
    vector<pair<int, int>> excludeLocs;
    for (auto &snake : snakes)
    {
        deque<pair<int, int>> body = snake.getBody();
        excludeLocs.insert(excludeLocs.end(), body.begin(), body.end());
    }
    game::generateApples(1, excludeLocs, -1);
    b.initialize();
}

game::game(int width, int height, int timeout) : width{width},
                                                 height{height},
                                                 snakes{vector<snake>{snake{width / 2, height / 2}}},
                                                 apples{vector<apple>{}},
                                                 b{board{width, height, timeout}},
                                                 score{0},
                                                 playing{true}
{
    srand(board::milliseconds());
    vector<pair<int, int>> excludeLocs;
    for (auto &snake : snakes)
    {
        deque<pair<int, int>> body = snake.getBody();
        excludeLocs.insert(excludeLocs.end(), body.begin(), body.end());
    }
    game::generateApples(1, excludeLocs, -1);
    b.initialize();
}

void game::generateApples(int numApples, vector<pair<int, int>> excludeLocs, int type = -1)
{
    vector<pair<int, int>> appleLocs = randomAppleLocations(width, height, excludeLocs, numApples);
    for (auto &loc : appleLocs)
    {
        int random = (int)(rand() * 100);
        if (type == -1)
        {
            if (random < 15)
            {
                apples.push_back(apple{loc.first, loc.second, JUICY});
            }
            else
            {
                apples.push_back(apple{loc.first, loc.second, NORMAL});
            }
        }
        else
        {
            apples.push_back(apple{loc.first, loc.second, type});
        }
    }
}

int game::tick()
{
    for (auto &snake : snakes)
    {
        pair<int, int> inFront = snake.inFrontLoc();
        if (inFront.first < 0 || inFront.first >= width ||
            inFront.second < 0 || inFront.second >= height)
        {
            playing = false;
            return -1;
        }
        deque<pair<int, int>> body = snake.getBody();
        if (count(body.begin(), body.end(), inFront) > 0 && inFront != *body.end())
        {
            playing = false;
            return -1;
        }
        bool hitApple = false;
        bool isJuicy = false;
        for (auto it = apples.begin(); it != apples.end(); ++it)
        {
            if (it->getLoc() == inFront)
            {
                hitApple = true;
                isJuicy = it->getType() == JUICY;
                apples.erase(it);
                break;
            }
        }
        if (hitApple)
        {
            snake.move(true);
            if (apples.size() == 0 || isJuicy)
            {
                vector<pair<int, int>> excludeLocs;
                for (auto &snake : snakes)
                {
                    deque<pair<int, int>> body = snake.getBody();
                    excludeLocs.insert(excludeLocs.end(), body.begin(), body.end());
                }
                for (auto &apple : apples)
                {
                    excludeLocs.push_back(apple.getLoc());
                }
                generateApples(isJuicy ? 5 : 1, excludeLocs, isJuicy ? NORMAL : -1);
            }
            ++score;
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

bool game::isPlaying()
{
    return playing;
}

int game::getScore()
{
    return score;
}

void game::processInput()
{
    chtype input = b.getInput();
    int timeout = b.getTimeout();
    if (input == KEY_UP)
    {
        turn(0, UP);
    }
    else if (input == KEY_RIGHT)
    {
        turn(0, RIGHT);
    }
    else if (input == KEY_DOWN)
    {
        turn(0, DOWN);
    }
    else if (input == KEY_LEFT)
    {
        turn(0, LEFT);
    }
    else if (input == 'p')
    {
        b.setTimeout(-1);
        while (b.getInput() != 'p') {}
        b.setTimeout(timeout);
    }
    else if (input == 'q')
    {
        playing = false;
    }
}

void game::draw()
{
    b.clear();
    for (auto &snake : snakes)
    {
        deque<pair<int, int>> body = snake.getBody();
        b.addList(body, 'O', COLOR_PAIR(2));
    }
    for (auto &apple : apples)
    {
        b.addAt(apple.getLoc(), '*', apple.getType() == JUICY ? COLOR_PAIR(4) : COLOR_PAIR(1));
    }
    b.drawStatus(score, COLOR_PAIR(3));
    b.refresh();
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
            bool isApple = false;
            for (auto apple : g.apples)
            {
                if (apple.getLoc() == loc)
                {
                    isApple = true;
                    break;
                }
            }
            if (isApple)
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
