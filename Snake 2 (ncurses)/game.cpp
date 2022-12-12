#include "game.hpp"

#include <iomanip>
#include <algorithm>
#include <vector>
#include <deque>
#include <thread>
#include <chrono>
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
                                    powerupLock{false},
                                    paused{false},
                                    playing{true}
{
    vector<pair<int, int>> excludeLocs;
    for (auto &snake : snakes)
    {
        snake.setAttrs(COLOR_PAIR(2));
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
                                                 powerupLock{false},
                                                 paused{false},
                                                 playing{true}
{
    vector<pair<int, int>> excludeLocs;
    for (auto &snake : snakes)
    {
        snake.setAttrs(COLOR_PAIR(2));
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
        
        if (type != -1)
        {
            apples.push_back(apple{loc.first, loc.second, type});
        }
        else
        {
            int random = b.randomInt(0, 100);
            if (random < 60)
            {
                apples.push_back(apple{loc.first, loc.second, NORMAL});
            }
            else
            {
                random = b.randomInt(1, 5);
                apples.push_back(apple{loc.first, loc.second, random});
            }
        }
    }
}

void game::mulSpeed(float factor)
{
    powerupLock = true;
    int startTimeout = b.getTimeout();
    b.setTimeout((int)(startTimeout / factor));
    this_thread::sleep_for(chrono::milliseconds(5000));
    b.setTimeout(startTimeout);
    powerupLock = false;
}

void game::makeSnakeInvincible(int snake)
{
    powerupLock = true;
    init_color(COLOR_RED, 1000, 392, 0);
    snakes[snake].setInvincible(true);;
    this_thread::sleep_for(chrono::milliseconds(5000));
    snakes[snake].setInvincible(false);
    init_color(COLOR_RED, 1000, 0, 0);
    powerupLock = false;
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
        if (!snake.isInvincible())
        {
            deque<pair<int, int>> body = snake.getBody();
            if (count(body.begin(), body.end(), inFront) > 0 && inFront != *body.end())
            {
                playing = false;
                return -1;
            }
        }
        int type = -1;
        for (auto it = apples.begin(); it != apples.end(); ++it)
        {
            if (it->getLoc() == inFront)
            {
                type = it->getType();
                apples.erase(it);
                break;
            }
        }
        if (type != -1)
        {
            snake.move(true);
            if (apples.size() == 0 || type == JUICY)
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
                if (powerupLock)
                {
                    generateApples(1, excludeLocs, NORMAL);
                }
                else
                {
                    generateApples(type == JUICY ? 5 : 1, excludeLocs, type != NORMAL ? NORMAL : -1);
                }
            }
            ++score;
            if (type == INVINCY)
            {
                thread powerup(&game::makeSnakeInvincible, this, 0);
                powerup.detach();
            }
            else if (type == SPEEDY)
            {
                thread powerup(&game::mulSpeed, this, 2);
                powerup.detach();
            }
            else if (type == SLOWY)
            {
                thread powerup(&game::mulSpeed, this, 0.5);
                powerup.detach();
            }
        }
        else
        {
            snake.move(false);
        }
    }
    return 0;
}

bool game::isPaused()
{
    return paused;
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
        paused = !paused;
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
        b.addList(body, 'O', snake.getAttrs());
    }
    for (auto &apple : apples)
    {
        b.addAt(apple.getLoc(), '*', apple.getAttrs());
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
