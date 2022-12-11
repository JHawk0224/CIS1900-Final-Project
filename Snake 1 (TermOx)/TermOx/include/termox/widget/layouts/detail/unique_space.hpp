#ifndef TERMOX_WIDGET_LAYOUTS_DETAIL_UNIQUE_SPACE_HPP
#define TERMOX_WIDGET_LAYOUTS_DETAIL_UNIQUE_SPACE_HPP
#include <cstddef>
#include <utility>
#include <vector>

#include <termox/widget/widget.hpp>

namespace ox::layout::detail {

/// Gives space to child Widgets where each gets full use of the length.
template <typename Parameters>
class Unique_space {
   private:
    using Length_list   = std::vector<int>;
    using Position_list = std::vector<int>;

   public:
    [[nodiscard]] auto calculate_lengths(Widget& parent) -> Length_list
    {
        auto result      = Length_list{};
        auto const limit = typename Parameters::Secondary::get_length{}(parent);
        auto children    = parent.get_children();
        auto begin       = std::next(std::begin(children), offset_);
        auto const end   = std::end(children);

        for (; begin != end; ++begin) {
            auto const& policy =
                typename Parameters::Secondary::get_policy{}(*begin);
            if (limit > policy.max())
                result.push_back(policy.max());
            else if (limit < policy.min() && !policy.can_ignore_min())
                result.push_back(0);
            else
                result.push_back(limit);
        }
        return result;
    }

    [[nodiscard]] auto calculate_positions(Length_list const& lengths)
        -> Position_list
    {
        return Position_list(lengths.size(), 0);
    }

    /// Return the child Widget offset, the first widget included in the layout.
    [[nodiscard]] auto get_offset() const -> std::size_t { return offset_; }

    /// Sets the child Widget offset, does not do bounds checking.
    void set_offset(std::size_t index) { offset_ = index; }

   private:
    std::size_t offset_ = 0;
};

}  // namespace ox::layout::detail
#endif  // TERMOX_WIDGET_LAYOUTS_DETAIL_UNIQUE_SPACE_HPP
