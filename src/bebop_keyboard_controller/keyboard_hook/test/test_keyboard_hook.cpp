#include <iostream>
#include <keyboard_hook.h>

bebop_keyboard_controller::movement_callback moveForward() {
  std::cout << "Forward !" << std::endl;
}
bebop_keyboard_controller::movement_callback moveBackWard() {
  std::cout << "Backward !" << std::endl;
}
bebop_keyboard_controller::movement_callback moveLeft() {
  std::cout << "Left !" << std::endl;
}
bebop_keyboard_controller::movement_callback moveRight() {
  std::cout << "right !" << std::endl;
}

int main() {
  bebop_keyboard_controller::KeyboardHook keyboard_hook(
      moveForward, moveBackWard, moveLeft, moveRight);
  keyboard_hook.run();

  std::cout << "End of test" << std::endl;
}
