#ifndef APPLE_HPP
#define APPLE_HPP

#include <iostream>

enum AppleType 
{
    NORMAL = 0,
    JUICY = 1
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
    friend std::ostream &operator<<(std::ostream &os, const apple &a);
};

#endif
