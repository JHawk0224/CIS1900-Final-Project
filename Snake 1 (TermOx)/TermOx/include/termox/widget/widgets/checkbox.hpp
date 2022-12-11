#ifndef TERMOX_WIDGET_WIDGETS_CHECKBOX_HPP
#define TERMOX_WIDGET_WIDGETS_CHECKBOX_HPP
#include <memory>
#include <utility>

#include <signals_light/signal.hpp>

#include <termox/common/overload.hpp>
#include <termox/painter/glyph_string.hpp>
#include <termox/system/mouse.hpp>
#include <termox/widget/detail/link_lifetimes.hpp>
#include <termox/widget/layouts/horizontal.hpp>
#include <termox/widget/layouts/vertical.hpp>
#include <termox/widget/pipe.hpp>
#include <termox/widget/widgets/label.hpp>

namespace ox {

/// Checkbox Widget that is either checked or not checked.
/** Uses mouse left button click to toggle between states. */
template <template <typename> typename Layout_t>
class Checkbox : public Label<Layout_t> {
   private:
    using Base_t = Label<Layout_t>;

   public:
    enum class State : bool { Unchecked, Checked };

    struct Display {
        Glyph_string checked;
        Glyph_string unchecked;
    };

    struct Parameters {
        State initial_state;
        Display display;
        bool locked;
    };

   public:
    /// Emitted when box becomes checked.
    sl::Signal<void()> checked;

    /// Emitted when box becomes unchecked.
    sl::Signal<void()> unchecked;

    /// Emitted every time the box changes state.
    sl::Signal<void()> toggled;

   public:
    /// Construct a new Checkbox
    explicit Checkbox(State initial_state, Display display, bool locked);

    /// Construct a new Checkbox
    explicit Checkbox(Parameters p);

   public:
    /// Set the state to be checked.
    void check();

    /// Set the state to be unchecked.
    void uncheck();

    /// Change state to be unchecked if currently checked, checked otherwise.
    void toggle();

    /// Return the current state of the Checkbox as Checkbox::State enum value.
    [[nodiscard]] auto get_state() const -> State;

    /// Lock the Checkbox, it can not be toggled when locked.
    void lock();

    /// Unlock the Checkbox, allowing it to be toggled.
    void unlock();

    /// Return true if the Checkbox is locked.
    [[nodiscard]] auto is_locked() const -> bool;

    /// Set the look of each Checkbox State.
    void set_display(Display d);

    /// Return the look of each Checkbox State.
    [[nodiscard]] auto get_display() -> Display;

   protected:
    auto mouse_press_event(Mouse const& m) -> bool override;

   private:
    State state_;
    Display display_;
    bool locked_;

   private:
    /// Push changes to display_ to the Label base class to update the display.
    void update_display();
};

using HCheckbox = Checkbox<layout::Horizontal>;
using VCheckbox = Checkbox<layout::Vertical>;

/// Helper function to create an HCheckbox instance.
[[nodiscard]] auto hcheckbox(HCheckbox::State initial_state,
                             HCheckbox::Display display,
                             bool locked) -> std::unique_ptr<HCheckbox>;

/// Helper function to create an HCheckbox instance.
[[nodiscard]] auto hcheckbox(HCheckbox::Parameters p)
    -> std::unique_ptr<HCheckbox>;

/// Helper function to create a VCheckbox instance.
[[nodiscard]] auto vcheckbox(VCheckbox::State initial_state,
                             VCheckbox::Display display,
                             bool locked) -> std::unique_ptr<VCheckbox>;

/// Helper function to create a VCheckbox instance.
[[nodiscard]] auto vcheckbox(VCheckbox::Parameters p)
    -> std::unique_ptr<VCheckbox>;

}  // namespace ox

namespace ox::detail {

/// Label, buffer and Checkbox tuple implementation.
template <template <typename> typename Layout_t,
          typename Checkbox_type,
          bool label_last>
class Label_checkbox_impl
    : public Label_wrapper<Layout_t, Checkbox_type, Layout_t, label_last> {
   private:
    using Base_t = Label_wrapper<Layout_t, Checkbox_type, Layout_t, label_last>;

   public:
    using Label_wrapper_t = Base_t;
    using Checkbox_t      = Checkbox_type;
    using Label_t         = Label<Layout_t>;

   public:
    Checkbox_t& checkbox = Base_t::wrapped;
    Label_t& label       = Base_t::label;

   public:
    explicit Label_checkbox_impl(
        typename Base_t::Parameters label_parameters        = {},
        typename Checkbox_t::Parameters checkbox_parameters = {})
        : Base_t{std::move(label_parameters), std::move(checkbox_parameters)}
    {
        using namespace pipe;
        Base_t::label | on_mouse_press([&](auto) { checkbox.toggle(); });
        Base_t::padding | on_mouse_press([&](auto) { checkbox.toggle(); });
    }

   private:
    using Base_t::wrapped;
};

}  // namespace ox::detail

