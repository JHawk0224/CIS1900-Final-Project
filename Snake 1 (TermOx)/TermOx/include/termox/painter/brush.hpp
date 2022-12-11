#ifndef TERMOX_PAINTER_BRUSH_HPP
#define TERMOX_PAINTER_BRUSH_HPP
#include <tuple>
#include <utility>

#include <termox/painter/color.hpp>
#include <termox/painter/trait.hpp>

namespace ox {

/// Holds the look of any paintable object with Traits and Colors.
/** sizeof(Brush) == 4 Bytes && alignof(Brush) == 2 Bytes. */
class Brush {
   public:
    Color background = Color::Background;
    Color foreground = Color::Foreground;
    Traits traits    = Trait::None;

   public:
    /// Construct a Brush with given Traits and Colors.
    template <typename... Items>
    explicit constexpr Brush(Items... items)
    {
        this->add_items(items...);
    }

   private:
    /// Add a variable number of Traits or Colors to the brush.
    template <typename Head, typename... Tail>
    void constexpr add_items(Head t, Tail... ts)
    {
        this->set_item(t);
        this->add_items(ts...);
    }
    void constexpr add_items() {}

    /// Used by add_items() to set a deail::Background_color.
    void constexpr set_item(Background_color bg)
    {
        background = Color{bg.value};
    }

    /// Used by add_items() to set a deail::Foreground_color.
    void constexpr set_item(Foreground_color fg)
    {
        foreground = Color{fg.value};
    }

    /// Used by add_items() to set an Trait.
    void constexpr set_item(Trait t) { traits |= t; }

    /// Used by add_items() to set Traits.
    void constexpr set_item(Traits t) { traits |= t; }
};

// Pipes -----------------------------------------------------------------------

auto constexpr operator|(Brush& b, Traits ts) -> Brush&
{
    b.traits |= ts;
    return b;
}

[[nodiscard]] auto constexpr operator|(Brush const& b, Traits ts) -> Brush
{
    auto copy = b;
    copy.traits |= ts;
    return copy;
}

[[nodiscard]] auto constexpr operator|(Brush&& b, Traits ts) -> Brush
{
    b.traits |= ts;
    return std::move(b);
}

auto constexpr operator|(Brush& b, Background_color c) -> Brush&
{
    b.background = Color{c.value};
    return b;
}

[[nodiscard]] auto constexpr operator|(Brush const& b, Background_color c)
    -> Brush
{
    auto copy       = b;
    copy.background = Color{c.value};
    return copy;
}

[[nodiscard]] auto constexpr operator|(Brush&& b, Background_color c) -> Brush
{
    b.background = Color{c.value};
    return std::move(b);
}

auto constexpr operator|(Brush& b, Foreground_color c) -> Brush&
{
    b.foreground = Color{c.value};
    return b;
}

[[nodiscard]] auto constexpr operator|(Brush const& b, Foreground_color c)
    -> Brush
{
    auto copy       = b;
    copy.foreground = Color{c.value};
    return copy;
}

[[nodiscard]] auto constexpr operator|(Brush&& b, Foreground_color c) -> Brush
{
    b.foreground = Color{c.value};
    return std::move(b);
}

// -----------------------------------------------------------------------------

/// Compares if the held traits and (back/fore)ground colors are equal.
[[nodiscard]] auto constexpr operator==(Brush a, Brush b) -> bool
{
    return std::tie(a.traits, a.background, a.foreground) ==
           std::tie(b.traits, b.background, b.foreground);
}

/// Combines the two Brushes, using the primary Brush's Colors, if any, first.
[[nodiscard]] auto constexpr merge(Brush primary, Brush secondary) -> Brush
{
    if (primary.background == Color::Background)
        primary.background = secondary.background;
    if (primary.foreground == Color::Foreground)
        primary.foreground = secondary.foreground;
    primary.traits |= secondary.traits;
    return primary;
}

}  // namespace ox
#endif  // TERMOX_PAINTER_BRUSH_HPP
