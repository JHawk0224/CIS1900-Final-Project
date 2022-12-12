#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdlib>
#include <ncurses.h>
#include <chrono>
#include <sys/time.h>
#include <time.h>

class board
{
private:
    WINDOW *board_window;
    WINDOW *screen;
    int height, width, start_row, start_col;
    int timeout;
    void construct(int height, int width, int time_per_turn)
    {
        int max_x, max_y;
        getmaxyx(stdscr, max_y, max_x);
        this->height = height;
        this->width = width;
        start_row = (max_y - height) / 2;
        start_col = (max_x - width) / 2;
        timeout = time_per_turn;
        board_window = newwin(height, width, start_row, start_col);
        screen = stdscr;
        setTimeout(time_per_turn);
        keypad(board_window, true);
    }
public:
    board(int height, int width, int time_per_turn)
    {
        construct(height, width, time_per_turn);
    }
    board(int height, int width)
    {
        construct(height, width, 300);
    }
    WINDOW* getWindow()
    {
        return board_window;
    }
    int getStartRow()
    {
        return start_row;
    }
    int getStartCol()
    {
        return start_col;
    }
    int getTimeout()
    {
        return timeout;
    }
    void setTimeout(int time_per_turn)
    {
        timeout = time_per_turn;
        wtimeout(board_window, time_per_turn);
    }
    static time_t milliseconds()
    {
        struct timeval curr_time
        {};
        gettimeofday(&curr_time, nullptr);
        return curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
    }
    static int randomInt(int min, int max)
    {
        srand(milliseconds());
        return (int)(rand() % (max - min)) + min;;
    }
    void clear()
    {
        wclear(board_window);
        addBorder();
    }
    void refresh()
    {
        wrefresh(screen);
        wrefresh(board_window);
    }
    void initialize()
    {
        clear();
        refresh();
    }
    void addBorder()
    {
        box(board_window, 0, 0);
    }
    chtype getInput()
    {
        time_t last_time = milliseconds();
        chtype input = wgetch(board_window);
        chtype new_input = ERR;
        chtype compare = ERR;
        wtimeout(board_window, 0);
        while (last_time + timeout >= milliseconds())
        {
            new_input = wgetch(board_window);
        }
        wtimeout(board_window, timeout);
        if (new_input != compare)
        {
            input = new_input;
        }
        return input;
    }
    chtype getCharAt(int row, int col)
    {
        return mvwinch(board_window, row, col);
    }
    void addAt(int row, int col, chtype ch, attr_t attrs = A_NORMAL)
    {
        wattron(board_window, attrs);
        mvwaddch(board_window, row, col, ch);
        wattroff(board_window, attrs);
    }
    void addAt(std::pair<int, int> loc, chtype ch, attr_t attrs = A_NORMAL)
    {
        addAt(loc.first, loc.second, ch, attrs);
    }
    template <typename Container>
    void addList(Container positions, chtype ch, attr_t attrs = A_NORMAL)
    {
        for (auto pos : positions)
        {
            addAt(pos.first, pos.second, ch, attrs);
        }
    }
    void drawStatus(int score, attr_t attrs = A_NORMAL)
    {
        int maxX, maxY;
        getmaxyx(screen, maxY, maxX);
        wattron(screen, attrs);
        mvwprintw(screen, maxY - 1, 2, "Score: %d", score);
        wattroff(screen, attrs);
    }
};

#endif
