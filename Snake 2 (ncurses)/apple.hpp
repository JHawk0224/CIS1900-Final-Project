#ifndef APPLE_HPP
#define APPLE_HPP

#include <iostream>
#include <ncurses.h>

enum AppleType 
{
    NORMAL = 0,
    JUICY = 1,
    INVINCY = 2,
    SLOWY = 3,
    SPEEDY = 4
};

class apple
{
private:
    int type;
    std::pair<int, int> position;
public:
    apple(int, int);
    apple(int, int, int);
    std::pair<int, int> getLoc();
    int getType();
    attr_t getAttrs();
    friend std::ostream &operator<<(std::ostream &os, const apple &a);
};

#endif
