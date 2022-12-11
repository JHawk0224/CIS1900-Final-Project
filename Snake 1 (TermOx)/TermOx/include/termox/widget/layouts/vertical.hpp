#ifndef TERMOX_WIDGET_LAYOUTS_VERTICAL_HPP
#define TERMOX_WIDGET_LAYOUTS_VERTICAL_HPP
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include <termox/widget/layouts/detail/linear_layout.hpp>

namespace ox::layout::v_detail {

struct Get_area {
    [[nodiscard]] auto operator()(int primary, int secondary) const -> Area
    {
        return {secondary, primary};
    }
};

struct Get_point {
    [[nodiscard]] auto operator()(int primary, int secondary) const -> Point
    {
        return {secondary, primary};
    }
};

struct Primary_policy {
    [[nodiscard]] auto operator()(Widget const& w) const -> Size_policy const&
    {
        return w.height_policy;
    }
};

struct Primary_length {
    [[nodiscard]] auto operator()(Widget const& w) const -> int
    {
        return w.area().height;
    }
};

struct Primary_offset {
    [[nodiscard]] auto operator()(Widget const& w) const -> int
    {
        return w.top_left().y;
    }
};

struct Secondary_policy {
    [[nodiscard]] auto operator()(Widget const& w) const -> Size_policy const&
    {
        return w.width_policy;
    }
};

struct Secondary_length {
    [[nodiscard]] auto operator()(Widget const& w) const -> int
    {
        return w.area().width;
    }
};

struct Secondary_offset {
    [[nodiscard]] auto operator()(Widget const& w) const -> int
    {
        return w.top_left().x;
    }
};

using Primary = detail::
    Dimension_parameters<Primary_policy, Primary_length, Primary_offset>;

using Secondary = detail::
    Dimension_parameters<Secondary_policy, Secondary_length, Secondary_offset>;

using Vertical_parameters =
    detail::Linear_layout_parameters<Primary, Secondary, Get_area, Get_point>;

}  // namespace ox::layout::v_detail

namespace ox::layout {

template <typename Child_t = Widget>
using Vertical = detail::Linear_layout<Child_t, v_detail::Vertical_parameters>;

/// Helper function to create an instance.
template <typename Widget_t = Widget, typename... Args>
[[nodiscard]] auto vertical(Args&&... args)
    -> std::unique_ptr<Vertical<Widget_t>>
{
    return std::make_unique<Vertical<Widget_t>>(std::forward<Args>(args)...);
}

namespace detail {
template <typename Child_t>
auto is_vertical_impl(layout::Vertical<Child_t>&) -> std::true_type;

auto is_vertical_impl(...) -> std::false_type;
}  // namespace detail

template <typename T>
using Is_vertical = decltype(detail::is_vertical_impl(std::declval<T&>()));

/// True if the given type is a layout::Vertical type or derived from.
template <typename T>
inline bool constexpr is_vertical_v = Is_vertical<T>::value;

}  // namespace ox::layout
#endif  // TERMOX_WIDGET_LAYOUTS_VERTICAL_HPP
