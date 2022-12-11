#include <iostream>
#include <ncurses.h>
#include "game.hpp"

using namespace std;

int main()
{
    initscr();
    clear();
    refresh();
    curs_set(0);
    noecho();
    if (!has_colors() || !can_change_color())
    {
        endwin();
        cout << "Your terminal does not support color." << endl;
        return 1;
    }
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);

    game game(20, 20 * 2.5, 100);
    game.draw();
		
	while (game.isPlaying())
    {
        game.processInput();
        game.tick();
        game.draw();
    }

    endwin();
    cout << "You scored " << game.getScore() << " points!" << endl;
    return 0;
}
