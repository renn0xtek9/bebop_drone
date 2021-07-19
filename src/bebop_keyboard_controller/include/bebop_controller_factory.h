#include <bebop_controller.h>
#include <keyboard_hook.h>
#include <memory>

namespace bebop_keyboard_controller {

callback dummy_callback{};

struct BebopControllerComponents {
  std::shared_ptr<KeyboardHook> keyboard_hook{};
  std::shared_ptr<BebopController> bebop_controller{};
};

class BebopControllerFactory {
public:
  BebopControllerFactory() {

    components.bebop_controller =
        std::make_shared<BebopController>(dummy_callback);
    components.keyboard_hook = std::make_shared<KeyboardHook>(
        components.bebop_controller->moveForward(),
        components.bebop_controller->moveBackward(),
        components.bebop_controller->moveLeft(),
        components.bebop_controller->moveRight(),
        components.bebop_controller->land(),
        components.bebop_controller->takeOff());
  };

  BebopControllerComponents components{};
};

} // namespace bebop_keyboard_controller
