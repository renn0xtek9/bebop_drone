#include <algorithm>
#include <chrono>
#include <iostream>
#include <keyboard_hook.h>
#include <thread>
#include <vector>
using namespace std::chrono_literals;
namespace bebop_keyboard_controller {

void KeyboardHook::run() {
  std::thread working_thread(this->listenToKeystroke, display_);
  working_thread.join();
}

void KeyboardHook::listenToKeystroke(Display *display) {
  constexpr std::uint32_t UP = static_cast<std::uint32_t>(XK_Up);
  constexpr std::uint32_t DOWN = static_cast<std::uint32_t>(XK_Down);
  constexpr std::uint32_t LEFT = static_cast<std::uint32_t>(XK_Left);
  constexpr std::uint32_t RIGHT = static_cast<std::uint32_t>(XK_Right);

  auto isPressed = [&display](char *keys_return,
                              const std::uint32_t &key_name) {
    KeyCode keycode = XKeysymToKeycode(display, key_name);
    return !!(keys_return[keycode >> 3] & (1 << (keycode & 7)));
  };

  std::vector<KeyStatus> statuses{KeyStatus(UP), KeyStatus(DOWN),
                                  KeyStatus(LEFT), KeyStatus(RIGHT)};

  while (true) {
    std::array<char, 32> key_sequence{};
    XQueryKeymap(display, key_sequence.data());

    for (auto &key_status : statuses) {
      if (isPressed(key_sequence.data(), key_status.key_defined)) {
        // rising front
        if (!key_status.is_currently_pressed) {
          key_status.is_currently_pressed = true;
          switch (key_status.key_defined) {
          case UP:
            std::cout << "Up is pressed" << std::endl;
            break;
          case DOWN:
            std::cout << "Down is pressed" << std::endl;
            break;
          case LEFT:
            std::cout << "Left is pressed" << std::endl;
            break;
          case RIGHT:
            std::cout << "Right is pressed" << std::endl;
            break;
          default:
            break;
          }
        }
      } else {
        key_status.is_currently_pressed = false;
      }
    }

    // std::size_t i{};
    // while (key_sequence[i] != '\0' and i < 32) {
    //   std::cout << key_sequence[i];
    //   ++i;
    // }
    // KeyCode keycode = XKeysymToKeycode(display, XK_Up);
    std::this_thread::sleep_for(1ms);
  }
}

} // namespace bebop_keyboard_controller
