#ifndef BEBOP_CONTROLLER_H
#define BEBOP_CONTROLLER_H
#include <functional>
namespace bebop_keyboard_controller {

using callback = std::function<void()>;
class BebopController {
public:
  BebopController(const callback &take_off_or_land);

  void takeOff();
  void land();
  void moveForward();
  void moveBackward();
  void moveLeft();
  void moveRight();

private:
  void hoverStationary();
};

} // namespace bebop_keyboard_controller

#endif // BEBOP_CONTROLLER_H
