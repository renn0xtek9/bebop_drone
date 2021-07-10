#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <keyboard_hook.h>
#include <mutex>
#include <thread>
#include <vector>
using namespace std::chrono_literals;
namespace bebop_keyboard_controller {

std::mutex callback_mutex;

void KeyboardHook::run() {
  constexpr std::uint32_t UP = static_cast<std::uint32_t>(XK_Up);
  constexpr std::uint32_t DOWN = static_cast<std::uint32_t>(XK_Down);
  constexpr std::uint32_t LEFT = static_cast<std::uint32_t>(XK_Left);
  constexpr std::uint32_t RIGHT = static_cast<std::uint32_t>(XK_Right);
  constexpr std::uint32_t PAGE_UP = static_cast<std::uint32_t>(XK_Page_Up);
  constexpr std::uint32_t PAGE_DOWN = static_cast<std::uint32_t>(XK_Page_Down);
  auto isPressed = [this](char *keys_return, const std::uint32_t &key_name) {
    KeyCode keycode = XKeysymToKeycode(display_, key_name);
    return !!(keys_return[keycode >> 3] & (1 << (keycode & 7)));
  };

  std::vector<KeyStatus> statuses{KeyStatus(UP),      KeyStatus(DOWN),
                                  KeyStatus(LEFT),    KeyStatus(RIGHT),
                                  KeyStatus(PAGE_UP), KeyStatus(PAGE_DOWN)};

  while (true) {
    std::array<char, 32> key_sequence{};
    XQueryKeymap(display_, key_sequence.data());

    for (auto &key_status : statuses) {
      if (isPressed(key_sequence.data(), key_status.key_defined)) {
        // rising front
        if (!key_status.is_currently_pressed) {
          key_status.is_currently_pressed = true;
          switch (key_status.key_defined) {
          case UP:
            m_move_forward_callback();
            break;
          case DOWN:
            m_move_backward_callback();
            break;
          case LEFT:
            m_move_left_callback();
            break;
          case RIGHT:
            m_move_right_callback();
            break;
          case PAGE_UP:
            m_take_off_callback();
            break;
          case PAGE_DOWN:
            m_landing_callback();
            break;
          default:
            break;
          }
        }
      } else {
        key_status.is_currently_pressed = false;
      }
    }
    std::this_thread::sleep_for(1ms);
  }
}
} // namespace bebop_keyboard_controller
