#ifndef TERMOX_SYSTEM_ANIMATION_ENGINE_HPP
#define TERMOX_SYSTEM_ANIMATION_ENGINE_HPP
#include <map>
#include <mutex>

#include <termox/common/lockable.hpp>
#include <termox/common/timer.hpp>
#include <termox/system/event_loop.hpp>
#include <termox/system/event_queue.hpp>

namespace ox {
class Widget;

/// Registers Widgets with intervals to send timer events.
class Animation_engine : private Lockable<std::recursive_mutex> {
   public:
    using Clock_t    = Timer::Clock_t;
    using Duration_t = Timer::Duration_t;
    using Time_point = Timer::Time_point;

    struct Registered_data {
        Duration_t interval;
        Time_point last_event_time;
    };

    static auto constexpr default_interval = Duration_t{100};

   public:
    /// Register to start sending Timer_events to \p w every \p interval.
    void register_widget(Widget& w, Duration_t interval);

    /// Register to start sending Timer_events to \p w at \p fps.
    void register_widget(Widget& w, FPS fps);

    /// Stop the given Widget from being sent Timer_events.
    void unregister_widget(Widget& w);

    /// Return true if there are no registered widgets
    [[nodiscard]] auto is_empty() const -> bool;

    /// Start another thread that waits on intervals and sents timer events.
    void start();

    /// Sends exit signal and waits for animation thread to exit.
    void stop();

    /// Return true if start() has been called, and hasn't been exited.
    [[nodiscard]] auto is_running() const -> bool;

   private:
    std::map<Widget*, Registered_data> subjects_;
    Event_loop loop_;
    Timer timer_ = Timer{default_interval};

   private:
    /// Post any Timer_events that are ready to be posted.
    auto get_timer_events() -> std::vector<Timer_event>&;

    /// Waits on intervals then sends Timer_events.
    void loop_function(Event_queue& queue);
};

}  // namespace ox
#endif  // TERMOX_SYSTEM_ANIMATION_ENGINE_HPP
