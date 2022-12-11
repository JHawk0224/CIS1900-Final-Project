#ifndef TERMOX_WIDGET_WIDGETS_ACCORDION_HPP
#define TERMOX_WIDGET_WIDGETS_ACCORDION_HPP
#include <memory>
#include <utility>

#include <signals_light/signal.hpp>

#include <termox/painter/color.hpp>
#include <termox/painter/glyph_string.hpp>
#include <termox/painter/painter.hpp>
#include <termox/painter/trait.hpp>
#include <termox/widget/layouts/detail/linear_layout.hpp>
#include <termox/widget/layouts/horizontal.hpp>
#include <termox/widget/layouts/opposite.hpp>
#include <termox/widget/layouts/passive.hpp>
#include <termox/widget/layouts/vertical.hpp>
#include <termox/widget/pipe.hpp>
#include <termox/widget/widgets/label.hpp>
#include <termox/widget/widgets/text_view.hpp>

namespace ox {

/// Layout_t is the Layout to use for the Bar, not Accordion.
template <template <typename> typename Layout_t>
class Bar : public Layout_t<Widget> {
   private:
    class Indicator : public Widget {
       public:
        Indicator()
        {
            using namespace pipe;
            if constexpr (layout::is_vertical_v<Layout_t<Widget>>)
                *this | fixed_height(1);
            else
                *this | fixed_width(3);
        }

       public:
        void plus()
        {
            x_ = U"[+]";
            this->update();
        }

        void minus()
        {
            x_ = U"[-]";
            this->update();
        }

       protected:
        auto paint_event(Painter& p) -> bool override
        {
            p.put(x_, {0, 0});
            return Widget::paint_event(p);
        }

       private:
        Glyph_string x_ = U"[+]";
    };

    class Title : public layout::Opposite_t<Layout_t<Widget>> {
       public:
        struct Parameters {
            Glyph_string title;
            Align alignment = is_vertical ? Align::Left : Align::Top;
            Glyph wallpaper = is_vertical ? U'─' : U'│';
        };

       public:
        sl::Signal<void()> clicked;

       public:
        Title(Parameters p)
            : centered_text_{this->template make_child<Label<Layout_t>>(
                  {(Glyph_string{U' '}
                        .append(std::move(p.title))
                        .append(U' ')) |
                       Trait::Bold,
                   p.alignment, extra_left})}
        {
            using namespace ox::pipe;
            if constexpr (is_vertical)
                centered_text_ | fixed_height(1);
            else {
                this->insert_child(widget(), 0);
                this->insert_child(widget(), 2);
                *this | children() | fixed_width(1);
            }
            *this | children() |
                on_mouse_press([this](auto const&) { this->clicked(); });
            centered_text_.set_wallpaper(p.wallpaper);
        }

       private:
        Label<Layout_t>& centered_text_;

        static auto constexpr is_vertical =
            layout::is_vertical_v<layout::Opposite_t<Layout_t<Widget>>>;

        static auto constexpr extra_left = is_vertical ? 3 : 1;
    };

   private:
    static auto constexpr is_vertical = layout::is_vertical_v<Layout_t<Widget>>;

   public:
    using Parameters = typename Title::Parameters;

   public:
    sl::Signal<void()> toggle_request;

   public:
    Bar(Parameters p) : text_{this->template make_child<Title>(std::move(p))}
    {
        using namespace pipe;
        if constexpr (is_vertical)
            *this | fixed_width(3);
        else
            *this | fixed_height(1);

        this->collapse();

        indicator_.mouse_pressed.connect(
            [this](auto const&) { this->toggle_request(); });
        text_.clicked.connect([this] { this->toggle_request(); });
    }

   public:
    void expand() { indicator_.minus(); }

    void collapse() { indicator_.plus(); }

    auto indicator_widget() -> Indicator& { return indicator_; }

    auto title_widget() -> Title& { return text_; }

   private:
    Indicator& indicator_ = this->template make_child<Indicator>();
    Title& text_;
};

enum class Bar_position { First, Last };

template <template <typename> typename Layout_t,
          typename Widget_t,
          Bar_position position = Bar_position::First>
class Accordion : public Passive<Layout_t<Widget>> {
   private:
    static_assert(layout::is_vertical_v<Layout_t<Widget>> ||
                  layout::is_horizontal_v<Layout_t<Widget>>);

