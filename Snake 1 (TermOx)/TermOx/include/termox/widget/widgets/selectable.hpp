#ifndef TERMOX_WIDGET_WIDGETS_SELECTABLE_HPP
#define TERMOX_WIDGET_WIDGETS_SELECTABLE_HPP
#include <termox/painter/trait.hpp>
#include <termox/widget/pipe.hpp>

namespace ox {

/// Wraps Widget_t to provide select() and unselect() methods to modify display.
template <typename Widget_t,
          typename Select_method   = void,
          typename Unselect_method = void>
class Selectable : public Widget_t {
   public:
    /// Provide two methods to modify Widget_t. Signature: void(Widget_t&);
    Selectable(Select_method s, Unselect_method u)
        : Widget_t{}, select_{std::move(s)}, unselect_{std::move(u)}
    {}

    Selectable(Select_method s,
               Unselect_method u,
               typename Widget_t::Parameters p)
        : Widget_t{std::move(p)}, select_{std::move(s)}, unselect_{std::move(u)}
    {}

   public:
    /// Change visual to mark as selected.
    void select() { select_(*this); }

    /// Change visual to mark as unselected.
    void unselect() { unselect_(*this); }

   private:
    Select_method select_;
    Unselect_method unselect_;
};

/// Helper function to create a selectable instance.
template <typename Widget_t, typename Select_method, typename Unselect_method>
[[nodiscard]] auto selectable(Select_method s, Unselect_method u)
    -> std::unique_ptr<Selectable<Widget_t, Select_method, Unselect_method>>
{
    return std::make_unique<
        Selectable<Widget_t, Select_method, Unselect_method>>(std::move(s),
                                                              std::move(u));
}

/// Helper function to create a selectable instance.
template <typename Widget_t, typename Select_method, typename Unselect_method>
[[nodiscard]] auto selectable(Select_method s,
                              Unselect_method u,
                              typename Widget_t::Parameters p)
    -> std::unique_ptr<Selectable<Widget_t, Select_method, Unselect_method>>
{
    return std::make_unique<
        Selectable<Widget_t, Select_method, Unselect_method>>(
        std::move(s), std::move(u), std::move(p));
}

/// Default overload that set's Widget_t's brush to Trait::Inverse.
template <typename Widget_t>
class Selectable<Widget_t, void, void> : public Widget_t {
   public:
    using Parameters = typename Widget_t::Parameters;

   public:
    Selectable() = default;

    Selectable(Parameters p) : Widget_t{std::move(p)} {}

   public:
    /// Change visual to mark as selected.
    void select()
    {
        *this | Trait::Inverse;
        *this | pipe::descendants() | Trait::Inverse;
    }

    /// Change visual to mark as unselected.
    void unselect()
    {
        *this | pipe::discard(Trait::Inverse);
        *this | pipe::descendants() | pipe::discard(Trait::Inverse);
    }
};

/// Helper function to create a Selectable instance.
template <typename Widget_t>
[[nodiscard]] auto selectable() -> std::unique_ptr<Selectable<Widget_t>>
{
    return std::make_unique<Selectable<Widget_t>>();
}

/// Helper function to create a Selectable instance.
template <typename Widget_t>
[[nodiscard]] auto selectable(typename Selectable<Widget_t>::Parameters p)
    -> std::unique_ptr<Selectable<Widget_t>>
{
    return std::make_unique<Selectable<Widget_t>>(std::move(p));
}

}  // namespace ox
#endif  // TERMOX_WIDGET_WIDGETS_SELECTABLE_HPP
