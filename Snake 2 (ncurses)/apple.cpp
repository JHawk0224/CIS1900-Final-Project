#include "apple.hpp"

using namespace std;

apple::apple(int x, int y) : type{NORMAL},
                             position{pair<int, int>{x, y}}
{
}

apple::apple(int x, int y, int type) : type{type},
                                       position{pair<int, int>{x, y}}
{
}

pair<int, int> apple::getLoc()
{
    return position;
}

int apple::getType()
{
    return type;
}

attr_t apple::getAttrs()
{
    switch (type)
    {
    case NORMAL:
        return COLOR_PAIR(1);
    case JUICY:
        return COLOR_PAIR(4);
    case INVINCY:
        return COLOR_PAIR(5);
    case SLOWY:
        return COLOR_PAIR(3);
    case SPEEDY:
        return COLOR_PAIR(6);
    default:
        return A_NORMAL;
    }
}

ostream &operator<<(ostream &os, const apple &a)
{
    if (a.type == NORMAL)
    {
        os << "Normal ";
    }
    else if (a.type == JUICY)
    {
        os << "Juicy ";
    }
    os << "apple at (" << a.position.first << ", " << a.position.second << ")";
    return os;
}