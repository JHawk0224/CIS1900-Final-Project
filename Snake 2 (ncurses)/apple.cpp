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