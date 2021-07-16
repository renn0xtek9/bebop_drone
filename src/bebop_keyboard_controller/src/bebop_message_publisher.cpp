#include <bebop_message_publisher.h>

namespace bebop_keyboard_controller {

void BebopMessagePublisher::sendTakeOffOrLandingMessage() {}
void BebopMessagePublisher::sendCmdVelMessage(const double linear_x,
                                              const double linear_y,
                                              const double linear_z,
                                              const double angular_z) {}

} // namespace bebop_keyboard_controller
