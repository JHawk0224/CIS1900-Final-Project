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
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

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
