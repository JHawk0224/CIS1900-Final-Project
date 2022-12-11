#ifndef TERMOX_TERMINAL_DETAIL_SCREEN_BUFFERS_HPP
#define TERMOX_TERMINAL_DETAIL_SCREEN_BUFFERS_HPP
#include <termox/terminal/detail/canvas.hpp>
#include <termox/widget/area.hpp>

namespace ox::detail {

/// Holds the current and next screen buffers as Canvas objects.
/** Provides merge and diff capabilities for the two buffers to determine what
 *  has changed and what should be written to the screen. */
class Screen_buffers {
   public:
    Canvas current;
    Canvas next;

   public:
    /// Construct with both Canvas objects having Area \p a.
    Screen_buffers(ox::Area a);

   public:
    /// Resizes both current and next Canvas objects to \p a.
    void resize(ox::Area a);

    /// Return the current size of the screen buffers.
    [[nodiscard]] auto area() const -> Area;

    /// Merges the next Canvas into the current Canvas.
    /** This will copy every Glyph from next that differs with current into
     *  current Canvas. */
    void merge();

    /// Merges the next Canvas into the current Canvas and returns the changes.
    /** This will copy every Glyph from next that differs with current into
     *  current, and writes that change to the returned Canvas::Diff object. */
    [[nodiscard]] auto merge_and_diff() -> Canvas::Diff const&;

    /// Generates a Canvas::Diff, with every Glyph from current that has \p c.
    /** This isn't a true difference, it is meant to be used to generate a list
     *  of Glyphs that need to be re-written to the screen. Used by
     *  Dynamic_color_engine. */
    [[nodiscard]] auto generate_color_diff(Color c) -> Canvas::Diff const&;

    /// Returns the entire current screen as a Diff. Used on Window Resize.
    [[nodiscard]] auto current_screen_as_diff() -> Canvas::Diff const&;

   private:
    Canvas::Diff diff_;
};

}  // namespace ox::detail
#endif  // TERMOX_TERMINAL_DETAIL_SCREEN_BUFFERS_HPP
