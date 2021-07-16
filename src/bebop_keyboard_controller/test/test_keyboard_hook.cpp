#include <iostream>
#include <keyboard_hook.h>
#include <mutex>
#include <thread>

void moveForward() {
  std::cout << "Forward !" << std::endl;
}

void moveBackWard() {
  std::cout << "Backward !" << std::endl;
}

void moveLeft() {
  std::cout << "Left !" << std::endl;
}

void moveRight() {
  std::cout << "Right !" << std::endl;
}

void takeOff() {
  std::cout << "Take off !" << std::endl;
}

void landing() {
  std::cout << "Landing !" << std::endl;
}

int main() {
  bebop_keyboard_controller::KeyboardHook keyboard_hook(
      moveForward, moveBackWard, moveLeft, moveRight, landing, takeOff);

  std::thread keyboard_hook_thread(
      &bebop_keyboard_controller::KeyboardHook::run, &keyboard_hook);
  keyboard_hook_thread.join();

  std::cout << "End of test" << std::endl;
}