namespace ox {

/// Template function to build a specified Labeled_checkbox type.
/** T is some sort of Labeled_checkbox type. */
template <typename T>
inline auto constexpr make_labeled_cb_fn =
    [](typename T::Label_wrapper_t::Parameters label_parameters = {},
       typename T::Checkbox_t::Parameters checkbox_parameters   = {})
    -> std::unique_ptr<T> {
    return std::make_unique<T>(std::move(label_parameters),
                               std::move(checkbox_parameters));
};

/// Template function to build a specified Labeled_checkbox type.
/** T is some sort of Labeled_checkbox type. */
template <typename Checkbox_t>
inline auto constexpr make_checkbox_fn = Overload{
    [](typename Checkbox_t::Parameters parameters = {})
        -> std::unique_ptr<Checkbox_t> {
        return std::make_unique<Checkbox_t>(std::move(parameters));
    },
    [](typename Checkbox_t::State initial_state,
       bool locked) -> std::unique_ptr<Checkbox_t> {
        return std::make_unique<Checkbox_t>(initial_state, locked);
    },
};

// ☒
class Checkbox1 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox1(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"☒", U"☐"}, locked}
    {}

    Checkbox1(Parameters p) : Checkbox1{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox1 = make_checkbox_fn<Checkbox1>;

using HCheckbox1_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox1, true>;
using HCheckbox_label = HCheckbox1_label;

using HLabel_checkbox1 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox1, false>;
using HLabel_checkbox = HLabel_checkbox1;

using VCheckbox1_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox1, true>;
using VCheckbox_label = VCheckbox1_label;

using VLabel_checkbox1 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox1, false>;
using VLabel_checkbox = VLabel_checkbox1;

inline auto constexpr hcheckbox1_label = make_labeled_cb_fn<HCheckbox_label>;
inline auto constexpr hcheckbox_label  = hcheckbox1_label;
inline auto constexpr hlabel_checkbox1 = make_labeled_cb_fn<HLabel_checkbox>;
inline auto constexpr hlabel_checkbox  = hlabel_checkbox1;
inline auto constexpr vcheckbox1_label = make_labeled_cb_fn<VCheckbox_label>;
inline auto constexpr vcheckbox_label  = vcheckbox1_label;
inline auto constexpr vlabel_checkbox1 = make_labeled_cb_fn<VLabel_checkbox>;
inline auto constexpr vlabel_checkbox  = vlabel_checkbox1;

// [x]
class Checkbox2 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox2(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"[x]", U"[ ]"}, locked}
    {}

    Checkbox2(Parameters p) : Checkbox2{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox2 = make_checkbox_fn<Checkbox2>;

using HCheckbox2_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox2, true>;
using HLabel_checkbox2 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox2, false>;
using VCheckbox2_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox2, true>;
using VLabel_checkbox2 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox2, false>;

inline auto constexpr hcheckbox2_label = make_labeled_cb_fn<HCheckbox2_label>;
inline auto constexpr hlabel_checkbox2 = make_labeled_cb_fn<HLabel_checkbox2>;
inline auto constexpr vcheckbox2_label = make_labeled_cb_fn<VCheckbox2_label>;
inline auto constexpr vlabel_checkbox2 = make_labeled_cb_fn<VLabel_checkbox2>;

// ┌
// x
// └
class Checkbox3 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox3(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"┌x└", U"┌ └"}, locked}
    {}

    Checkbox3(Parameters p) : Checkbox3{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox3 = make_checkbox_fn<Checkbox3>;

using HCheckbox3_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox3, true>;

inline auto constexpr hcheckbox3_label = make_labeled_cb_fn<HCheckbox3_label>;

// ┐
// x
// ┘
class Checkbox4 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox4(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"┐x┘", U"┐ ┘"}, locked}
    {}

    Checkbox4(Parameters p) : Checkbox4{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox4 = make_checkbox_fn<Checkbox4>;

using HLabel_checkbox4 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox4, false>;

inline auto constexpr hlabel_checkbox4 = make_labeled_cb_fn<HLabel_checkbox4>;

// ┌x┐
class Checkbox5 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox5(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"┌x┐", U"┌ ┐"}, locked}
    {}

    Checkbox5(Parameters p) : Checkbox5{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox5 = make_checkbox_fn<Checkbox5>;

using VCheckbox5_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox5, true>;

inline auto constexpr vcheckbox5_label = make_labeled_cb_fn<VCheckbox5_label>;

// └x┘
class Checkbox6 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox6(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"└x┘", U"└ ┘"}, locked}
    {}

    Checkbox6(Parameters p) : Checkbox6{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox6 = make_checkbox_fn<Checkbox6>;

using VLabel_checkbox6 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox6, false>;

inline auto constexpr vlabel_checkbox6 = make_labeled_cb_fn<VLabel_checkbox6>;

// ╭
// x
// ╰
class Checkbox7 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox7(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"╭x╰", U"╭ ╰"}, locked}
    {}

    Checkbox7(Parameters p) : Checkbox7{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox7 = make_checkbox_fn<Checkbox7>;

using HCheckbox7_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox7, true>;

inline auto constexpr hcheckbox7_label = make_labeled_cb_fn<HCheckbox7_label>;

// ╮
// x
// ╯
class Checkbox8 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox8(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"╮x╯", U"╮ ╯"}, locked}
    {}

    Checkbox8(Parameters p) : Checkbox8{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox8 = make_checkbox_fn<Checkbox8>;

using HLabel_checkbox8 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox8, false>;

inline auto constexpr hlabel_checkbox8 = make_labeled_cb_fn<HLabel_checkbox8>;

// ╭x╮
class Checkbox9 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox9(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"╭x╮", U"╭ ╮"}, locked}
    {}

    Checkbox9(Parameters p) : Checkbox9{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox9 = make_checkbox_fn<Checkbox9>;

using VCheckbox9_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox9, true>;

inline auto constexpr vcheckbox9_label = make_labeled_cb_fn<VCheckbox9_label>;

// ╰x╯
class Checkbox10 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox10(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"╰x╯", U"╰ ╯"}, locked}
    {}

    Checkbox10(Parameters p) : Checkbox10{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox10 = make_checkbox_fn<Checkbox10>;

using VLabel_checkbox10 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox10, false>;

inline auto constexpr vlabel_checkbox10 = make_labeled_cb_fn<VLabel_checkbox10>;

// -----------------------------------------------------------------------------

// ┘
// ╴
// ┐
class Checkbox11 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox11(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"┘╴┐", U"┘ ┐"}, locked}
    {}

    Checkbox11(Parameters p) : Checkbox11{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox11 = make_checkbox_fn<Checkbox11>;

using HCheckbox11_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox11, true>;

inline auto constexpr hcheckbox11_label = make_labeled_cb_fn<HCheckbox11_label>;

// └
// ╶
// ┌
class Checkbox12 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox12(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"└╶┌", U"└ ┌"}, locked}
    {}

    Checkbox12(Parameters p) : Checkbox12{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox12 = make_checkbox_fn<Checkbox12>;

using HLabel_checkbox12 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox12, false>;

inline auto constexpr hlabel_checkbox12 = make_labeled_cb_fn<HLabel_checkbox12>;

// ┘╵└
class Checkbox13 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox13(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"┘╵└", U"┘ └"}, locked}
    {}

    Checkbox13(Parameters p) : Checkbox13{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox13 = make_checkbox_fn<Checkbox13>;

using VCheckbox13_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox13, true>;

inline auto constexpr vcheckbox13_label = make_labeled_cb_fn<VCheckbox13_label>;

// ┐╷┌
class Checkbox14 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox14(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"┐╷┌", U"┐ ┌"}, locked}
    {}

    Checkbox14(Parameters p) : Checkbox14{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox14 = make_checkbox_fn<Checkbox14>;

using VLabel_checkbox14 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox14, false>;

inline auto constexpr vlabel_checkbox14 = make_labeled_cb_fn<VLabel_checkbox14>;

// ╯
// ╴
// ╮
class Checkbox15 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox15(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"╯╴╮", U"╯ ╮"}, locked}
    {}

    Checkbox15(Parameters p) : Checkbox15{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox15 = make_checkbox_fn<Checkbox15>;

using HCheckbox15_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox15, true>;

inline auto constexpr hcheckbox15_label = make_labeled_cb_fn<HCheckbox15_label>;

// ╰
// ╶
// ╭
class Checkbox16 : public VCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox16(State initial_state = State::Unchecked, bool locked = false)
        : VCheckbox{initial_state, {U"╰╶╭", U"╰ ╭"}, locked}
    {}

    Checkbox16(Parameters p) : Checkbox16{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox16 = make_checkbox_fn<Checkbox16>;

using HLabel_checkbox16 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox16, false>;

inline auto constexpr hlabel_checkbox16 = make_labeled_cb_fn<HLabel_checkbox16>;

// ╯╵╰
class Checkbox17 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox17(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"╯╵╰", U"╯ ╰"}, locked}
    {}

    Checkbox17(Parameters p) : Checkbox17{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox17 = make_checkbox_fn<Checkbox17>;

using VCheckbox17_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox17, true>;

inline auto constexpr vcheckbox17_label = make_labeled_cb_fn<VCheckbox17_label>;

// ╮╷╭
class Checkbox18 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox18(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"╮╷╭", U"╮ ╭"}, locked}
    {}

    Checkbox18(Parameters p) : Checkbox18{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox18 = make_checkbox_fn<Checkbox18>;

using VLabel_checkbox18 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox18, false>;

inline auto constexpr vlabel_checkbox18 = make_labeled_cb_fn<VLabel_checkbox18>;

// -----------------------------------------------------------------------------

// ├x┤
class Checkbox19 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox19(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"├x┤", U"├ ┤"}, locked}
    {}

    Checkbox19(Parameters p) : Checkbox19{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox19 = make_checkbox_fn<Checkbox19>;

using HCheckbox19_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox19, true>;
using HLabel_checkbox19 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox19, false>;
using VCheckbox19_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox19, true>;
using VLabel_checkbox19 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox19, false>;

inline auto constexpr hcheckbox19_label = make_labeled_cb_fn<HCheckbox19_label>;
inline auto constexpr hlabel_checkbox19 = make_labeled_cb_fn<HLabel_checkbox19>;
inline auto constexpr vcheckbox19_label = make_labeled_cb_fn<VCheckbox19_label>;
inline auto constexpr vlabel_checkbox19 = make_labeled_cb_fn<VLabel_checkbox19>;

// ┤x├
class Checkbox20 : public HCheckbox {
   public:
    struct Parameters {
        State initial_state = State::Unchecked;
        bool locked         = false;
    };

   public:
    Checkbox20(State initial_state = State::Unchecked, bool locked = false)
        : HCheckbox{initial_state, {U"┤x├", U"┤ ├"}, locked}
    {}

    Checkbox20(Parameters p) : Checkbox20{p.initial_state, p.locked} {}
};

inline auto constexpr checkbox20 = make_checkbox_fn<Checkbox20>;

using HCheckbox20_label =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox20, true>;
using HLabel_checkbox20 =
    detail::Label_checkbox_impl<layout::Horizontal, Checkbox20, false>;
using VCheckbox20_label =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox20, true>;
using VLabel_checkbox20 =
    detail::Label_checkbox_impl<layout::Vertical, Checkbox20, false>;

inline auto constexpr hcheckbox20_label = make_labeled_cb_fn<HCheckbox20_label>;
inline auto constexpr hlabel_checkbox20 = make_labeled_cb_fn<HLabel_checkbox20>;
inline auto constexpr vcheckbox20_label = make_labeled_cb_fn<VCheckbox20_label>;
inline auto constexpr vlabel_checkbox20 = make_labeled_cb_fn<VLabel_checkbox20>;

}  // namespace ox

namespace ox::slot {

template <template <typename> typename Layout_t>
auto toggle(Checkbox<Layout_t>& cb) -> sl::Slot<void()>;

template <template <typename> typename Layout_t>
auto check(Checkbox<Layout_t>& cb) -> sl::Slot<void()>;

template <template <typename> typename Layout_t>
auto uncheck(Checkbox<Layout_t>& cb) -> sl::Slot<void()>;

}  // namespace ox::slot
#endif  // TERMOX_WIDGET_WIDGETS_CHECKBOX_HPP
