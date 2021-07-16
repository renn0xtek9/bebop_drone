#include <bebop_controller.h>

namespace bebop_keyboard_controller {
BebopController::BebopController(const callback &take_off_or_land)
    : take_off_or_land_{take_off_or_land} 
    {
        // take_off_or_land_=std::bind(take_off_or_land);

    }
void BebopController::land() {
  if (is_supposed_to_be_airborne) {
    take_off_or_land_();
    is_supposed_to_be_airborne = false;
  }
}
void BebopController::takeOff() {
  if (not is_supposed_to_be_airborne) {
    take_off_or_land_();
    is_supposed_to_be_airborne = true;
  }
}
} // namespace bebop_keyboard_controller
