#ifndef KEYBOARD_HOOK_H
#define KEYBOARD_HOOK_H
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <exception>
#include <functional>

namespace bebop_keyboard_controller {

using movement_callback = std::function<void()>;

class KeyboardHook {
public:
  KeyboardHook(const movement_callback forward, movement_callback backward,
               movement_callback left, movement_callback right,
               movement_callback landing, movement_callback take_off)
      : m_move_forward_callback(forward), m_move_backward_callback(backward),
        m_move_left_callback(left), m_move_right_callback(right),
        m_landing_callback(landing), m_take_off_callback(take_off) {
    display_ = XOpenDisplay(":0");
    if (display_ == nullptr) {
      throw("Keyboardhook Cannot open display :0");
    }
  };
  ~KeyboardHook() { XCloseDisplay(display_); }
  void run();

private:
  static void listenToKeystroke(Display *);
  Display *display_{};
  movement_callback m_move_forward_callback{};
  movement_callback m_move_backward_callback{};
  movement_callback m_move_left_callback{};
  movement_callback m_move_right_callback{};
  movement_callback m_take_off_callback{};
  movement_callback m_landing_callback{};

  struct KeyStatus {
    KeyStatus(std::uint32_t x_key_defined) : key_defined{x_key_defined} {};
    std::uint32_t key_defined{};
    bool is_currently_pressed{};
  };

  int m_file_device{};
};

} // namespace bebop_keyboard_controller
#endif // KEYBOARD_HOOK_H
