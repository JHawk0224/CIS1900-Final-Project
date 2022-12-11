#include <termox/painter/detail/is_paintable.hpp>

#include <termox/widget/widget.hpp>

namespace ox::detail {

auto is_paintable(Widget const& w) -> bool
{
    return w.is_enabled() && (w.area().width != 0) && (w.area().height != 0);
}

}  // namespace ox::detail
