#include "game.hpp"

#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string s;
    bool gameExists = false;
    unique_ptr<game> g;

    cout << "Welcome to Snake!" << endl;
    cout << "Commands:" << endl;
    cout << "\tnew <width> <height>" << endl;
    cout << "\ttick" << endl;
    cout << "\tdir <x>" << endl;
    cout << "\tquit" << endl;

    while (getline(cin, s)) // terminate when EOF is received
    {
        istringstream iss{s};
        string command;

        iss >> command;

        if (command == "new")
        {
            int width, height;
            iss >> width >> height;
            g = make_unique<game>(width, height);
            cout << *g << endl;
            gameExists = true;
        }
        else if (command == "tick")
        {
            if (!gameExists)
            {
                cout << "Invalid command" << endl;
                continue;
            }
            int result = g->tick();
            // loss
            if (result != 0)
            {
                cout << *g << endl;
                cout << "You lose!" << endl;
                gameExists = false;
            }
            else
            {
                cout << *g << endl;
            }
        }
        else if (command == "dir")
        {
            if (!gameExists)
            {
                cout << "Invalid command" << endl;
                continue;
            }

            string dir;
            iss >> dir;
            int x;
            if (dir == "down")
            {
                x = 0;
            }
            else if (dir == "right")
            {
                x = 1;
            }
            else if (dir == "up")
            {
                x = 2;
            }
            else if (dir == "left")
            {
                x = 3;
            }
            else
            {
                x = stoi(dir);
            }
            g->turn(0, x);
            cout << *g << endl;
        }
        else if (command == "quit")
        {
            gameExists = false;
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}
