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

void KeyboardHook::run() {
  auto isPressed = [this](char *keys_return, const std::uint32_t &key_name) {
    KeyCode keycode = XKeysymToKeycode(display_, key_name);
    return !!(keys_return[keycode >> 3] & (1 << (keycode & 7)));
  };

  while (true) {
    std::array<char, 32> key_sequence{};
    XQueryKeymap(display_, key_sequence.data());

    for (auto &key_status : statuses_) {
      if (isPressed(key_sequence.data(), key_status.key_defined)) {
        // rising front
        if (!key_status.is_currently_pressed) {
          key_status.is_currently_pressed = true;
          key_status.callback();
        }
      } else {
        key_status.is_currently_pressed = false;
      }
    }
    std::this_thread::sleep_for(1ms);
  }
}
} // namespace bebop_keyboard_controller
