#include <termox/termox.hpp>

class Menu : public ox::Menu_stack {
   public:
    Menu()
    {
        using namespace ox;
        using namespace ox::pipe;

        Shortcuts::add_shortcut(Key::Escape).connect([this] {
            this->Menu_stack::goto_menu();
        });

        //this->make_page<snake::Snake_game>(U"Snake Game" | brush);
        //this->make_page<fractal::Fractal_demo>(U"Fractals" | brush);
        this->make_page<ox::Textbox>("Play Game");
        this->make_page<ox::Textbox>("Instructions");
        this->make_page<ox::Textbox>("Settings");
    }
};

class SnakeTUI : public ox::layout::Vertical<> {
   public:
    ox::Titlebar& title_ = this->make_child<ox::Titlebar>("Welcome to Snake!");
    Menu& menu = this->make_child<Menu>();

   public:
    SnakeTUI()
    {
        using namespace ox::pipe;
        *this | direct_focus() | forward_focus(menu);
    }
};

int main()
{
    return ox::System{ox::Mouse_mode::Drag}.run<SnakeTUI>();
}