#include <memory>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> randomAppleLocations(int width,
                                            int height,
                                            std::vector<std::pair<int, int>> excludeLocs,
                                            int number)
{
    if (number > width * height - 1)
    {
        return vector<pair<int, int>>{};
    }

    random_device rd;
    default_random_engine g{rd()};

    vector<pair<int, int>> v;
    for (int i {0}; i < width; ++i)
    {
        for (int j {0}; j < height; ++j)
        {
            pair<int, int> p {make_pair(i, j)};
            if (count(excludeLocs.begin(), excludeLocs.end(), p) == 0)
            {
                v.push_back(p);
            }
        }
    }

    shuffle(v.begin(), v.end(), g);

    vector<pair<int, int>> result{v.begin(), v.begin() + number};

    return result;
}
