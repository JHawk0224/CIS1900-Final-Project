#include "game.hpp"

#include <iostream>
#include <sstream>

#include <termox/termox.hpp>

Snake_game::Snake_game()
{
    using namespace ox;
    using namespace ox::pipe;
    *this | direct_focus() | forward_focus(game_space_) |
        on_focus_in([] { ox::Terminal::set_palette(snake_palette); });

    bottom_ | fixed_height(1);
    bottom_.buttons.start.connect([this] { game_space_.start(); });
    bottom_.buttons.pause.connect([this] { game_space_.stop(); });

    auto constexpr s_size = ox::Area{60, 17};
    auto constexpr m_size = ox::Area{100, 27};
    auto constexpr l_size = ox::Area{160, 37};
    auto constexpr x_size = ox::Area{230, 47};

    bottom_.buttons.size_change.connect([=](char c) {
        switch (c) {
            case 's': game_space_.resize(s_size); break;
            case 'm': game_space_.resize(m_size); break;
            case 'l': game_space_.resize(l_size); break;
            case 'x': game_space_.resize(x_size); break;
        }
    });

    floating_game.buffer_1 | bg(color::Border);
    floating_game.buffer_2 | bg(color::Border);
    floating_game.widget.buffer_1 | bg(color::Border);
    floating_game.widget.buffer_2 | bg(color::Border);

    game_space_.resize(s_size);
    game_space_.score.connect(
        [this](unsigned score) { bottom_.score.set(score); });
    game_space_.started.connect(
        [this] { bottom_.buttons.show_pause_button(); });
    game_space_.stopped.connect(
        [this] { bottom_.buttons.show_start_button(); });
}