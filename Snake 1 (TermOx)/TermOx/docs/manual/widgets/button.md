# Button Widgets

[`<termox/widget/widgets/button.hpp>`](../../../include/termox/widget/widgets/button.hpp)

## `Button`

Emits `pressed` signal on left mouse button press, and `released` on left mouse
button release. Constructor takes a `Glyph_string` which is centered
horizontally and vertically on the Widget.

```cpp
class Button : public Widget {
   public:
    sl::Signal<void()> pressed;
    sl::Signal<void()> released;

    struct Parameters { Glyph_string text = U""; };

   public:
    Button(Glyph_string text = U"");
    Button(Parameters);

    // Set the text and repaint.
    void set_text(Glyph_string text);

    // Return the current text.
    auto text() const -> Glyph_string const&;
};
```

## `Push_button`

A Button that changes its background color on `pressed` signal, and resets the
color on `released` signal.

```cpp
class Push_button : public Button {
   public:
    struct Parameters {
        Glyph_string text;
        Color pressed_color  = Color::Foreground;
        Color released_color = Color::Background;
    };

   public:
    Push_button(Glyph_string text    = U"",
                Color pressed_color  = Color::Foreground,
                Color released_color = Color::Background);

    Push_button(Parameters);

   public:
    // Set the background Color of the Button when pressed Signal is emitted.
    void set_pressed_color(Color c);

    // Return the current Color assigned to mouse press events.
    auto get_pressed_color() const -> Color;

    // Set the background Color of the Button when released Signal is emitted.
    void set_released_color(Color c);

    // Return the current Color assigned to mouse release events.
    auto get_released_color() const -> Color;
};
```

## `Thin_button`

A Button with a height or width of one. Type aliases `VThin_button` for a fixed
width of 1, and `HThin_button` for a fixed height of 1.

```cpp
template <template <typename> typename Layout_t>
class Thin_button : public Button {
   public:
    using Button::Parameters;

   public:
    Thin_button(Glyph_string text = U"");
    Thin_button(Parameters);
};

using HThin_button = Thin_button<layout::Horizontal>;
using VThin_button = Thin_button<layout::Vertical>;
```