   private:
    using Bar_t =
        Bar<layout::Opposite_template<Layout_t<Widget>>::template type>;

   public:
    using Parameters = typename Bar_t::Parameters;

   public:
    // TODO add unique_ptr<Widget_t> overload, since this is a wrapper, and add
    // free functions for this type of constructor.

    /// Create an Accordion with \p args... going to Widget_t constructor.
    template <typename... Args>
    Accordion(Parameters p, Args&&... args)
        : bar_{this->template make_child<Bar_t>(std::move(p))},
          wrapped_{
              this->template make_child<Widget_t>(std::forward<Args>(args)...)}
    {
        if constexpr (wrapped_index_ == 0)
            this->swap_children(0, 1);

        bar_.toggle_request.connect([this] { this->toggle_expansion(); });

        this->collapse();
    }

   public:
    /// Enable the wrapped Widget.
    void expand()
    {
        expanded_ = true;
        bar_.expand();
        this->reinsert_wrapped();
        this->enable(this->is_enabled());
    }

    /// Disable the wrapped Widget.
    void collapse()
    {
        expanded_ = false;
        bar_.collapse();
        this->extract_wrapped();
        this->enable(this->is_enabled());
    }

    void toggle_expansion()
    {
        if (expanded_)
            this->collapse();
        else
            this->expand();
    }

    /// Return the wrapped widget.
    [[nodiscard]] auto wrapped() -> Widget_t& { return wrapped_; }

    /// Return the wrapped widget.
    [[nodiscard]] auto wrapped() const -> Widget_t const& { return wrapped_; }

    /// Return the titled Bar widget.
    [[nodiscard]] auto bar() -> Bar_t& { return bar_; }

    /// Return the titled Bar widget.
    [[nodiscard]] auto bar() const -> Bar_t const& { return bar_; }

   private:
    Bar_t& bar_;
    Widget_t& wrapped_;

    bool expanded_                     = true;
    std::unique_ptr<Widget> w_storage_ = nullptr;

    static auto constexpr wrapped_index_ =
        position == Bar_position::First ? 1 : 0;

    static auto constexpr is_vertical = layout::is_vertical_v<Layout_t<Widget>>;

   private:
    void reinsert_wrapped()
    {
        if (w_storage_ == nullptr)
            return;
        this->insert_child(std::move(w_storage_), wrapped_index_);
        w_storage_ = nullptr;
    }

    void extract_wrapped()
    {
        if (w_storage_ == nullptr)
            w_storage_ = this->remove_child_at(wrapped_index_);
    }
};

template <template <typename> typename Layout_t,
          typename Widget_t,
          Bar_position position = Bar_position::First,
          typename... Args>
[[nodiscard]] auto accordion(Args&&... args)
    -> std::unique_ptr<Accordion<Layout_t, Widget_t, position>>
{
    return std::make_unique<Accordion<Layout_t, Widget_t, position>>(
        std::forward<Args>(args)...);
}

template <typename Widget_t, Bar_position position = Bar_position::First>
using HAccordion = Accordion<layout::Horizontal, Widget_t, position>;

template <typename Widget_t,
          Bar_position position = Bar_position::First,
          typename... Args>
[[nodiscard]] auto haccordion(Args&&... args)
    -> std::unique_ptr<HAccordion<Widget_t, position>>
{
    return std::make_unique<HAccordion<Widget_t, position>>(
        std::forward<Args>(args)...);
}

template <typename Widget_t, Bar_position position = Bar_position::First>
using VAccordion = Accordion<layout::Vertical, Widget_t, position>;

template <typename Widget_t,
          Bar_position position = Bar_position::First,
          typename... Args>
[[nodiscard]] auto vaccordion(Args&&... args)
    -> std::unique_ptr<VAccordion<Widget_t, position>>
{
    return std::make_unique<VAccordion<Widget_t, position>>(
        std::forward<Args>(args)...);
}

}  // namespace ox
#endif  // TERMOX_WIDGET_WIDGETS_ACCORDION_HPP
