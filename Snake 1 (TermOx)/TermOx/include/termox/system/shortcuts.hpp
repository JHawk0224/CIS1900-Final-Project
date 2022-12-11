#ifndef TERMOX_SYSTEM_SHORTCUTS_HPP
#define TERMOX_SYSTEM_SHORTCUTS_HPP
#include <unordered_map>

#include <signals_light/signal.hpp>

#include <termox/system/key.hpp>

namespace ox {

/// Provides functions for defining global keyboard shortcuts.
class Shortcuts {
   public:
    /// Add an entry for the \p key, returning a Signal to connect an action to.
    /** Key has combined key presses defined for multi-key shortcuts. The
     *  returned Signal reference will be called each time the keyboard shortcut
     *  is encountered. */
    [[nodiscard]] static auto add_shortcut(Key k) -> sl::Signal<void()>&;

    /// Stop \p key and its associated Signal from being called.
    /** No-op if key is not an existing shortcut. */
    static void remove_shortcut(Key k);

    /// Remove all shortcuts from the system.
    static void clear();

    /// Call on the associated Signal if \p key exists as a shortcut.
    /** Returns true if the key was used as a shortcut. */
    static auto send_key(Key k) -> bool;

    /// Stop all shortcuts from working.
    static void disable_all();

    /// Allow all shortcuts to be processed, on by default.
    static void enable_all();

   private:
    using Map_t = std::unordered_map<Key, sl::Signal<void()>>;
    inline static Map_t shortcuts_;
    inline static bool enabled_ = true;
};

}  // namespace ox
#endif  // TERMOX_SYSTEM_SHORTCUTS_HPP
