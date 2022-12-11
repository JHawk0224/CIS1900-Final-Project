#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <termox/termox.hpp>

namespace color {

inline auto constexpr Fade    = ox::Color{16};
inline auto constexpr Rainbow = ox::Color{17};

inline auto constexpr Apple            = Fade;
inline auto constexpr Snake            = Rainbow;
inline auto constexpr Border           = ox::stormy6::Teal;
inline auto constexpr Instruction_fg   = ox::stormy6::White;
inline auto constexpr Instruction_bg   = ox::stormy6::Teal;
inline auto constexpr Start_bg         = ox::stormy6::Green;
inline auto constexpr Pause_bg         = ox::stormy6::Red;
inline auto constexpr Size_bg          = ox::stormy6::White;
inline auto constexpr Size_fg          = ox::stormy6::Black;
inline auto constexpr Score_bg         = ox::stormy6::White;
inline auto constexpr Score_fg         = ox::stormy6::Black;
inline auto constexpr Instruction_text = ox::stormy6::Orange;

}  // namespace color

inline auto const snake_palette = [] {
    auto pal = ox::stormy6::palette;
    pal.push_back({color::Fade, ox::dynamic::fade<ox::dynamic::Sine>(
                                    ox::RGB{0x7f9860}, ox::RGB{0xa95a3f})});
    pal.push_back({color::Rainbow, ox::dynamic::rainbow()});
    return pal;
}();

class Snake_game : public ox::layout::Vertical<> {
   private:
    using Floating_game = ox::Float_2d<Game_space>;

   public:
    Snake_game();

   private:
    Floating_game& floating_game = make_child<Floating_game>();
    Game_space& game_space_ = floating_game.widget.widget;
    HPair& bottom_ = make_child<ox::HPair<ox::HPair<ox::Hlabel, ox::Int_view>, ox::HPair<ox::Hlabel, ox::Int_view>>>();
};

#endif