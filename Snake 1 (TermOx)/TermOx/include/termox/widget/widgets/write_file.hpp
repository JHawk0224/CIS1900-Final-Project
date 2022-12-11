#ifndef TERMOX_WIDGET_WIDGETS_WRITE_FILE_HPP
#define TERMOX_WIDGET_WIDGETS_WRITE_FILE_HPP
#include <fstream>

#include <signals_light/signal.hpp>

#include <termox/widget/pipe.hpp>
#include <termox/widget/tuple.hpp>
#include <termox/widget/widgets/button.hpp>
#include <termox/widget/widgets/line_edit.hpp>
#include <termox/widget/widgets/tile.hpp>

namespace ox::detail {

struct Write_file_widgets : HTuple<Button, Tile, Line_edit> {
    Button& save_btn         = this->get<0>();
    Tile& buffer             = this->get<1>();
    Line_edit& filename_edit = this->get<2>();

    Write_file_widgets();
};

}  // namespace ox::detail

namespace ox {

template <typename Char_t = char>
class Write_file : public detail::Write_file_widgets {
   public:
    using Stream_t = std::basic_ofstream<Char_t>;

   public:
    sl::Signal<void(Stream_t&)> request;

   public:
    Write_file()
    {
        save_btn | pipe::on_press([this] { this->notify(); });
    }

   private:
    void notify()
    {
        auto ofs = Stream_t{filename_edit.text().str()};
        request.emit(ofs);
    }
};

/// Helper function to create a Write_file instance.
template <typename Char_t = char>
[[nodiscard]] auto write_file() -> std::unique_ptr<Write_file<Char_t>>
{
    return std::make_unique<Write_file<Char_t>>();
}

}  // namespace ox
#endif  // TERMOX_WIDGET_WIDGETS_WRITE_FILE_HPP
