#ifndef KEYBOARD_HOOK_H
#define KEYBOARD_HOOK_H
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <exception>
#include <functional>
#include <vector>

namespace bebop_keyboard_controller {

using movement_callback = std::function<void()>;

constexpr std::uint32_t UP = static_cast<std::uint32_t>(XK_Up);
constexpr std::uint32_t DOWN = static_cast<std::uint32_t>(XK_Down);
constexpr std::uint32_t LEFT = static_cast<std::uint32_t>(XK_Left);
constexpr std::uint32_t RIGHT = static_cast<std::uint32_t>(XK_Right);
constexpr std::uint32_t PAGE_UP = static_cast<std::uint32_t>(XK_Page_Up);
constexpr std::uint32_t PAGE_DOWN = static_cast<std::uint32_t>(XK_Page_Down);

class KeyboardHook {
public:
  KeyboardHook(const movement_callback& forward, const movement_callback& backward,
               const movement_callback& left, const movement_callback& right,
               const movement_callback& landing, const movement_callback& take_off) {
    display_ = XOpenDisplay(":0");
    if (display_ == nullptr) {
      throw("Keyboardhook Cannot open display :0");
    }
    statuses_.push_back(KeyStatus(UP, forward));
    statuses_.push_back(KeyStatus(DOWN, backward));
    statuses_.push_back(KeyStatus(LEFT, left));
    statuses_.push_back(KeyStatus(RIGHT, right));
    statuses_.push_back(KeyStatus(PAGE_UP, take_off));
    statuses_.push_back(KeyStatus(PAGE_DOWN, landing));
  };
  ~KeyboardHook() { XCloseDisplay(display_); }
  void run();

private:
  Display *display_{};

  struct KeyStatus {
    KeyStatus(std::uint32_t x_key_defined, movement_callback move_callback)
        : key_defined{x_key_defined}, callback{move_callback} {};
    std::uint32_t key_defined{};
    bool is_currently_pressed{};
    movement_callback callback{};
  };

  std::vector<KeyStatus> statuses_{};
};

} // namespace bebop_keyboard_controller
#endif // KEYBOARD_HOOK_H
